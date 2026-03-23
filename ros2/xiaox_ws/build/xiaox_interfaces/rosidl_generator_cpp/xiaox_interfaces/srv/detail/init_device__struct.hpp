// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from xiaox_interfaces:srv/InitDevice.idl
// generated code does not contain a copyright notice

#ifndef XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__STRUCT_HPP_
#define XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__xiaox_interfaces__srv__InitDevice_Request __attribute__((deprecated))
#else
# define DEPRECATED__xiaox_interfaces__srv__InitDevice_Request __declspec(deprecated)
#endif

namespace xiaox_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct InitDevice_Request_
{
  using Type = InitDevice_Request_<ContainerAllocator>;

  explicit InitDevice_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = "";
    }
  }

  explicit InitDevice_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : action(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = "";
    }
  }

  // field types and members
  using _action_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _action_type action;

  // setters for named parameter idiom
  Type & set__action(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->action = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__xiaox_interfaces__srv__InitDevice_Request
    std::shared_ptr<xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__xiaox_interfaces__srv__InitDevice_Request
    std::shared_ptr<xiaox_interfaces::srv::InitDevice_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const InitDevice_Request_ & other) const
  {
    if (this->action != other.action) {
      return false;
    }
    return true;
  }
  bool operator!=(const InitDevice_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct InitDevice_Request_

// alias to use template instance with default allocator
using InitDevice_Request =
  xiaox_interfaces::srv::InitDevice_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace xiaox_interfaces


#ifndef _WIN32
# define DEPRECATED__xiaox_interfaces__srv__InitDevice_Response __attribute__((deprecated))
#else
# define DEPRECATED__xiaox_interfaces__srv__InitDevice_Response __declspec(deprecated)
#endif

namespace xiaox_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct InitDevice_Response_
{
  using Type = InitDevice_Response_<ContainerAllocator>;

  explicit InitDevice_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit InitDevice_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__xiaox_interfaces__srv__InitDevice_Response
    std::shared_ptr<xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__xiaox_interfaces__srv__InitDevice_Response
    std::shared_ptr<xiaox_interfaces::srv::InitDevice_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const InitDevice_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const InitDevice_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct InitDevice_Response_

// alias to use template instance with default allocator
using InitDevice_Response =
  xiaox_interfaces::srv::InitDevice_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace xiaox_interfaces

namespace xiaox_interfaces
{

namespace srv
{

struct InitDevice
{
  using Request = xiaox_interfaces::srv::InitDevice_Request;
  using Response = xiaox_interfaces::srv::InitDevice_Response;
};

}  // namespace srv

}  // namespace xiaox_interfaces

#endif  // XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__STRUCT_HPP_
