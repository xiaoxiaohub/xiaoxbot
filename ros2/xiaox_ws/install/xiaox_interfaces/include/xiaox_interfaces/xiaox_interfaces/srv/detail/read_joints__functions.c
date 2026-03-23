// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from xiaox_interfaces:srv/ReadJoints.idl
// generated code does not contain a copyright notice
#include "xiaox_interfaces/srv/detail/read_joints__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `action`
#include "rosidl_runtime_c/string_functions.h"

bool
xiaox_interfaces__srv__ReadJoints_Request__init(xiaox_interfaces__srv__ReadJoints_Request * msg)
{
  if (!msg) {
    return false;
  }
  // action
  if (!rosidl_runtime_c__String__init(&msg->action)) {
    xiaox_interfaces__srv__ReadJoints_Request__fini(msg);
    return false;
  }
  return true;
}

void
xiaox_interfaces__srv__ReadJoints_Request__fini(xiaox_interfaces__srv__ReadJoints_Request * msg)
{
  if (!msg) {
    return;
  }
  // action
  rosidl_runtime_c__String__fini(&msg->action);
}

bool
xiaox_interfaces__srv__ReadJoints_Request__are_equal(const xiaox_interfaces__srv__ReadJoints_Request * lhs, const xiaox_interfaces__srv__ReadJoints_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // action
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->action), &(rhs->action)))
  {
    return false;
  }
  return true;
}

bool
xiaox_interfaces__srv__ReadJoints_Request__copy(
  const xiaox_interfaces__srv__ReadJoints_Request * input,
  xiaox_interfaces__srv__ReadJoints_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // action
  if (!rosidl_runtime_c__String__copy(
      &(input->action), &(output->action)))
  {
    return false;
  }
  return true;
}

xiaox_interfaces__srv__ReadJoints_Request *
xiaox_interfaces__srv__ReadJoints_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  xiaox_interfaces__srv__ReadJoints_Request * msg = (xiaox_interfaces__srv__ReadJoints_Request *)allocator.allocate(sizeof(xiaox_interfaces__srv__ReadJoints_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(xiaox_interfaces__srv__ReadJoints_Request));
  bool success = xiaox_interfaces__srv__ReadJoints_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
xiaox_interfaces__srv__ReadJoints_Request__destroy(xiaox_interfaces__srv__ReadJoints_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    xiaox_interfaces__srv__ReadJoints_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
xiaox_interfaces__srv__ReadJoints_Request__Sequence__init(xiaox_interfaces__srv__ReadJoints_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  xiaox_interfaces__srv__ReadJoints_Request * data = NULL;

  if (size) {
    data = (xiaox_interfaces__srv__ReadJoints_Request *)allocator.zero_allocate(size, sizeof(xiaox_interfaces__srv__ReadJoints_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = xiaox_interfaces__srv__ReadJoints_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        xiaox_interfaces__srv__ReadJoints_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
xiaox_interfaces__srv__ReadJoints_Request__Sequence__fini(xiaox_interfaces__srv__ReadJoints_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      xiaox_interfaces__srv__ReadJoints_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

xiaox_interfaces__srv__ReadJoints_Request__Sequence *
xiaox_interfaces__srv__ReadJoints_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  xiaox_interfaces__srv__ReadJoints_Request__Sequence * array = (xiaox_interfaces__srv__ReadJoints_Request__Sequence *)allocator.allocate(sizeof(xiaox_interfaces__srv__ReadJoints_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = xiaox_interfaces__srv__ReadJoints_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
xiaox_interfaces__srv__ReadJoints_Request__Sequence__destroy(xiaox_interfaces__srv__ReadJoints_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    xiaox_interfaces__srv__ReadJoints_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
xiaox_interfaces__srv__ReadJoints_Request__Sequence__are_equal(const xiaox_interfaces__srv__ReadJoints_Request__Sequence * lhs, const xiaox_interfaces__srv__ReadJoints_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!xiaox_interfaces__srv__ReadJoints_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
xiaox_interfaces__srv__ReadJoints_Request__Sequence__copy(
  const xiaox_interfaces__srv__ReadJoints_Request__Sequence * input,
  xiaox_interfaces__srv__ReadJoints_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(xiaox_interfaces__srv__ReadJoints_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    xiaox_interfaces__srv__ReadJoints_Request * data =
      (xiaox_interfaces__srv__ReadJoints_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!xiaox_interfaces__srv__ReadJoints_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          xiaox_interfaces__srv__ReadJoints_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!xiaox_interfaces__srv__ReadJoints_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `positions`
// Member `velocities`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
xiaox_interfaces__srv__ReadJoints_Response__init(xiaox_interfaces__srv__ReadJoints_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    xiaox_interfaces__srv__ReadJoints_Response__fini(msg);
    return false;
  }
  // positions
  if (!rosidl_runtime_c__double__Sequence__init(&msg->positions, 0)) {
    xiaox_interfaces__srv__ReadJoints_Response__fini(msg);
    return false;
  }
  // velocities
  if (!rosidl_runtime_c__double__Sequence__init(&msg->velocities, 0)) {
    xiaox_interfaces__srv__ReadJoints_Response__fini(msg);
    return false;
  }
  return true;
}

void
xiaox_interfaces__srv__ReadJoints_Response__fini(xiaox_interfaces__srv__ReadJoints_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // positions
  rosidl_runtime_c__double__Sequence__fini(&msg->positions);
  // velocities
  rosidl_runtime_c__double__Sequence__fini(&msg->velocities);
}

bool
xiaox_interfaces__srv__ReadJoints_Response__are_equal(const xiaox_interfaces__srv__ReadJoints_Response * lhs, const xiaox_interfaces__srv__ReadJoints_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // positions
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->positions), &(rhs->positions)))
  {
    return false;
  }
  // velocities
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->velocities), &(rhs->velocities)))
  {
    return false;
  }
  return true;
}

bool
xiaox_interfaces__srv__ReadJoints_Response__copy(
  const xiaox_interfaces__srv__ReadJoints_Response * input,
  xiaox_interfaces__srv__ReadJoints_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // positions
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->positions), &(output->positions)))
  {
    return false;
  }
  // velocities
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->velocities), &(output->velocities)))
  {
    return false;
  }
  return true;
}

xiaox_interfaces__srv__ReadJoints_Response *
xiaox_interfaces__srv__ReadJoints_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  xiaox_interfaces__srv__ReadJoints_Response * msg = (xiaox_interfaces__srv__ReadJoints_Response *)allocator.allocate(sizeof(xiaox_interfaces__srv__ReadJoints_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(xiaox_interfaces__srv__ReadJoints_Response));
  bool success = xiaox_interfaces__srv__ReadJoints_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
xiaox_interfaces__srv__ReadJoints_Response__destroy(xiaox_interfaces__srv__ReadJoints_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    xiaox_interfaces__srv__ReadJoints_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
xiaox_interfaces__srv__ReadJoints_Response__Sequence__init(xiaox_interfaces__srv__ReadJoints_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  xiaox_interfaces__srv__ReadJoints_Response * data = NULL;

  if (size) {
    data = (xiaox_interfaces__srv__ReadJoints_Response *)allocator.zero_allocate(size, sizeof(xiaox_interfaces__srv__ReadJoints_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = xiaox_interfaces__srv__ReadJoints_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        xiaox_interfaces__srv__ReadJoints_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
xiaox_interfaces__srv__ReadJoints_Response__Sequence__fini(xiaox_interfaces__srv__ReadJoints_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      xiaox_interfaces__srv__ReadJoints_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

xiaox_interfaces__srv__ReadJoints_Response__Sequence *
xiaox_interfaces__srv__ReadJoints_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  xiaox_interfaces__srv__ReadJoints_Response__Sequence * array = (xiaox_interfaces__srv__ReadJoints_Response__Sequence *)allocator.allocate(sizeof(xiaox_interfaces__srv__ReadJoints_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = xiaox_interfaces__srv__ReadJoints_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
xiaox_interfaces__srv__ReadJoints_Response__Sequence__destroy(xiaox_interfaces__srv__ReadJoints_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    xiaox_interfaces__srv__ReadJoints_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
xiaox_interfaces__srv__ReadJoints_Response__Sequence__are_equal(const xiaox_interfaces__srv__ReadJoints_Response__Sequence * lhs, const xiaox_interfaces__srv__ReadJoints_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!xiaox_interfaces__srv__ReadJoints_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
xiaox_interfaces__srv__ReadJoints_Response__Sequence__copy(
  const xiaox_interfaces__srv__ReadJoints_Response__Sequence * input,
  xiaox_interfaces__srv__ReadJoints_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(xiaox_interfaces__srv__ReadJoints_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    xiaox_interfaces__srv__ReadJoints_Response * data =
      (xiaox_interfaces__srv__ReadJoints_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!xiaox_interfaces__srv__ReadJoints_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          xiaox_interfaces__srv__ReadJoints_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!xiaox_interfaces__srv__ReadJoints_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
