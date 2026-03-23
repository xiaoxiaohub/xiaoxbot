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

### 1. 基础项目参考

- [Dummy Robot（稚晖君）](https://github.com/peng-zhihui/Dummy-Robot) - 原始开源六轴机械臂项目
- [木子晓汶dummy](https://gitee.com/switchpi/dummy) - Gitee镜像版本
- [木子晓汶dummy2](https://www.bilibili.com/video/BV1WJNgeBEqe/?spm_id_from=333.1391.0.0&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1) - 后续版本视频

### 2. ROS2基础教程

#### 在线文档
- [动手学ROS2](https://fishros.com/d2lros2foxy/#/)
- [古月居在线文档](https://book.guyuehome.com/)
- [古月居官网](https://www.guyuehome.com/)
- [ROS培训教程](https://tr-ros-tutorial.readthedocs.io/zh-cn/latest/_source/simulation/gazebo_and_rviz.html)
- [赵虚左的在线文档](https://www.autolabor.com.cn/book/ROSTutorials/)
- [知乎系列：ros2-control教程(0) - 高度解耦的ROS2控制框架](https://zhuanlan.zhihu.com/p/682574108)

#### B站视频
- [赵虚左的B站系列视频](https://www.bilibili.com/video/BV15V4y1P744/?spm_id_from=333.1391.0.0&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)
- [古月居GYH的系列视频](https://www.bilibili.com/video/BV1zt411G7Vn?spm_id_from=333.788.videopod.episodes&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1&p=11)
- [古月居早期ROS理论教程（提取码：c2eh）](https://pan.baidu.com/s/1wB7taUcgUk_CeRL2n9SlAw)
- [黑马程序员 - 零代码全栈ROS2视频](https://www.bilibili.com/video/BV131ZuBdEMZ/?spm_id_from=333.1391.0.0&p=30&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)
- [鱼香ROS机器人系列视频](https://www.bilibili.com/video/BV1kQAqeCEE9/?spm_id_from=333.1391.0.0&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)
- [后来老师系列视频](https://www.bilibili.com/video/BV1SGYRzBEEm?spm_id_from=333.788.videopod.sections&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)

#### GitHub资源
- [动手学ROS2课程配套教程](https://github.com/fishros/d2l-ros2)
- [《ROS机器人开发实践》源码](https://github.com/JerryRain/rosexplore_ws/tree/master/src)

### 3. ros2_control框架教程

- [B站WMGIII - ros2_control教程](https://www.bilibili.com/video/BV1ku411G7UR/?spm_id_from=333.1391.0.0&p=2&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)
- [博客园 - ros_control中hardware_interface教程](https://www.cnblogs.com/slgkaifa/p/19165997)

### 4. MoveIt2与仿真教程

- [ROS2+MoveIt2+Gazebo中的仿真](https://blog.csdn.net/qq_45253884/article/details/146335840)
- [在ROS2中，通过MoveIt2控制Gazebo中的自定义机械手](https://blog.csdn.net/joyopirate/article/details/129424607)
- [MoveIt2学习笔记（一）- MoveIt + Gazebo + RViz 的连接](https://blog.csdn.net/qq_36674060/article/details/144629785)
- [从零开始基于ROS-Noetic使用gazebo操控真实机械臂](https://blog.csdn.net/m0_74713645/article/details/143266300)

### 5. 开源机械臂项目参考

#### 相关的Dummy机械臂项目
- [dummy_ros2_driver](https://github.com/yeyiru/dummy_ros2_driver)
- [dummy_robot_description](https://github.com/aod321/dummy_robot_description)
- [Safety_First_Studio](https://github.com/StephenGu010/Safety_First_Studio) - 附带B站视频：[【Dummy机械臂】大四技术宅开发机械臂+固件+上位机](https://www.bilibili.com/video/BV1EufNBZEBH/?spm_id_from=333.1391.0.0&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)

#### 力控机械臂项目
- [livelybot_arm - 高擎生态可力控六轴机械臂](https://github.com/liuyt/livelybot_arm/tree/main/livelybot_new) - 对应B站视频：[晴晴机械臂B站视频](https://www.bilibili.com/video/BV1jE421j7Mz/?spm_id_from=333.1391.0.0&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)
- [light_lift_arm_6dof - 3D打印六轴力控机械臂](https://gitee.com/qingqing-gaq/light_lift_arm_6dof.git) - 对应B站视频：[【开源】3D打印六轴力控机械臂-开源地址在视频简介](https://www.bilibili.com/video/BV1sSoCYmEzG?spm_id_from=333.788.videopod.sections&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)

#### 其他机器人平台
- [wpr_simulation2](https://github.com/6-robot/wpr_simulation2)
- [fishbot](https://github.com/fishros/fishbot)

### 6. B站系列课程视频

- [B站狮头 - 基于ROS2的开源EtherCAT总线机械臂控制系统](https://www.bilibili.com/video/BV15X4y1t7XY/?spm_id_from=333.1391.0.0&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)
- [B站晴晴的机械臂系列视频](https://www.bilibili.com/video/BV1jE421j7Mz/?spm_id_from=333.1391.0.0&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)
- [B站哈萨克斯坦x系列视频](https://www.bilibili.com/video/BV1zH4y1n7yS/?spm_id_from=333.1387.upload.video_card.click&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)
- [B站机器人工匠阿杰系列视频](https://www.bilibili.com/video/BV1de4y1h7H5?spm_id_from=333.788.videopod.sections&vd_source=c22c0bdbee7d0f45e072fba519a4b9f1)

