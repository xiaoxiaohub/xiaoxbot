#!/usr/bin/env python3
import errno
import fcntl
import os
import select
import termios
import threading
import time

import rclpy
from rclpy.node import Node

from xiaox_interfaces.srv import InitDevice, ReadJoints, WriteJoints


NUM_JOINTS = 6
DEFAULT_COMMAND_MODE = 2
DEFAULT_COMMAND_SPEED = 180.0
DEFAULT_BAUD_RATE = 115200
DEFAULT_TIMEOUT_MS = 200
DEFAULT_RETRIES = 25
DEFAULT_RETRY_SLEEP_MS = 200


BAUD_RATE_MAP = {
    9600: termios.B9600,
    19200: termios.B19200,
    38400: termios.B38400,
    57600: termios.B57600,
    115200: termios.B115200,
}

if hasattr(termios, 'B230400'):
    BAUD_RATE_MAP[230400] = termios.B230400
if hasattr(termios, 'B460800'):
    BAUD_RATE_MAP[460800] = termios.B460800
if hasattr(termios, 'B921600'):
    BAUD_RATE_MAP[921600] = termios.B921600


class XiaoxDriverNode(Node):
    def __init__(self):
        super().__init__('xiaox_driver')

        self.declare_parameter('serial_port', '/dev/ttyACM0')
        self.declare_parameter('baud_rate', DEFAULT_BAUD_RATE)
        self.declare_parameter('command_mode', DEFAULT_COMMAND_MODE)
        self.declare_parameter('command_speed', DEFAULT_COMMAND_SPEED)
        self.declare_parameter('reply_timeout_ms', DEFAULT_TIMEOUT_MS)
        self.declare_parameter('init_retries', DEFAULT_RETRIES)
        self.declare_parameter('retry_sleep_ms', DEFAULT_RETRY_SLEEP_MS)

        self.serial_port = self.get_parameter('serial_port').value
        self.baud_rate = int(self.get_parameter('baud_rate').value)
        self.command_mode = int(self.get_parameter('command_mode').value)
        self.command_speed = float(self.get_parameter('command_speed').value)
        self.reply_timeout_ms = int(self.get_parameter('reply_timeout_ms').value)
        self.init_retries = int(self.get_parameter('init_retries').value)
        self.retry_sleep_ms = int(self.get_parameter('retry_sleep_ms').value)

        self.serial_fd = -1
        self.motors_enabled = False
        self.joint_positions = [0.0] * NUM_JOINTS
        self.joint_velocities = [0.0] * NUM_JOINTS
        self.last_feedback_time = None
        self.lock = threading.Lock()

        self.create_service(InitDevice, 'init_device', self.init_device_callback)
        self.create_service(WriteJoints, 'write_joints', self.write_joints_callback)
        self.create_service(ReadJoints, 'read_joints', self.read_joints_callback)

        self.get_logger().info(
            f'Xiaox driver ready on {self.serial_port} @ {self.baud_rate} baud'
        )

    def init_device_callback(self, request, response):
        with self.lock:
            action = request.action.strip().lower()
            success = False
            message = ''

            try:
                if action == 'start':
                    success, message = self.start_session()
                elif action == 'stop':
                    success, message = self.stop_session()
                elif action == 'active':
                    success, message = self.set_active(True)
                elif action == 'deactive':
                    success, message = self.set_active(False)
                else:
                    message = f'unsupported action: {request.action}'
            except OSError as exc:
                success = False
                message = f'OS error: {exc}'
            except Exception as exc:
                success = False
                message = str(exc)

            response.success = success
            response.message = message
            if success:
                self.get_logger().info(f'Device action {action}: {message}')
            else:
                self.get_logger().error(f'Device action {action} failed: {message}')
            return response

    def write_joints_callback(self, request, response):
        with self.lock:
            response.success = False
            response.message = ''

            if len(request.positions) != NUM_JOINTS:
                response.message = f'expected {NUM_JOINTS} joint positions, got {len(request.positions)}'
                return response

            if self.serial_fd < 0:
                response.message = 'serial port is not open'
                return response

            command = '>{},'.format(
                ','.join(f'{float(pos):.2f}' for pos in request.positions)
            )
            if self.command_mode == 2:
                command += f'{self.command_speed:.2f}'
            command += '\n'

            if not self.serial_send(command):
                recovered = self.recover_connection('joint command write failure')
                if not recovered or not self.serial_send(command):
                    response.message = 'failed to send joint command'
                    return response

            response.success = True
            response.message = 'joint command sent'
            return response

    def read_joints_callback(self, request, response):
        with self.lock:
            response.success = False
            response.message = ''
            response.positions = list(self.joint_positions)
            response.velocities = list(self.joint_velocities)

            if request.action and request.action.lower() not in ('read', 'status'):
                response.message = f'unsupported action: {request.action}'
                return response

            if self.serial_fd < 0:
                response.message = 'serial port is not open'
                return response

            positions = self.request_joint_positions()
            if positions is None:
                recovered = self.recover_connection('joint feedback timeout')
                if recovered:
                    positions = self.request_joint_positions()

            if positions is None:
                response.message = 'failed to read joint positions'
                return response

            self.update_feedback_cache(positions)
            response.success = True
            response.message = 'joint positions updated'
            response.positions = list(self.joint_positions)
            response.velocities = list(self.joint_velocities)
            return response

    def start_session(self):
        if self.serial_fd >= 0:
            return True, 'serial session already open'

        if not self.serial_open():
            return False, f'cannot open {self.serial_port}'

        if not self.initialize_serial_session(reset_feedback=True):
            self.serial_close()
            return False, 'failed to initialize firmware session'

        self.motors_enabled = False
        return True, 'serial session initialized'

    def stop_session(self):
        if self.serial_fd >= 0:
            self.stop_and_disable_motors(retries=3)
        self.motors_enabled = False
        self.serial_close()
        return True, 'serial session closed'

    def set_active(self, enabled):
        if self.serial_fd < 0:
            ok, message = self.start_session()
            if not ok:
                return ok, message

        if enabled:
            command_ok = self.send_control_command('!START\n', retries=self.init_retries)
        else:
            command_ok = self.stop_and_disable_motors(retries=self.init_retries)
        if not command_ok:
            recovered = self.recover_connection('motor state change failed')
            if enabled:
                command_ok = self.send_control_command('!START\n', retries=self.init_retries)
            else:
                command_ok = self.stop_and_disable_motors(retries=self.init_retries)
            if not recovered or not command_ok:
                return False, 'failed to enable motors' if enabled else 'failed to disable motors'

        self.motors_enabled = enabled
        positions = self.request_joint_positions()
        if positions is not None:
            self.update_feedback_cache(positions, reset_velocity=True)
        return True, 'motors enabled' if enabled else 'motors disabled'

    def stop_and_disable_motors(self, retries):
        stop_ok = self.send_control_command('!STOP\n', retries=retries)
        disable_ok = self.send_control_command('!DISABLE\n', retries=retries)
        return stop_ok and disable_ok

    def recover_connection(self, reason):
        restore_motor_state = self.motors_enabled
        self.get_logger().warning(
            f'Serial issue detected ({reason}), attempting recovery on {self.serial_port}'
        )

        self.serial_close()
        if not self.serial_open():
            return False

        if not self.initialize_serial_session(reset_feedback=True):
            self.serial_close()
            return False

        if restore_motor_state and not self.send_control_command('!START\n', retries=self.init_retries):
            self.serial_close()
            return False

        self.motors_enabled = restore_motor_state
        self.get_logger().info(f'Serial recovery succeeded on {self.serial_port}')
        return True

    def initialize_serial_session(self, reset_feedback):
        self.serial_flush_input()
        time.sleep(0.25)
        self.serial_flush_input()

        reply = self.serial_send_and_read_reply(
            f'#CMDMODE {self.command_mode}\n',
            retries=self.init_retries,
            timeout_ms=self.reply_timeout_ms,
            retry_sleep_ms=self.retry_sleep_ms,
        )
        if reply is None:
            self.get_logger().error(f'No response to CMDMODE on {self.serial_port}')
            return False

        positions = self.request_joint_positions(
            retries=self.init_retries,
            timeout_ms=self.reply_timeout_ms,
            retry_sleep_ms=self.retry_sleep_ms,
        )
        if positions is None:
            self.get_logger().error(
                f'Failed to read initial joint positions from {self.serial_port}'
            )
            return False

        self.update_feedback_cache(positions, reset_velocity=reset_feedback)
        self.get_logger().info(f'CMDMODE response: {reply}')
        return True

    def send_control_command(self, command, retries):
        reply = self.serial_send_and_read_reply(
            command,
            retries=retries,
            timeout_ms=self.reply_timeout_ms,
            retry_sleep_ms=50,
        )
        if reply is None:
            return False
        command_name = command.strip().lstrip('!')
        self.get_logger().info(f'{command_name} response: {reply}')
        return True

    def update_feedback_cache(self, positions, reset_velocity=False):
        now = time.monotonic()
        if self.last_feedback_time is None or reset_velocity:
            velocities = [0.0] * NUM_JOINTS
        else:
            dt = now - self.last_feedback_time
            if dt <= 0.0:
                velocities = [0.0] * NUM_JOINTS
            else:
                velocities = [
                    (new - old) / dt for new, old in zip(positions, self.joint_positions)
                ]

        self.joint_positions = list(positions)
        self.joint_velocities = velocities
        self.last_feedback_time = now

    def request_joint_positions(self, retries=1, timeout_ms=100, retry_sleep_ms=20):
        for attempt in range(retries):
            self.serial_flush_input()
            if not self.serial_send('#GETJPOS\n'):
                return None

            for _ in range(3):
                reply = self.serial_read_line(timeout_ms)
                if not reply:
                    break

                ok_pos = reply.find('ok')
                if ok_pos > 0:
                    reply = reply[ok_pos:]

                if not reply.startswith('ok'):
                    continue

                parts = reply.split()
                if len(parts) < NUM_JOINTS + 1:
                    continue

                try:
                    return [float(value) for value in parts[1:NUM_JOINTS + 1]]
                except ValueError:
                    continue

            if attempt + 1 < retries:
                time.sleep(retry_sleep_ms / 1000.0)

        return None

    def serial_open(self):
        flags = os.O_RDWR | os.O_NOCTTY | os.O_NONBLOCK
        try:
            self.serial_fd = os.open(self.serial_port, flags)
        except OSError as exc:
            self.get_logger().error(f'Cannot open {self.serial_port}: {exc}')
            self.serial_fd = -1
            return False

        current_flags = fcntl.fcntl(self.serial_fd, fcntl.F_GETFL)
        fcntl.fcntl(self.serial_fd, fcntl.F_SETFL, current_flags & ~os.O_NONBLOCK)

        try:
            attrs = termios.tcgetattr(self.serial_fd)
        except termios.error as exc:
            self.get_logger().error(f'tcgetattr failed: {exc}')
            self.serial_close()
            return False

        speed = BAUD_RATE_MAP.get(self.baud_rate, termios.B115200)
        attrs[4] = speed
        attrs[5] = speed

        attrs[0] &= ~(
            termios.IXON | termios.IXOFF | termios.IXANY |
            termios.IGNBRK | termios.BRKINT | termios.PARMRK |
            termios.ISTRIP | termios.INLCR | termios.IGNCR | termios.ICRNL
        )
        attrs[1] &= ~termios.OPOST
        attrs[2] &= ~(termios.PARENB | termios.CSTOPB | termios.CSIZE)
        if hasattr(termios, 'CRTSCTS'):
            attrs[2] &= ~termios.CRTSCTS
        if hasattr(termios, 'HUPCL'):
            attrs[2] &= ~termios.HUPCL
        attrs[2] |= termios.CS8 | termios.CREAD | termios.CLOCAL
        attrs[3] &= ~(termios.ICANON | termios.ECHO | termios.ECHOE | termios.ISIG)
        attrs[6][termios.VMIN] = 0
        attrs[6][termios.VTIME] = 2

        try:
            termios.tcsetattr(self.serial_fd, termios.TCSANOW, attrs)
            termios.tcflush(self.serial_fd, termios.TCIOFLUSH)
        except termios.error as exc:
            self.get_logger().error(f'tcsetattr failed: {exc}')
            self.serial_close()
            return False

        return True

    def serial_close(self):
        if self.serial_fd >= 0:
            os.close(self.serial_fd)
            self.serial_fd = -1

    def serial_flush_input(self):
        if self.serial_fd >= 0:
            termios.tcflush(self.serial_fd, termios.TCIFLUSH)

    def serial_send(self, message):
        if self.serial_fd < 0:
            return False

        data = message.encode('ascii')
        total_written = 0
        while total_written < len(data):
            try:
                written = os.write(self.serial_fd, data[total_written:])
            except OSError as exc:
                if exc.errno == errno.EINTR:
                    continue
                self.get_logger().warning(f'Serial write failed: {exc}')
                return False

            if written <= 0:
                return False
            total_written += written

        return True

    def serial_read_line(self, timeout_ms):
        if self.serial_fd < 0:
            return ''

        deadline = time.monotonic() + (timeout_ms / 1000.0)
        line = bytearray()

        while time.monotonic() < deadline:
            remaining = max(0.0, deadline - time.monotonic())
            readable, _, _ = select.select([self.serial_fd], [], [], remaining)
            if not readable:
                break

            chunk = os.read(self.serial_fd, 1)
            if not chunk:
                break

            char = chunk[0]
            if char == ord('\n'):
                break
            if char != ord('\r'):
                line.append(char)

        return line.decode('ascii', errors='ignore').strip()

    def serial_send_and_read_reply(self, message, retries, timeout_ms, retry_sleep_ms):
        for attempt in range(retries):
            self.serial_flush_input()
            if not self.serial_send(message):
                return None

            reply = self.serial_read_line(timeout_ms)
            if reply:
                return reply

            if attempt + 1 < retries:
                time.sleep(retry_sleep_ms / 1000.0)

        return None


def main(args=None):
    rclpy.init(args=args)
    node = XiaoxDriverNode()
    try:
        rclpy.spin(node)
    finally:
        with node.lock:
            node.stop_session()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
