#ifndef XIAOX_HARDWARE__XIAOX_HARDWARE_HPP_
#define XIAOX_HARDWARE__XIAOX_HARDWARE_HPP_

#include <memory>
#include <string>
#include <vector>

#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp"
#include "xiaox_interfaces/srv/init_device.hpp"
#include "xiaox_interfaces/srv/read_joints.hpp"
#include "xiaox_interfaces/srv/write_joints.hpp"

namespace xiaox_hardware
{

using CallbackReturn =
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

class XiaoxHardware : public hardware_interface::SystemInterface
{
public:
  CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override;

  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  CallbackReturn on_activate(const rclcpp_lifecycle::State &) override;
  CallbackReturn on_deactivate(const rclcpp_lifecycle::State &) override;
  CallbackReturn on_cleanup(const rclcpp_lifecycle::State &) override;
  CallbackReturn on_shutdown(const rclcpp_lifecycle::State &) override;
  CallbackReturn on_error(const rclcpp_lifecycle::State &) override;

  hardware_interface::return_type read(
    const rclcpp::Time &,
    const rclcpp::Duration &) override;

  hardware_interface::return_type write(
    const rclcpp::Time &,
    const rclcpp::Duration &) override;

private:
  bool wait_for_services();
  void initialize_vectors();
  bool initialize_joint_directions();
  bool refresh_feedback(bool reset_commands);
  bool init_device(const std::string & action);
  bool read_joints(std::vector<double> & positions, std::vector<double> & velocities);
  bool write_joints(
    const std::vector<double> & positions,
    const std::vector<double> & velocities);
  double clamp_deg(double value, size_t joint_idx) const;
  double clamp_joint_command_deg(double joint_command_rad, size_t joint_idx) const;
  double joint_to_actuator_deg(double joint_deg, size_t joint_idx) const;
  double actuator_to_joint_rad(double actuator_deg, size_t joint_idx) const;

  static constexpr size_t kNumJoints = 6;
  static constexpr double kDegToRad = M_PI / 180.0;
  static constexpr double kRadToDeg = 180.0 / M_PI;

  struct JointLimit
  {
    double min_deg;
    double max_deg;
  };

  static constexpr JointLimit kJointLimits[kNumJoints] = {
    {-170.0, 170.0},
    {-73.0, 90.0},
    {-55.0, 90.0},
    {-180.0, 180.0},
    {-120.0, 120.0},
    {-720.0, 720.0},
  };

  std::vector<double> actuator_pos_commands_;
  std::vector<double> actuator_vel_commands_;
  std::vector<double> actuator_positions_;
  std::vector<double> actuator_velocities_;
  std::vector<double> joint_positions_;
  std::vector<double> joint_velocities_;
  std::vector<double> joint_position_commands_;
  std::vector<double> joint_directions_;

  std::shared_ptr<rclcpp::Node> node_;
  rclcpp::Client<xiaox_interfaces::srv::InitDevice>::SharedPtr init_device_client_;
  rclcpp::Client<xiaox_interfaces::srv::WriteJoints>::SharedPtr write_joints_client_;
  rclcpp::Client<xiaox_interfaces::srv::ReadJoints>::SharedPtr read_joints_client_;
};

}  // namespace xiaox_hardware

#endif  // XIAOX_HARDWARE__XIAOX_HARDWARE_HPP_
