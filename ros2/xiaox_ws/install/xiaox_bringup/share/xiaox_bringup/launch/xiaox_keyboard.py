#!/usr/bin/env python3
import sys
import time
import tty
import termios
import select
import rclpy
from rclpy.node import Node

from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from sensor_msgs.msg import JointState
from builtin_interfaces.msg import Duration
from xiaox_interfaces.srv import WriteJoints
from controller_manager_msgs.srv import ListHardwareComponents, SetHardwareComponentState
from lifecycle_msgs.msg import State


class DummyKeyboardController(Node):
    def __init__(self):
        super().__init__('dummy_keyboard_controller')

        self.declare_parameter('controller_manager_name', '/controller_manager')
        self.declare_parameter('hardware_component_name', 'XiaoxSystem')

        self.publisher = self.create_publisher(
            JointTrajectory,
            '/arm_controller/joint_trajectory',
            10
        )

        self.joint_names = ['Joint1', 'Joint2', 'Joint3', 'Joint4', 'Joint5', 'Joint6']
        self.current_positions = None
        self.feedback_positions = [0.0] * len(self.joint_names)
        self.joint_state_ready = False
        self.last_command_time = 0.0
        self.last_joint_state_time = 0.0
        self.feedback_stale_warned = False
        self.start_fold_positions = None
        self.home_positions = [0.0] * len(self.joint_names)
        self.last_known_hardware_state = None

        controller_manager_name = self.get_parameter('controller_manager_name').value
        if not controller_manager_name.startswith('/'):
            controller_manager_name = '/' + controller_manager_name
        self.controller_manager_name = controller_manager_name
        self.hardware_component_name = self.get_parameter('hardware_component_name').value

        self.write_client = self.create_client(WriteJoints, 'write_joints')
        self.set_hardware_state_client = self.create_client(
            SetHardwareComponentState,
            f'{self.controller_manager_name}/set_hardware_component_state'
        )
        self.list_hardware_components_client = self.create_client(
            ListHardwareComponents,
            f'{self.controller_manager_name}/list_hardware_components'
        )

        self.joint_state_sub = self.create_subscription(
            JointState,
            '/joint_states',
            self._joint_state_cb,
            10
        )

        self.step = 0.1  # 每次按键变化弧度
        self.limit = 3.14

        self._wait_for_joint_states()
        self.start_fold_positions = list(self.current_positions)
        self._wait_for_management_services()
        self._refresh_hardware_state(log_result=True)

        self.get_logger().info(
            '\n键盘控制说明：\n'
            'q/a -> Joint1 +/-\n'
            'w/s -> Joint2 +/-\n'
            'e/d -> Joint3 +/-\n'
            'r/f -> Joint4 +/-\n'
            't/g -> Joint5 +/-\n'
            'y/h -> Joint6 +/-\n'
            'v   -> 手动使能\n'
            'b   -> 手动关闭使能\n'
            'z   -> 回到 home (全零)\n'
            'c   -> 回到起始收缩位\n'
            'p   -> 查询硬件状态\n'
            'x   -> 退出\n'
        )

    def _wait_for_joint_states(self):
        self.get_logger().info('等待 /joint_states 获取当前关节位置...')
        while rclpy.ok() and not self.joint_state_ready:
            rclpy.spin_once(self, timeout_sec=0.5)

        self.get_logger().info(
            f'初始关节位置 (rad): {[round(v, 3) for v in self.current_positions]}'
        )

    def _wait_for_management_services(self):
        services = [
            (self.set_hardware_state_client, 'set_hardware_component_state'),
            (self.list_hardware_components_client, 'list_hardware_components'),
        ]

        for client, name in services:
            while rclpy.ok() and not client.wait_for_service(timeout_sec=1.0):
                self.get_logger().info(f'等待 {self.controller_manager_name}/{name} 服务...')

    def _joint_state_cb(self, msg):
        name_to_index = {name: i for i, name in enumerate(msg.name)}
        has_full_state = True

        for i, name in enumerate(self.joint_names):
            idx = name_to_index.get(name)
            if idx is None or idx >= len(msg.position):
                has_full_state = False
                continue
            self.feedback_positions[i] = msg.position[idx]

        if not has_full_state:
            return

        if self.current_positions is None or (time.monotonic() - self.last_command_time) > 0.5:
            self.current_positions = list(self.feedback_positions)

        self.joint_state_ready = True
        self.last_joint_state_time = time.monotonic()
        self.feedback_stale_warned = False

    def get_key(self):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
            if rlist:
                ch = sys.stdin.read(1)
            else:
                ch = ''
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

    def clamp(self, value):
        return max(min(value, self.limit), -self.limit)

    def _call_service(self, client, request, timeout_sec=3.0):
        future = client.call_async(request)
        rclpy.spin_until_future_complete(self, future, timeout_sec=timeout_sec)
        if not future.done():
            self.get_logger().warning('服务调用超时')
            return None
        exc = future.exception()
        if exc is not None:
            self.get_logger().warning(f'服务调用失败: {exc}')
            return None
        return future.result()

    def _refresh_hardware_state(self, log_result=False):
        request = ListHardwareComponents.Request()
        response = self._call_service(self.list_hardware_components_client, request)
        if response is None:
            return None

        for component in response.component:
            if component.name == self.hardware_component_name:
                self.last_known_hardware_state = component.state.label
                if log_result:
                    self.get_logger().info(
                        f'硬件 {self.hardware_component_name} 当前状态: {component.state.label}'
                    )
                return component.state.label

        self.get_logger().warning(
            f'没有在 controller_manager 中找到硬件组件 {self.hardware_component_name}'
        )
        return None

    def _set_hardware_state(self, target_label):
        target_state = State()
        if target_label == 'active':
            target_state.id = State.PRIMARY_STATE_ACTIVE
            target_state.label = 'active'
        elif target_label == 'inactive':
            target_state.id = State.PRIMARY_STATE_INACTIVE
            target_state.label = 'inactive'
        else:
            self.get_logger().warning(f'不支持的硬件目标状态: {target_label}')
            return False

        request = SetHardwareComponentState.Request()
        request.name = self.hardware_component_name
        request.target_state = target_state

        response = self._call_service(self.set_hardware_state_client, request)
        if response is None:
            return False

        self.last_known_hardware_state = response.state.label
        if not response.ok:
            self.get_logger().warning(
                f'切换硬件状态失败，当前状态: {response.state.label}'
            )
            return False

        self.current_positions = list(self.feedback_positions)
        self.last_command_time = 0.0
        self.get_logger().info(
            f'硬件 {self.hardware_component_name} 已切换到 {response.state.label}'
        )
        return True

    def _motion_allowed(self):
        state = self.last_known_hardware_state
        if state is None:
            state = self._refresh_hardware_state(log_result=False)

        if state != 'active':
            self.get_logger().warning('机械臂当前未使能，请先按 v 使能')
            return False
        return True

    def _check_joint_state_freshness(self):
        if self.last_joint_state_time <= 0.0:
            return

        if (time.monotonic() - self.last_joint_state_time) > 10.0 and not self.feedback_stale_warned:
            self.feedback_stale_warned = True
            self.get_logger().warning(
                '/joint_states 已超过 10 秒未更新，RViz TF 和键盘控制都会失效，请检查 controller_manager 或串口连接'
            )

    def publish_positions(self, positions=None, move_name='关节命令', duration_sec=1.0):
        if self.current_positions is None:
            self.get_logger().warning('尚未收到完整的 /joint_states，忽略当前按键')
            return

        if positions is not None:
            self.current_positions = [float(p) for p in positions]

        msg = JointTrajectory()
        msg.header.stamp.sec = 0
        msg.header.stamp.nanosec = 0
        msg.joint_names = self.joint_names

        point = JointTrajectoryPoint()
        point.positions = [float(p) for p in self.current_positions]
        sec = int(duration_sec)
        nanosec = int((duration_sec - sec) * 1e9)
        point.time_from_start = Duration(sec=sec, nanosec=nanosec)

        msg.points = [point]
        self.publisher.publish(msg)
        self.last_command_time = time.monotonic()

        self.get_logger().info(
            f'{move_name}: {[round(v, 3) for v in self.current_positions]}'
        )

    def _handle_exit(self):
        state = self.last_known_hardware_state
        if state is None:
            state = self._refresh_hardware_state(log_result=False)

        if state == 'active':
            self.get_logger().warning('退出键盘控制，机械臂仍处于使能状态；如需下使能，请先按 b')
        else:
            self.get_logger().info('退出键盘控制')

    def run(self):
        key_map = {
            'q': (0, +1), 'a': (0, -1),
            'w': (1, +1), 's': (1, -1),
            'e': (2, +1), 'd': (2, -1),
            'r': (3, +1), 'f': (3, -1),
            't': (4, +1), 'g': (4, -1),
            'y': (5, +1), 'h': (5, -1),
        }

        while rclpy.ok():
            rclpy.spin_once(self, timeout_sec=0.0)
            self._check_joint_state_freshness()
            key = self.get_key()

            if not key:
                continue

            if key == '\x03' or key == 'x':  # \x03 is Ctrl+C
                self._handle_exit()
                break

            if key == 'p':
                self._refresh_hardware_state(log_result=True)
                continue

            if key == 'v':
                self._set_hardware_state('active')
                continue

            if key == 'b':
                self._set_hardware_state('inactive')
                continue

            if key == 'z':
                if self._motion_allowed():
                    self.publish_positions(
                        positions=self.home_positions,
                        move_name='回到 home',
                        duration_sec=2.5
                    )
                continue

            if key == 'c':
                if self.start_fold_positions is None:
                    self.get_logger().warning('尚未记录到起始收缩位')
                    continue
                if self._motion_allowed():
                    self.publish_positions(
                        positions=self.start_fold_positions,
                        move_name='回到起始收缩位',
                        duration_sec=2.5
                    )
                continue

            if key in key_map:
                if not self._motion_allowed():
                    continue
                idx, direction = key_map[key]
                self.current_positions[idx] = self.clamp(
                    self.current_positions[idx] + direction * self.step
                )
                self.publish_positions(move_name='当前关节角')


def main(args=None):
    rclpy.init(args=args)
    node = DummyKeyboardController()
    try:
        node.run()
    except KeyboardInterrupt:
        node._handle_exit()
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
