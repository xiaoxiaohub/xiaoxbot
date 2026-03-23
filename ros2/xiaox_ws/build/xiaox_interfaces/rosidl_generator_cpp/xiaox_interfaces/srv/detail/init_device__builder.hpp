// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from xiaox_interfaces:srv/InitDevice.idl
// generated code does not contain a copyright notice

#ifndef XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__BUILDER_HPP_
#define XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "xiaox_interfaces/srv/detail/init_device__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace xiaox_interfaces
{

namespace srv
{

namespace builder
{

class Init_InitDevice_Request_action
{
public:
  Init_InitDevice_Request_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::xiaox_interfaces::srv::InitDevice_Request action(::xiaox_interfaces::srv::InitDevice_Request::_action_type arg)
  {
    msg_.action = std::move(arg);
    return std::move(msg_);
  }

private:
  ::xiaox_interfaces::srv::InitDevice_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::xiaox_interfaces::srv::InitDevice_Request>()
{
  return xiaox_interfaces::srv::builder::Init_InitDevice_Request_action();
}

}  // namespace xiaox_interfaces


namespace xiaox_interfaces
{

namespace srv
{

namespace builder
{

class Init_InitDevice_Response_message
{
public:
  explicit Init_InitDevice_Response_message(::xiaox_interfaces::srv::InitDevice_Response & msg)
  : msg_(msg)
  {}
  ::xiaox_interfaces::srv::InitDevice_Response message(::xiaox_interfaces::srv::InitDevice_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::xiaox_interfaces::srv::InitDevice_Response msg_;
};

class Init_InitDevice_Response_success
{
public:
  Init_InitDevice_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InitDevice_Response_message success(::xiaox_interfaces::srv::InitDevice_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_InitDevice_Response_message(msg_);
  }

private:
  ::xiaox_interfaces::srv::InitDevice_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::xiaox_interfaces::srv::InitDevice_Response>()
{
  return xiaox_interfaces::srv::builder::Init_InitDevice_Response_success();
}

}  // namespace xiaox_interfaces

#endif  // XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__BUILDER_HPP_
