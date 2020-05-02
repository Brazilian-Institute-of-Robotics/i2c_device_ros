cmake_minimum_required(VERSION 2.8.3)
project(i2c_device)

add_compile_options(-std=c++11)
add_definitions(-Wall -Werror)

include_directories(
  include
)

set(I2C_DEVICE_LIB i2c_device)
add_library(${I2C_DEVICE_LIB}
  src/${I2C_DEVICE_LIB}.cpp
)
