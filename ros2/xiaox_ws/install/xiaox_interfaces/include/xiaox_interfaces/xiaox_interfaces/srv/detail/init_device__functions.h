// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from xiaox_interfaces:srv/InitDevice.idl
// generated code does not contain a copyright notice

#ifndef XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__FUNCTIONS_H_
#define XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "xiaox_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "xiaox_interfaces/srv/detail/init_device__struct.h"

/// Initialize srv/InitDevice message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * xiaox_interfaces__srv__InitDevice_Request
 * )) before or use
 * xiaox_interfaces__srv__InitDevice_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Request__init(xiaox_interfaces__srv__InitDevice_Request * msg);

/// Finalize srv/InitDevice message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
void
xiaox_interfaces__srv__InitDevice_Request__fini(xiaox_interfaces__srv__InitDevice_Request * msg);

/// Create srv/InitDevice message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * xiaox_interfaces__srv__InitDevice_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
xiaox_interfaces__srv__InitDevice_Request *
xiaox_interfaces__srv__InitDevice_Request__create();

/// Destroy srv/InitDevice message.
/**
 * It calls
 * xiaox_interfaces__srv__InitDevice_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
void
xiaox_interfaces__srv__InitDevice_Request__destroy(xiaox_interfaces__srv__InitDevice_Request * msg);

/// Check for srv/InitDevice message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Request__are_equal(const xiaox_interfaces__srv__InitDevice_Request * lhs, const xiaox_interfaces__srv__InitDevice_Request * rhs);

/// Copy a srv/InitDevice message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Request__copy(
  const xiaox_interfaces__srv__InitDevice_Request * input,
  xiaox_interfaces__srv__InitDevice_Request * output);

/// Initialize array of srv/InitDevice messages.
/**
 * It allocates the memory for the number of elements and calls
 * xiaox_interfaces__srv__InitDevice_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Request__Sequence__init(xiaox_interfaces__srv__InitDevice_Request__Sequence * array, size_t size);

/// Finalize array of srv/InitDevice messages.
/**
 * It calls
 * xiaox_interfaces__srv__InitDevice_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
void
xiaox_interfaces__srv__InitDevice_Request__Sequence__fini(xiaox_interfaces__srv__InitDevice_Request__Sequence * array);

/// Create array of srv/InitDevice messages.
/**
 * It allocates the memory for the array and calls
 * xiaox_interfaces__srv__InitDevice_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
xiaox_interfaces__srv__InitDevice_Request__Sequence *
xiaox_interfaces__srv__InitDevice_Request__Sequence__create(size_t size);

/// Destroy array of srv/InitDevice messages.
/**
 * It calls
 * xiaox_interfaces__srv__InitDevice_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
void
xiaox_interfaces__srv__InitDevice_Request__Sequence__destroy(xiaox_interfaces__srv__InitDevice_Request__Sequence * array);

/// Check for srv/InitDevice message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Request__Sequence__are_equal(const xiaox_interfaces__srv__InitDevice_Request__Sequence * lhs, const xiaox_interfaces__srv__InitDevice_Request__Sequence * rhs);

/// Copy an array of srv/InitDevice messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Request__Sequence__copy(
  const xiaox_interfaces__srv__InitDevice_Request__Sequence * input,
  xiaox_interfaces__srv__InitDevice_Request__Sequence * output);

/// Initialize srv/InitDevice message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * xiaox_interfaces__srv__InitDevice_Response
 * )) before or use
 * xiaox_interfaces__srv__InitDevice_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Response__init(xiaox_interfaces__srv__InitDevice_Response * msg);

/// Finalize srv/InitDevice message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
void
xiaox_interfaces__srv__InitDevice_Response__fini(xiaox_interfaces__srv__InitDevice_Response * msg);

/// Create srv/InitDevice message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * xiaox_interfaces__srv__InitDevice_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
xiaox_interfaces__srv__InitDevice_Response *
xiaox_interfaces__srv__InitDevice_Response__create();

/// Destroy srv/InitDevice message.
/**
 * It calls
 * xiaox_interfaces__srv__InitDevice_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
void
xiaox_interfaces__srv__InitDevice_Response__destroy(xiaox_interfaces__srv__InitDevice_Response * msg);

/// Check for srv/InitDevice message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Response__are_equal(const xiaox_interfaces__srv__InitDevice_Response * lhs, const xiaox_interfaces__srv__InitDevice_Response * rhs);

/// Copy a srv/InitDevice message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Response__copy(
  const xiaox_interfaces__srv__InitDevice_Response * input,
  xiaox_interfaces__srv__InitDevice_Response * output);

/// Initialize array of srv/InitDevice messages.
/**
 * It allocates the memory for the number of elements and calls
 * xiaox_interfaces__srv__InitDevice_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Response__Sequence__init(xiaox_interfaces__srv__InitDevice_Response__Sequence * array, size_t size);

/// Finalize array of srv/InitDevice messages.
/**
 * It calls
 * xiaox_interfaces__srv__InitDevice_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
void
xiaox_interfaces__srv__InitDevice_Response__Sequence__fini(xiaox_interfaces__srv__InitDevice_Response__Sequence * array);

/// Create array of srv/InitDevice messages.
/**
 * It allocates the memory for the array and calls
 * xiaox_interfaces__srv__InitDevice_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
xiaox_interfaces__srv__InitDevice_Response__Sequence *
xiaox_interfaces__srv__InitDevice_Response__Sequence__create(size_t size);

/// Destroy array of srv/InitDevice messages.
/**
 * It calls
 * xiaox_interfaces__srv__InitDevice_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
void
xiaox_interfaces__srv__InitDevice_Response__Sequence__destroy(xiaox_interfaces__srv__InitDevice_Response__Sequence * array);

/// Check for srv/InitDevice message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Response__Sequence__are_equal(const xiaox_interfaces__srv__InitDevice_Response__Sequence * lhs, const xiaox_interfaces__srv__InitDevice_Response__Sequence * rhs);

/// Copy an array of srv/InitDevice messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_xiaox_interfaces
bool
xiaox_interfaces__srv__InitDevice_Response__Sequence__copy(
  const xiaox_interfaces__srv__InitDevice_Response__Sequence * input,
  xiaox_interfaces__srv__InitDevice_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // XIAOX_INTERFACES__SRV__DETAIL__INIT_DEVICE__FUNCTIONS_H_
