# Xiaox Robot Arm

基于稚晖君 [Dummy Robot](https://github.com/peng-zhihui/Dummy-Robot) 的开源六轴机械臂项目，包含 STM32 固件和完整 ROS2 控制栈，支持 Gazebo 仿真与真实硬件控制。

## 快速开始（真实硬件 + MoveIt）

你当前验证通过的最短流程如下：

1. 启动主链路（MoveIt + ros2_control + 驱动）：

```bash
source ros2/xiaox_ws/install/setup.bash
ros2 launch xiaox_bringup robot_moveit.launch.py \
  use_real_hardware:=true \
  serial_port:=/dev/ttyACM0 \
  baud_rate:=115200 \
  command_speed:=180.0
```

2. 新开终端，启动键盘节点并使能：

```bash
source ros2/xiaox_ws/install/setup.bash
ros2 run xiaox_bringup xiaox_keyboard.py
```

在键盘窗口按 `v`，将硬件组件 `XiaoxSystem` 从 `inactive` 切到 `active`。

3. 回到 RViz 拖动机械臂并执行轨迹，实机即可动作。

## 系统架构

### 1) ASCII 总览（快速理解）

```text
                         命令下行链路
[用户/RViz/MoveIt] --------------------------------> [ros2_control] ---------------------> [固件/电机]
      ^                                                   |                                       |
      |                                                   |                                       |
      |                                                   v                                       |
      |                                             [xiaox_hardware] <----服务调用----> [xiaox_driver]
      |                                                   ^                               |
      +---------------------- /joint_states 反馈 ---------+                               v
                                                                                      /dev/ttyACM0
                                                                                           |
                                                                                           v
                                                                                       UART/ASCII
```

### 2) Mermaid 总览（详细链路）

![System Architecture Diagram](/doc/flowchart.png)


### 3) 三条关键链路

- `命令下行`：`RViz -> move_group -> arm_controller -> XiaoxHardware -> xiaox_driver -> 串口 -> 固件 -> 电机`
- `状态上行`：`电机 -> 固件 -> 串口 -> 驱动 -> XiaoxHardware -> /joint_states -> RViz`
- `使能控制`：`xiaox_keyboard(v键) -> set_hardware_component_state(active)`；未使能时实机不执行轨迹

## 核心原理（分层）

### 用户层

- 在终端运行 launch 和键盘使能脚本
- 在 RViz 中拖动目标并执行轨迹

### 应用层

- `robot_moveit.launch.py` 负责启动 MoveIt、RViz、`ros2_control_node`、`xiaox_driver`
- `move_group` 负责规划轨迹
- `xiaox_keyboard.py` 负责手动使能/下使能和关节调试

### 控制层

- `arm_controller` 使用 `joint_trajectory_controller` 执行关节轨迹
- `controller_manager` 管理控制器与硬件组件生命周期
- `XiaoxSystem` 初始在 `inactive`（见 `xiaox_controllers.yaml`）

### 硬件与通信层

- `XiaoxHardware` 是 `ros2_control` 硬件插件
- 通过服务调用 `xiaox_driver`：
  - `InitDevice`
  - `ReadJoints`
  - `WriteJoints`
- `xiaox_driver` 通过 `/dev/ttyACM0` 使用 ASCII 协议和 STM32 固件通信

## 项目结构

```
xiaoxbot/
├── firmware/                         # STM32 电机控制板固件
│   ├── dummy-35motor-fw/             # 35 步进电机固件 (STM32F103)
│   ├── dummy-42motor-fw/             # 42 步进电机固件 (STM32F103)
│   └── dummy-ref-core-fw/            # 参考核心固件 (STM32F405)
└── ros2/
    └── xiaox_ws/                     # ROS2 工作空间
        └── src/
            ├── xiaox_interfaces/      # ROS2 服务/消息接口定义
            ├── xiaoxbot_description/  # URDF/Xacro、网格、RViz配置
            ├── xiaoxbot_moveit_config/# MoveIt 配置与 launch
            ├── xiaox_bringup/         # 启动文件（MoveIt/实机/仿真）
            ├── xiaox_controllers/     # ros2_control 控制器参数
            ├── xiaox_hardware/        # ros2_control 硬件接口插件
            └── xiaox_driver/          # 串口驱动节点（与固件通信）
```

## 包职责说明

| 包名 | 职责 |
|------|------|
| `xiaox_interfaces` | 定义 `InitDevice`、`ReadJoints`、`WriteJoints` 服务 |
| `xiaoxbot_description` | 机器人 URDF/Xacro、网格、RViz 配置 |
| `xiaoxbot_moveit_config` | MoveIt 配置与 launch |
| `xiaox_bringup` | 启动文件和键盘节点 |
| `xiaox_controllers` | `ros2_control` 控制器参数 |
| `xiaox_hardware` | `ros2_control` 硬件插件 |
| `xiaox_driver` | 串口驱动，与固件进行 ASCII 协议通信 |

## 环境要求

- Ubuntu 22.04+
- ROS2 Humble 或更高版本
- ROS2 依赖：
  - `ros2_control`、`ros2_controllers`
  - `controller_manager`
  - `joint_trajectory_controller`、`joint_state_broadcaster`
  - `xacro`、`robot_state_publisher`、`rviz2`
  - `ros_gz_sim`、`ros_gz_bridge`、`gz_ros2_control`（仿真需要）

## 安装

### 1. 克隆项目

```bash
git clone <本项目地址>
cd xiaoxbot
```

### 2. 安装 ROS2 依赖

```bash
sudo apt install ros-humble-ros2-control ros-humble-ros2-controllers \
  ros-humble-controller-manager ros-humble-xacro \
  ros-humble-robot-state-publisher ros-humble-rviz2 \
  ros-humble-ros-gz-sim ros-humble-ros-gz-bridge ros-humble-gz-ros2-control
```

### 3. 编译 ROS2 工作空间

```bash
cd ros2/xiaox_ws
colcon build --symlink-install
source install/setup.bash
```

### 4. 串口权限（真实硬件）

```bash
ls /dev/ttyACM*
sudo chmod 666 /dev/ttyACM0
```

## 其他使用方式

### Gazebo 仿真

```bash
source ros2/xiaox_ws/install/setup.bash
ros2 launch xiaox_bringup robot.launch.py use_gazebo:=true
```

### 仅启动驱动节点

```bash
source ros2/xiaox_ws/install/setup.bash
ros2 launch xiaox_driver driver.launch.py serial_port:=/dev/ttyACM0
```

### 单独启动键盘节点

```bash
source ros2/xiaox_ws/install/setup.bash
ros2 run xiaox_bringup xiaox_keyboard.py
```

键盘按键映射：

| 按键 | 功能 |
|------|------|
| `q` / `a` | Joint1 正转 / 反转 |
| `w` / `s` | Joint2 正转 / 反转 |
| `e` / `d` | Joint3 正转 / 反转 |
| `r` / `f` | Joint4 正转 / 反转 |
| `t` / `g` | Joint5 正转 / 反转 |
| `y` / `h` | Joint6 正转 / 反转 |
| `v` | 使能机械臂 |
| `b` | 关闭使能 |
| `z` | 回到 Home 位（全零） |
| `c` | 回到启动时的收缩位 |
| `p` | 查询硬件状态 |
| `x` | 退出 |

## Launch 参数说明

### `robot_moveit.launch.py`

| 参数 | 默认值 | 说明 |
|------|--------|------|
| `use_gazebo` | `false` | 是否使用 Gazebo 仿真 |
| `use_real_hardware` | `false` | 是否连接真实硬件 |
| `serial_port` | `/dev/ttyACM0` | 串口设备路径 |
| `baud_rate` | `115200` | 串口波特率 |
| `command_speed` | `180.0` | 关节运动速度（deg/s） |

### `robot.launch.py`（基础版）

除上表参数外，支持：

| 参数 | 默认值 | 说明 |
|------|--------|------|
| `control_file` | 空 | 控制脚本，可选 `xiaox_keyboard.py` |

## 常见问题

### 1. RViz 能规划但实机不动

先检查是否按了键盘 `v` 使能；`XiaoxSystem` 处于 `inactive` 时不会执行实机动作。

### 2. `/joint_states` 长时间不更新

检查 `arm_controller`、`joint_state_broadcaster` 是否正常，串口是否连接稳定。

### 3. 串口打开失败

确认设备名（如 `/dev/ttyACM0`）和权限（`chmod` 或加入 `dialout` 组）。

## 固件编译

如需重新编译 STM32 固件，安装工具链：

```bash
sudo apt install gcc-arm-none-eabi
```

### 42 / 35 步进电机固件

```bash
cd firmware/dummy-42motor-fw   # 或 dummy-35motor-fw
mkdir build && cd build
cmake ..
make
```

产物：`Ctrl-Step-STM32-fw.elf`、`.hex`、`.bin`

### 核心控制板固件

```bash
cd firmware/dummy-ref-core-fw
mkdir build && cd build
cmake ..
make
```

产物：`Core-STM32F4-fw.elf`、`.hex`、`.bin`

## 参考链接

- [Dummy Robot（稚晖君）](https://github.com/peng-zhihui/Dummy-Robot)
