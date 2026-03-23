// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from xiaox_interfaces:srv/InitDevice.idl
// generated code does not contain a copyright notice

#ifndef XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__STRUCT_H_
#define XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'action'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/InitDevice in the package xiaox_interfaces.
typedef struct xiaox_interfaces__srv__InitDevice_Request
{
  rosidl_runtime_c__String action;
} xiaox_interfaces__srv__InitDevice_Request;

// Struct for a sequence of xiaox_interfaces__srv__InitDevice_Request.
typedef struct xiaox_interfaces__srv__InitDevice_Request__Sequence
{
  xiaox_interfaces__srv__InitDevice_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} xiaox_interfaces__srv__InitDevice_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/InitDevice in the package xiaox_interfaces.
typedef struct xiaox_interfaces__srv__InitDevice_Response
{
  bool success;
  rosidl_runtime_c__String message;
} xiaox_interfaces__srv__InitDevice_Response;

// Struct for a sequence of xiaox_interfaces__srv__InitDevice_Response.
typedef struct xiaox_interfaces__srv__InitDevice_Response__Sequence
{
  xiaox_interfaces__srv__InitDevice_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} xiaox_interfaces__srv__InitDevice_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__STRUCT_H_
