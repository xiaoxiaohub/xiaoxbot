// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from xiaox_interfaces:srv/WriteJoints.idl
// generated code does not contain a copyright notice

#ifndef XIAOX_INTERFACES__SRV__DETAIL__WRITE_JOINTS__BUILDER_HPP_
#define XIAOX_INTERFACES__SRV__DETAIL__WRITE_JOINTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "xiaox_interfaces/srv/detail/write_joints__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace xiaox_interfaces
{

namespace srv
{

namespace builder
{

class Init_WriteJoints_Request_velocities
{
public:
  explicit Init_WriteJoints_Request_velocities(::xiaox_interfaces::srv::WriteJoints_Request & msg)
  : msg_(msg)
  {}
  ::xiaox_interfaces::srv::WriteJoints_Request velocities(::xiaox_interfaces::srv::WriteJoints_Request::_velocities_type arg)
  {
    msg_.velocities = std::move(arg);
    return std::move(msg_);
  }

private:
  ::xiaox_interfaces::srv::WriteJoints_Request msg_;
};

class Init_WriteJoints_Request_positions
{
public:
  Init_WriteJoints_Request_positions()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WriteJoints_Request_velocities positions(::xiaox_interfaces::srv::WriteJoints_Request::_positions_type arg)
  {
    msg_.positions = std::move(arg);
    return Init_WriteJoints_Request_velocities(msg_);
  }

private:
  ::xiaox_interfaces::srv::WriteJoints_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::xiaox_interfaces::srv::WriteJoints_Request>()
{
  return xiaox_interfaces::srv::builder::Init_WriteJoints_Request_positions();
}

}  // namespace xiaox_interfaces


namespace xiaox_interfaces
{

namespace srv
{

namespace builder
{

class Init_WriteJoints_Response_message
{
public:
  explicit Init_WriteJoints_Response_message(::xiaox_interfaces::srv::WriteJoints_Response & msg)
  : msg_(msg)
  {}
  ::xiaox_interfaces::srv::WriteJoints_Response message(::xiaox_interfaces::srv::WriteJoints_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::xiaox_interfaces::srv::WriteJoints_Response msg_;
};

class Init_WriteJoints_Response_success
{
public:
  Init_WriteJoints_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WriteJoints_Response_message success(::xiaox_interfaces::srv::WriteJoints_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_WriteJoints_Response_message(msg_);
  }

private:
  ::xiaox_interfaces::srv::WriteJoints_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::xiaox_interfaces::srv::WriteJoints_Response>()
{
  return xiaox_interfaces::srv::builder::Init_WriteJoints_Response_success();
}

}  // namespace xiaox_interfaces

#endif  // XIAOX_INTERFACES__SRV__DETAIL__WRITE_JOINTS__BUILDER_HPP_
