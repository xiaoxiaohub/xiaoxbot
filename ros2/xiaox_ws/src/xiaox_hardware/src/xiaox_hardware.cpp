#include "xiaox_hardware/xiaox_hardware.hpp"

#include <algorithm>
#include <cmath>
#include <exception>
#include <memory>
#include <string>
#include <vector>

#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "pluginlib/class_list_macros.hpp"

namespace xiaox_hardware
{

CallbackReturn XiaoxHardware::on_init(const hardware_interface::HardwareInfo & info)
{
  if (hardware_interface::SystemInterface::on_init(info) != CallbackReturn::SUCCESS) {
    return CallbackReturn::ERROR;
  }

  if (info_.joints.size() != kNumJoints) {
    RCLCPP_ERROR(
      rclcpp::get_logger("XiaoxHardware"),
      "Expected %zu joints, got %zu",
      kNumJoints,
      info_.joints.size());
    return CallbackReturn::ERROR;
  }

  initialize_vectors();
  if (!initialize_joint_directions()) {
    return CallbackReturn::ERROR;
  }

  node_ = std::make_shared<rclcpp::Node>("xiaox_hardware_node");
  init_device_client_ =
    node_->create_client<xiaox_interfaces::srv::InitDevice>("init_device");
  write_joints_client_ =
    node_->create_client<xiaox_interfaces::srv::WriteJoints>("write_joints");
  read_joints_client_ =
    node_->create_client<xiaox_interfaces::srv::ReadJoints>("read_joints");

  if (!wait_for_services()) {
    return CallbackReturn::ERROR;
  }

  if (!init_device("start")) {
    return CallbackReturn::ERROR;
  }

  RCLCPP_INFO(rclcpp::get_logger("XiaoxHardware"), "Initialized");
  return CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> XiaoxHardware::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;
  for (size_t i = 0; i < info_.joints.size(); ++i) {
    state_interfaces.emplace_back(
      info_.joints[i].name,
      hardware_interface::HW_IF_POSITION,
      &joint_positions_[i]);
    state_interfaces.emplace_back(
      info_.joints[i].name,
      hardware_interface::HW_IF_VELOCITY,
      &joint_velocities_[i]);
  }
  return state_interfaces;
}

std::vector<hardware_interface::CommandInterface> XiaoxHardware::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;
  for (size_t i = 0; i < info_.joints.size(); ++i) {
    command_interfaces.emplace_back(
      info_.joints[i].name,
      hardware_interface::HW_IF_POSITION,
      &joint_position_commands_[i]);
  }
  return command_interfaces;
}

CallbackReturn XiaoxHardware::on_activate(const rclcpp_lifecycle::State &)
{
  if (!init_device("active")) {
    return CallbackReturn::ERROR;
  }

  if (!refresh_feedback(true)) {
    return CallbackReturn::ERROR;
  }

  RCLCPP_INFO(rclcpp::get_logger("XiaoxHardware"), "Activated");
  return CallbackReturn::SUCCESS;
}

CallbackReturn XiaoxHardware::on_deactivate(const rclcpp_lifecycle::State &)
{
  init_device("deactive");
  RCLCPP_INFO(rclcpp::get_logger("XiaoxHardware"), "Deactivated");
  return CallbackReturn::SUCCESS;
}

CallbackReturn XiaoxHardware::on_cleanup(const rclcpp_lifecycle::State &)
{
  init_device("stop");
  return CallbackReturn::SUCCESS;
}

CallbackReturn XiaoxHardware::on_shutdown(const rclcpp_lifecycle::State &)
{
  init_device("stop");
  return CallbackReturn::SUCCESS;
}

CallbackReturn XiaoxHardware::on_error(const rclcpp_lifecycle::State &)
{
  init_device("stop");
  return CallbackReturn::SUCCESS;
}

hardware_interface::return_type XiaoxHardware::read(
  const rclcpp::Time &,
  const rclcpp::Duration &)
{
  refresh_feedback(false);
  return hardware_interface::return_type::OK;
}

hardware_interface::return_type XiaoxHardware::write(
  const rclcpp::Time &,
  const rclcpp::Duration &)
{
  for (size_t i = 0; i < info_.joints.size(); ++i) {
    const double joint_command_deg = clamp_joint_command_deg(joint_position_commands_[i], i);
    actuator_pos_commands_[i] = joint_to_actuator_deg(joint_command_deg, i);
    actuator_vel_commands_[i] = 0.0;
  }

  if (!write_joints(actuator_pos_commands_, actuator_vel_commands_)) {
    return hardware_interface::return_type::ERROR;
  }

  return hardware_interface::return_type::OK;
}

bool XiaoxHardware::wait_for_services()
{
  if (!init_device_client_->wait_for_service(std::chrono::seconds(5))) {
    RCLCPP_ERROR(rclcpp::get_logger("XiaoxHardware"), "init_device is unavailable");
    return false;
  }

  if (!write_joints_client_->wait_for_service(std::chrono::seconds(5))) {
    RCLCPP_ERROR(rclcpp::get_logger("XiaoxHardware"), "write_joints is unavailable");
    return false;
  }

  if (!read_joints_client_->wait_for_service(std::chrono::seconds(5))) {
    RCLCPP_ERROR(rclcpp::get_logger("XiaoxHardware"), "read_joints is unavailable");
    return false;
  }

  return true;
}

void XiaoxHardware::initialize_vectors()
{
  actuator_pos_commands_.assign(kNumJoints, 0.0);
  actuator_vel_commands_.assign(kNumJoints, 0.0);
  actuator_positions_.assign(kNumJoints, 0.0);
  actuator_velocities_.assign(kNumJoints, 0.0);
  joint_positions_.assign(kNumJoints, 0.0);
  joint_velocities_.assign(kNumJoints, 0.0);
  joint_position_commands_.assign(kNumJoints, 0.0);
}

bool XiaoxHardware::initialize_joint_directions()
{
  joint_directions_.assign(kNumJoints, 1.0);

  for (size_t i = 0; i < info_.joints.size(); ++i) {
    const auto parameter_it = info_.joints[i].parameters.find("direction");
    if (parameter_it == info_.joints[i].parameters.end()) {
      continue;
    }

    try {
      const double direction = std::stod(parameter_it->second);
      if (direction == 0.0) {
        RCLCPP_ERROR(
          rclcpp::get_logger("XiaoxHardware"),
          "Joint %s has invalid direction 0",
          info_.joints[i].name.c_str());
        return false;
      }
      joint_directions_[i] = direction > 0.0 ? 1.0 : -1.0;
    } catch (const std::exception & ex) {
      RCLCPP_ERROR(
        rclcpp::get_logger("XiaoxHardware"),
        "Failed to parse direction for joint %s: %s",
        info_.joints[i].name.c_str(),
        ex.what());
      return false;
    }
  }

  RCLCPP_INFO(
    rclcpp::get_logger("XiaoxHardware"),
    "Joint directions loaded as [%.0f, %.0f, %.0f, %.0f, %.0f, %.0f]",
    joint_directions_[0],
    joint_directions_[1],
    joint_directions_[2],
    joint_directions_[3],
    joint_directions_[4],
    joint_directions_[5]);

  return true;
}

bool XiaoxHardware::refresh_feedback(bool reset_commands)
{
  if (!read_joints(actuator_positions_, actuator_velocities_)) {
    return false;
  }

  for (size_t i = 0; i < info_.joints.size(); ++i) {
    joint_positions_[i] = actuator_to_joint_rad(actuator_positions_[i], i);
    joint_velocities_[i] = actuator_to_joint_rad(actuator_velocities_[i], i);
    if (reset_commands) {
      joint_position_commands_[i] = joint_positions_[i];
    }
  }

  return true;
}

bool XiaoxHardware::init_device(const std::string & action)
{
  auto request = std::make_shared<xiaox_interfaces::srv::InitDevice::Request>();
  request->action = action;

  auto future = init_device_client_->async_send_request(request);
  if (rclcpp::spin_until_future_complete(node_, future) != rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_ERROR(
      rclcpp::get_logger("XiaoxHardware"),
      "Failed to call init_device with action %s",
      action.c_str());
    return false;
  }

  const auto result = future.get();
  if (!result->success) {
    RCLCPP_ERROR(
      rclcpp::get_logger("XiaoxHardware"),
      "init_device(%s) failed: %s",
      action.c_str(),
      result->message.c_str());
    return false;
  }

  return true;
}

bool XiaoxHardware::read_joints(
  std::vector<double> & positions,
  std::vector<double> & velocities)
{
  auto request = std::make_shared<xiaox_interfaces::srv::ReadJoints::Request>();
  request->action = "read";

  auto future = read_joints_client_->async_send_request(request);
  if (rclcpp::spin_until_future_complete(node_, future) != rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_ERROR(rclcpp::get_logger("XiaoxHardware"), "Failed to call read_joints");
    return false;
  }

  const auto result = future.get();
  if (!result->success) {
    RCLCPP_WARN(
      rclcpp::get_logger("XiaoxHardware"),
      "read_joints failed: %s",
      result->message.c_str());
    return false;
  }

  if (result->positions.size() != kNumJoints || result->velocities.size() != kNumJoints) {
    RCLCPP_ERROR(
      rclcpp::get_logger("XiaoxHardware"),
      "Unexpected feedback size: pos=%zu vel=%zu",
      result->positions.size(),
      result->velocities.size());
    return false;
  }

  positions = result->positions;
  velocities = result->velocities;
  return true;
}

bool XiaoxHardware::write_joints(
  const std::vector<double> & positions,
  const std::vector<double> & velocities)
{
  auto request = std::make_shared<xiaox_interfaces::srv::WriteJoints::Request>();
  request->positions = positions;
  request->velocities = velocities;

  auto future = write_joints_client_->async_send_request(request);
  if (rclcpp::spin_until_future_complete(node_, future) != rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_ERROR(rclcpp::get_logger("XiaoxHardware"), "Failed to call write_joints");
    return false;
  }

  const auto result = future.get();
  if (!result->success) {
    RCLCPP_ERROR(
      rclcpp::get_logger("XiaoxHardware"),
      "write_joints failed: %s",
      result->message.c_str());
    return false;
  }

  return true;
}

double XiaoxHardware::clamp_deg(double value, size_t joint_idx) const
{
  return std::clamp(value, kJointLimits[joint_idx].min_deg, kJointLimits[joint_idx].max_deg);
}

double XiaoxHardware::clamp_joint_command_deg(double joint_command_rad, size_t joint_idx) const
{
  return clamp_deg(joint_command_rad * kRadToDeg, joint_idx);
}

double XiaoxHardware::joint_to_actuator_deg(double joint_deg, size_t joint_idx) const
{
  double actuator_deg = joint_deg * joint_directions_[joint_idx];
  if (joint_idx == 2) {
    actuator_deg += 90.0;
  }
  return actuator_deg;
}

double XiaoxHardware::actuator_to_joint_rad(double actuator_deg, size_t joint_idx) const
{
  double joint_deg = actuator_deg * joint_directions_[joint_idx];
  if (joint_idx == 2) {
    joint_deg -= 90.0;
  }
  return joint_deg * kDegToRad;
}

}  // namespace xiaox_hardware

PLUGINLIB_EXPORT_CLASS(xiaox_hardware::XiaoxHardware, hardware_interface::SystemInterface)
