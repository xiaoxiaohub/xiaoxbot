// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from xiaox_interfaces:srv/WriteJoints.idl
// generated code does not contain a copyright notice

#ifndef XIAOX_INTERFACES__SRV__DETAIL__WRITE_JOINTS__TRAITS_HPP_
#define XIAOX_INTERFACES__SRV__DETAIL__WRITE_JOINTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "xiaox_interfaces/srv/detail/write_joints__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace xiaox_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const WriteJoints_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: positions
  {
    if (msg.positions.size() == 0) {
      out << "positions: []";
    } else {
      out << "positions: [";
      size_t pending_items = msg.positions.size();
      for (auto item : msg.positions) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: velocities
  {
    if (msg.velocities.size() == 0) {
      out << "velocities: []";
    } else {
      out << "velocities: [";
      size_t pending_items = msg.velocities.size();
      for (auto item : msg.velocities) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const WriteJoints_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: positions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.positions.size() == 0) {
      out << "positions: []\n";
    } else {
      out << "positions:\n";
      for (auto item : msg.positions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: velocities
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.velocities.size() == 0) {
      out << "velocities: []\n";
    } else {
      out << "velocities:\n";
      for (auto item : msg.velocities) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WriteJoints_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace xiaox_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use xiaox_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const xiaox_interfaces::srv::WriteJoints_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  xiaox_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use xiaox_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const xiaox_interfaces::srv::WriteJoints_Request & msg)
{
  return xiaox_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<xiaox_interfaces::srv::WriteJoints_Request>()
{
  return "xiaox_interfaces::srv::WriteJoints_Request";
}

template<>
inline const char * name<xiaox_interfaces::srv::WriteJoints_Request>()
{
  return "xiaox_interfaces/srv/WriteJoints_Request";
}

template<>
struct has_fixed_size<xiaox_interfaces::srv::WriteJoints_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<xiaox_interfaces::srv::WriteJoints_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<xiaox_interfaces::srv::WriteJoints_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace xiaox_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const WriteJoints_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const WriteJoints_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WriteJoints_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace xiaox_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use xiaox_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const xiaox_interfaces::srv::WriteJoints_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  xiaox_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use xiaox_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const xiaox_interfaces::srv::WriteJoints_Response & msg)
{
  return xiaox_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<xiaox_interfaces::srv::WriteJoints_Response>()
{
  return "xiaox_interfaces::srv::WriteJoints_Response";
}

template<>
inline const char * name<xiaox_interfaces::srv::WriteJoints_Response>()
{
  return "xiaox_interfaces/srv/WriteJoints_Response";
}

template<>
struct has_fixed_size<xiaox_interfaces::srv::WriteJoints_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<xiaox_interfaces::srv::WriteJoints_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<xiaox_interfaces::srv::WriteJoints_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<xiaox_interfaces::srv::WriteJoints>()
{
  return "xiaox_interfaces::srv::WriteJoints";
}

template<>
inline const char * name<xiaox_interfaces::srv::WriteJoints>()
{
  return "xiaox_interfaces/srv/WriteJoints";
}

template<>
struct has_fixed_size<xiaox_interfaces::srv::WriteJoints>
  : std::integral_constant<
    bool,
    has_fixed_size<xiaox_interfaces::srv::WriteJoints_Request>::value &&
    has_fixed_size<xiaox_interfaces::srv::WriteJoints_Response>::value
  >
{
};

template<>
struct has_bounded_size<xiaox_interfaces::srv::WriteJoints>
  : std::integral_constant<
    bool,
    has_bounded_size<xiaox_interfaces::srv::WriteJoints_Request>::value &&
    has_bounded_size<xiaox_interfaces::srv::WriteJoints_Response>::value
  >
{
};

template<>
struct is_service<xiaox_interfaces::srv::WriteJoints>
  : std::true_type
{
};

template<>
struct is_service_request<xiaox_interfaces::srv::WriteJoints_Request>
  : std::true_type
{
};

template<>
struct is_service_response<xiaox_interfaces::srv::WriteJoints_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // XIAOX_INTERFACES__SRV__DETAIL__WRITE_JOINTS__TRAITS_HPP_
