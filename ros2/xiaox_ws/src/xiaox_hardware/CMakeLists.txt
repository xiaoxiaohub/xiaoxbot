cmake_minimum_required(VERSION 3.8)
project(xiaox_hardware)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(controller_manager REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(xiaox_interfaces REQUIRED)

add_library(${PROJECT_NAME} SHARED
  src/xiaox_hardware.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(${PROJECT_NAME}
  controller_manager
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
  xiaox_interfaces
)

pluginlib_export_plugin_description_file(hardware_interface xiaox_hardware.xml)

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib
)

install(DIRECTORY include/
  DESTINATION include
)

install(FILES xiaox_hardware.xml
  DESTINATION share/${PROJECT_NAME}
)

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(
  controller_manager
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
  xiaox_interfaces
)

ament_package()
