from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory

from launch_ros.actions import Node
from launch.actions import TimerAction, ExecuteProcess, OpaqueFunction, LogInfo
from launch.substitutions import Command
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

import os
import shutil

from launch.conditions import IfCondition
from launch.conditions import UnlessCondition


packagepath = get_package_share_directory('xiaoxbot_description')
xacro_file = packagepath + '/urdf/xiaox_ros2_control.xacro'


def _launch_control_file(context):
    """Decide how to launch the control file at runtime."""
    cf = context.launch_configurations.get('control_file', '')
    if not cf:
        return []
    if cf == 'xiaox_keyboard.py':
        keyboard_cmd = 'ros2 run xiaox_bringup xiaox_keyboard.py; exec bash'
        terminal_commands = [
            ('x-terminal-emulator', ['x-terminal-emulator', '-e', 'bash', '-lc', keyboard_cmd]),
            ('gnome-terminal', ['gnome-terminal', '--', 'bash', '-lc', keyboard_cmd]),
            ('konsole', ['konsole', '-e', 'bash', '-lc', keyboard_cmd]),
            ('xterm', ['xterm', '-e', 'bash', '-lc', keyboard_cmd]),
        ]

        for terminal_name, cmd in terminal_commands:
            if shutil.which(terminal_name):
                return [ExecuteProcess(cmd=cmd, output='screen')]

        return [
            LogInfo(
                msg='No supported terminal emulator found; starting keyboard node inline.'
            ),
            ExecuteProcess(
                cmd=['bash', '-lc', 'ros2 run xiaox_bringup xiaox_keyboard.py'],
                output='screen',
                emulate_tty=True,
            )
        ]
    else:
        return [Node(
            package='xiaox_bringup',
            executable=cf,
        )]


def generate_launch_description():

    actions = []

    actions.append(
        DeclareLaunchArgument(
            'use_gazebo',
            default_value='false',
            description='Whether to use Gazebo simulation',
            choices=['true', 'false', 'True', 'False']
        )
    )

    actions.append(
        DeclareLaunchArgument(
            'use_real_hardware',
            default_value='false',
            description='Whether to use real robot hardware via serial',
            choices=['true', 'false', 'True', 'False']
        )
    )

    actions.append(
        DeclareLaunchArgument(
            'serial_port',
            default_value='/dev/ttyACM0',
            description='Serial port for real hardware'
        )
    )

    actions.append(
        DeclareLaunchArgument(
            'baud_rate',
            default_value='115200',
            description='Baud rate for serial communication'
        )
    )

    actions.append(
        DeclareLaunchArgument(
            'command_speed',
            default_value='180.0',
            description='Joint command speed in deg/s for real hardware'
        )
    )

    actions.append(
        DeclareLaunchArgument(
            'control_file',
            default_value='',
            description='choice the control file',
            choices=[
                '',
                'xiaox_keyboard.py'
            ]
        )
    )

    use_gazebo = LaunchConfiguration('use_gazebo', default='false')
    use_real_hardware = LaunchConfiguration('use_real_hardware', default='false')
    serial_port = LaunchConfiguration('serial_port')
    baud_rate = LaunchConfiguration('baud_rate')
    command_speed = LaunchConfiguration('command_speed')

    robot_desc = Command([
        'xacro ', xacro_file,
        ' use_gazebo:=', use_gazebo,
        ' use_real_hardware:=', use_real_hardware,
        ' serial_port:=', serial_port,
        ' baud_rate:=', baud_rate,
        ' command_speed:=', command_speed,
    ])


    actions.append(
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [os.path.join(
                    get_package_share_directory('xiaox_bringup'),
                    'launch'),
                 '/sim.launch.py']
            ),
            launch_arguments=[('robot_desc', robot_desc)],
            condition=IfCondition(use_gazebo)
        )
    )


    controller_manager_node = Node(
        package='controller_manager',
        executable='ros2_control_node',
        parameters=[get_package_share_directory('xiaox_controllers') + '/config/xiaox_controllers.yaml'],
        remappings=[
            ('~/robot_description', '/robot_description'),
        ],
        output='both',
        condition=UnlessCondition(use_gazebo)
    )

    driver_node = Node(
        package='xiaox_driver',
        executable='driver_node',
        name='xiaox_driver',
        output='screen',
        parameters=[{
            'serial_port': serial_port,
            'baud_rate': baud_rate,
            'command_mode': 2,
            'command_speed': command_speed,
        }],
        condition=IfCondition(
            PythonExpression([
                '"', use_real_hardware, '" in ["true", "True"] and "',
                use_gazebo, '" not in ["true", "True"]'
            ])
        )
    )


    robot_desc_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='both',
        parameters=[
            {'use_sim_time': use_gazebo},
            {'robot_description': robot_desc}
        ]
    )


    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz',
        arguments=['-d', packagepath + '/rviz/rviz.rviz']
    )


    controllers_node = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'arm_controller',
            'joint_state_broadcaster',
            '--param-file', get_package_share_directory('xiaox_controllers') + '/config/xiaox_controllers.yaml'
        ],
        output='screen',
        name='controllers'
    )


    actions.extend([
        robot_desc_node,
        rviz_node,
        driver_node,
        controller_manager_node,
        TimerAction(
            period=2.0,
            actions=[controllers_node],
        ),
        TimerAction(
            period=5.0,
            actions=[OpaqueFunction(function=_launch_control_file)],
        )
    ])


    return LaunchDescription(actions)
