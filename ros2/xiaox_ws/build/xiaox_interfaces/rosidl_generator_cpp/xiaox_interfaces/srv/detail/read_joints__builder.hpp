// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from xiaox_interfaces:srv/ReadJoints.idl
// generated code does not contain a copyright notice

#ifndef XIAOX_INTERFACES__SRV__DETAIL__READ_JOINTS__BUILDER_HPP_
#define XIAOX_INTERFACES__SRV__DETAIL__READ_JOINTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "xiaox_interfaces/srv/detail/read_joints__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace xiaox_interfaces
{

namespace srv
{

namespace builder
{

class Init_ReadJoints_Request_action
{
public:
  Init_ReadJoints_Request_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::xiaox_interfaces::srv::ReadJoints_Request action(::xiaox_interfaces::srv::ReadJoints_Request::_action_type arg)
  {
    msg_.action = std::move(arg);
    return std::move(msg_);
  }

private:
  ::xiaox_interfaces::srv::ReadJoints_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::xiaox_interfaces::srv::ReadJoints_Request>()
{
  return xiaox_interfaces::srv::builder::Init_ReadJoints_Request_action();
}

}  // namespace xiaox_interfaces


namespace xiaox_interfaces
{

namespace srv
{

namespace builder
{

class Init_ReadJoints_Response_velocities
{
public:
  explicit Init_ReadJoints_Response_velocities(::xiaox_interfaces::srv::ReadJoints_Response & msg)
  : msg_(msg)
  {}
  ::xiaox_interfaces::srv::ReadJoints_Response velocities(::xiaox_interfaces::srv::ReadJoints_Response::_velocities_type arg)
  {
    msg_.velocities = std::move(arg);
    return std::move(msg_);
  }

private:
  ::xiaox_interfaces::srv::ReadJoints_Response msg_;
};

class Init_ReadJoints_Response_positions
{
public:
  explicit Init_ReadJoints_Response_positions(::xiaox_interfaces::srv::ReadJoints_Response & msg)
  : msg_(msg)
  {}
  Init_ReadJoints_Response_velocities positions(::xiaox_interfaces::srv::ReadJoints_Response::_positions_type arg)
  {
    msg_.positions = std::move(arg);
    return Init_ReadJoints_Response_velocities(msg_);
  }

private:
  ::xiaox_interfaces::srv::ReadJoints_Response msg_;
};

class Init_ReadJoints_Response_message
{
public:
  explicit Init_ReadJoints_Response_message(::xiaox_interfaces::srv::ReadJoints_Response & msg)
  : msg_(msg)
  {}
  Init_ReadJoints_Response_positions message(::xiaox_interfaces::srv::ReadJoints_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_ReadJoints_Response_positions(msg_);
  }

private:
  ::xiaox_interfaces::srv::ReadJoints_Response msg_;
};

class Init_ReadJoints_Response_success
{
public:
  Init_ReadJoints_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ReadJoints_Response_message success(::xiaox_interfaces::srv::ReadJoints_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ReadJoints_Response_message(msg_);
  }

private:
  ::xiaox_interfaces::srv::ReadJoints_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::xiaox_interfaces::srv::ReadJoints_Response>()
{
  return xiaox_interfaces::srv::builder::Init_ReadJoints_Response_success();
}

}  // namespace xiaox_interfaces

#endif  // XIAOX_INTERFACES__SRV__DETAIL__READ_JOINTS__BUILDER_HPP_
