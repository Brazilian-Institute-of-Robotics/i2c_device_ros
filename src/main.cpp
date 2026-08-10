#include <iostream>
#include <string>

#include "i2c_device_ros/i2c_device.hpp"

int main(int argc, char* argv[])
{
  int id = std::stoi(argv[1], nullptr, 16);
  I2CDevice i2c;
  i2c.openI2CBus("/dev/i2c-4", id);
  return 0;
}