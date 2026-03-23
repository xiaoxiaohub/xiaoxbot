// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from xiaox_interfaces:srv/WriteJoints.idl
// generated code does not contain a copyright notice

#ifndef XIAOX_INTERFACES__SRV__DETAIL__WRITE_JOINTS__STRUCT_H_
#define XIAOX_INTERFACES__SRV__DETAIL__WRITE_JOINTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'positions'
// Member 'velocities'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/WriteJoints in the package xiaox_interfaces.
typedef struct xiaox_interfaces__srv__WriteJoints_Request
{
  rosidl_runtime_c__double__Sequence positions;
  rosidl_runtime_c__double__Sequence velocities;
} xiaox_interfaces__srv__WriteJoints_Request;

// Struct for a sequence of xiaox_interfaces__srv__WriteJoints_Request.
typedef struct xiaox_interfaces__srv__WriteJoints_Request__Sequence
{
  xiaox_interfaces__srv__WriteJoints_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} xiaox_interfaces__srv__WriteJoints_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/WriteJoints in the package xiaox_interfaces.
typedef struct xiaox_interfaces__srv__WriteJoints_Response
{
  bool success;
  rosidl_runtime_c__String message;
} xiaox_interfaces__srv__WriteJoints_Response;

// Struct for a sequence of xiaox_interfaces__srv__WriteJoints_Response.
typedef struct xiaox_interfaces__srv__WriteJoints_Response__Sequence
{
  xiaox_interfaces__srv__WriteJoints_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} xiaox_interfaces__srv__WriteJoints_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // XIAOX_INTERFACES__SRV__DETAIL__WRITE_JOINTS__STRUCT_H_
