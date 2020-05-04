cmake_minimum_required(VERSION 2.8.3)
project(i2c_device)

add_compile_options(-std=c++11)
add_definitions(-Wall -Werror)

include_directories(
  include
)

set(I2C_DEVICE_LIB i2c_device)
add_library(${I2C_DEVICE_LIB} SHARED
  src/${I2C_DEVICE_LIB}.cpp
)

install(TARGETS ${I2C_DEVICE_LIB}
  DESTINATION lib
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.hpp"
  PATTERN "*~" EXCLUDE
)

configure_file(cmake/i2c_device.pc.in i2c_device.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/i2c_device.pc
  DESTINATION lib/pkgconfig
)

configure_file(cmake/i2c_device-config.cmake.in i2c_device-config.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/i2c_device-config.cmake
  DESTINATION share/i2c_device/cmake
)
