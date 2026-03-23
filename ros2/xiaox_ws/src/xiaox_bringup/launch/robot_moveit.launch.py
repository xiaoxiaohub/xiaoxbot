#!/usr/bin/env python3
"""
Launch file for controlling real robot arm with MoveIt.
Combines MoveIt planning with real hardware support.

Usage:
    ros2 launch xiaox_bringup robot_moveit.launch.py use_real_hardware:=true serial_port:=/dev/ttyACM0 baud_rate:=115200 command_speed:=180.0
"""

from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory

from launch_ros.actions import Node
from launch.actions import TimerAction, DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import Command, LaunchConfiguration, PythonExpression
from launch.launch_description_sources import PythonLaunchDescriptionSource

import os

from launch.conditions import IfCondition
from launch.conditions import UnlessCondition


def generate_launch_description():
    actions = []

    # Launch arguments
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

    use_gazebo = LaunchConfiguration('use_gazebo', default='false')
    use_real_hardware = LaunchConfiguration('use_real_hardware', default='false')
    serial_port = LaunchConfiguration('serial_port')
    baud_rate = LaunchConfiguration('baud_rate')
    command_speed = LaunchConfiguration('command_speed')

    # URDF description
    packagepath = get_package_share_directory('xiaoxbot_description')
    xacro_file = packagepath + '/urdf/xiaox_ros2_control.xacro'

    robot_desc = Command([
        'xacro ', xacro_file,
        ' use_gazebo:=', use_gazebo,
        ' use_real_hardware:=', use_real_hardware,
        ' serial_port:=', serial_port,
        ' baud_rate:=', baud_rate,
        ' command_speed:=', command_speed,
    ])

    # Robot state publisher
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

    # Controller manager (real hardware only, not for Gazebo)
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

    # Driver node (real hardware only)
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

    # Controllers
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

    # MoveIt move_group
    move_group_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory('xiaoxbot_moveit_config'),
                'launch',
                'move_group.launch.py'
            )
        ),
    )

    # MoveIt RViz
    moveit_rviz_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory('xiaoxbot_moveit_config'),
                'launch',
                'moveit_rviz.launch.py'
            )
        ),
    )

    actions.extend([
        robot_desc_node,
        driver_node,
        controller_manager_node,
        TimerAction(
            period=2.0,
            actions=[controllers_node],
        ),
        TimerAction(
            period=3.0,
            actions=[move_group_launch],
        ),
        TimerAction(
            period=4.0,
            actions=[moveit_rviz_launch],
        ),
    ])

    return LaunchDescription(actions)
