// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from xiaox_interfaces:srv/WriteJoints.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "xiaox_interfaces/srv/detail/write_joints__rosidl_typesupport_introspection_c.h"
#include "xiaox_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "xiaox_interfaces/srv/detail/write_joints__functions.h"
#include "xiaox_interfaces/srv/detail/write_joints__struct.h"


// Include directives for member types
// Member `positions`
// Member `velocities`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  xiaox_interfaces__srv__WriteJoints_Request__init(message_memory);
}

void xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_fini_function(void * message_memory)
{
  xiaox_interfaces__srv__WriteJoints_Request__fini(message_memory);
}

size_t xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__size_function__WriteJoints_Request__positions(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_const_function__WriteJoints_Request__positions(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_function__WriteJoints_Request__positions(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__fetch_function__WriteJoints_Request__positions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_const_function__WriteJoints_Request__positions(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__assign_function__WriteJoints_Request__positions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_function__WriteJoints_Request__positions(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__resize_function__WriteJoints_Request__positions(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__size_function__WriteJoints_Request__velocities(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_const_function__WriteJoints_Request__velocities(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_function__WriteJoints_Request__velocities(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__fetch_function__WriteJoints_Request__velocities(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_const_function__WriteJoints_Request__velocities(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__assign_function__WriteJoints_Request__velocities(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_function__WriteJoints_Request__velocities(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__resize_function__WriteJoints_Request__velocities(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_message_member_array[2] = {
  {
    "positions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(xiaox_interfaces__srv__WriteJoints_Request, positions),  // bytes offset in struct
    NULL,  // default value
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__size_function__WriteJoints_Request__positions,  // size() function pointer
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_const_function__WriteJoints_Request__positions,  // get_const(index) function pointer
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_function__WriteJoints_Request__positions,  // get(index) function pointer
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__fetch_function__WriteJoints_Request__positions,  // fetch(index, &value) function pointer
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__assign_function__WriteJoints_Request__positions,  // assign(index, value) function pointer
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__resize_function__WriteJoints_Request__positions  // resize(index) function pointer
  },
  {
    "velocities",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(xiaox_interfaces__srv__WriteJoints_Request, velocities),  // bytes offset in struct
    NULL,  // default value
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__size_function__WriteJoints_Request__velocities,  // size() function pointer
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_const_function__WriteJoints_Request__velocities,  // get_const(index) function pointer
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__get_function__WriteJoints_Request__velocities,  // get(index) function pointer
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__fetch_function__WriteJoints_Request__velocities,  // fetch(index, &value) function pointer
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__assign_function__WriteJoints_Request__velocities,  // assign(index, value) function pointer
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__resize_function__WriteJoints_Request__velocities  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_message_members = {
  "xiaox_interfaces__srv",  // message namespace
  "WriteJoints_Request",  // message name
  2,  // number of fields
  sizeof(xiaox_interfaces__srv__WriteJoints_Request),
  xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_message_member_array,  // message members
  xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_message_type_support_handle = {
  0,
  &xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_xiaox_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, xiaox_interfaces, srv, WriteJoints_Request)() {
  if (!xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_message_type_support_handle.typesupport_identifier) {
    xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &xiaox_interfaces__srv__WriteJoints_Request__rosidl_typesupport_introspection_c__WriteJoints_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "xiaox_interfaces/srv/detail/write_joints__rosidl_typesupport_introspection_c.h"
// already included above
// #include "xiaox_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "xiaox_interfaces/srv/detail/write_joints__functions.h"
// already included above
// #include "xiaox_interfaces/srv/detail/write_joints__struct.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  xiaox_interfaces__srv__WriteJoints_Response__init(message_memory);
}

void xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_fini_function(void * message_memory)
{
  xiaox_interfaces__srv__WriteJoints_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(xiaox_interfaces__srv__WriteJoints_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(xiaox_interfaces__srv__WriteJoints_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_message_members = {
  "xiaox_interfaces__srv",  // message namespace
  "WriteJoints_Response",  // message name
  2,  // number of fields
  sizeof(xiaox_interfaces__srv__WriteJoints_Response),
  xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_message_member_array,  // message members
  xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_message_type_support_handle = {
  0,
  &xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_xiaox_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, xiaox_interfaces, srv, WriteJoints_Response)() {
  if (!xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_message_type_support_handle.typesupport_identifier) {
    xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &xiaox_interfaces__srv__WriteJoints_Response__rosidl_typesupport_introspection_c__WriteJoints_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "xiaox_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "xiaox_interfaces/srv/detail/write_joints__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers xiaox_interfaces__srv__detail__write_joints__rosidl_typesupport_introspection_c__WriteJoints_service_members = {
  "xiaox_interfaces__srv",  // service namespace
  "WriteJoints",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // xiaox_interfaces__srv__detail__write_joints__rosidl_typesupport_introspection_c__WriteJoints_Request_message_type_support_handle,
  NULL  // response message
  // xiaox_interfaces__srv__detail__write_joints__rosidl_typesupport_introspection_c__WriteJoints_Response_message_type_support_handle
};

static rosidl_service_type_support_t xiaox_interfaces__srv__detail__write_joints__rosidl_typesupport_introspection_c__WriteJoints_service_type_support_handle = {
  0,
  &xiaox_interfaces__srv__detail__write_joints__rosidl_typesupport_introspection_c__WriteJoints_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, xiaox_interfaces, srv, WriteJoints_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, xiaox_interfaces, srv, WriteJoints_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_xiaox_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, xiaox_interfaces, srv, WriteJoints)() {
  if (!xiaox_interfaces__srv__detail__write_joints__rosidl_typesupport_introspection_c__WriteJoints_service_type_support_handle.typesupport_identifier) {
    xiaox_interfaces__srv__detail__write_joints__rosidl_typesupport_introspection_c__WriteJoints_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)xiaox_interfaces__srv__detail__write_joints__rosidl_typesupport_introspection_c__WriteJoints_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, xiaox_interfaces, srv, WriteJoints_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, xiaox_interfaces, srv, WriteJoints_Response)()->data;
  }

  return &xiaox_interfaces__srv__detail__write_joints__rosidl_typesupport_introspection_c__WriteJoints_service_type_support_handle;
}
