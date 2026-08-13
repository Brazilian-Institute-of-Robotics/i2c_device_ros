#include <iostream>
#include <string>

#include "i2c_device_ros/i2c_device.hpp"

int end(int argc, char* argv[])
{
  int id = std::stoi(argv[1], nullptr, 16);
  I2CDevice i2c;
  i2c.openI2CBus("/dev/i2c-1", id);
  uint8_t data[6];
  i2c.readBytes(0xFD, 6, data);
  uint16_t water = (static_cast<uint16_t>(data[0]) << 8) | data[1];

  while (true){
    if (water > 32767){
      water -= 65536;
    }

    // uint16_t raw_humidity = (static_cast<uint16_t>(data[3]) << 8) | data[4];
    double out = 4.096 * water / 32768.0;
    // double humidity = -6.0 + 125.0 * raw_humidity / 65535.0;
    // std::cout << "Temp: " << temperature << " Hum: " << humidity << std::endl;
    std::cout << "Water Level: " << out << std::endl;
  }
  return 0;
}
