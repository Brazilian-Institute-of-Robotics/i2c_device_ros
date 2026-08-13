#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "i2c_device_ros/i2c_device.hpp"

int main(int argc, char* argv[])
{
  // int id = std::stoi(argv[1], nullptr, 16);
  // I2CDevice i2c;
  // i2c.openI2CBus("/dev/i2c-1", id);
  // uint8_t data[6];
  // i2c.readBytes(0xFD, 6, data);
  // uint16_t raw_temperature = (static_cast<uint16_t>(data[0]) << 8) | data[1];
  // uint16_t raw_humidity = (static_cast<uint16_t>(data[3]) << 8) | data[4];
  // double temperature = -45.0 + 175.0 * raw_temperature / 65535.0;
  // double humidity = -6.0 + 125.0 * raw_humidity / 65535.0;
  // std::cout << "Temp: " << temperature << " Hum: " << humidity << std::endl;

  int id = std::stoi(argv[1], nullptr, 16);
  I2CDevice i2c;
  i2c.openI2CBus("/dev/i2c-1", id);
  uint8_t data[6];
  i2c.readBytes(0xFD, 2, data);
  uint16_t water = (static_cast<uint16_t>(data[0]) << 8) | data[1];

  while (true){
    if (water > 32767){
      water -= 65536;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // uint16_t raw_humidity = (static_cast<uint16_t>(data[3]) << 8) | data[4];
    double out = water * 4.096 / 32768.0;
    // double humidity = -6.0 + 125.0 * raw_humidity / 65535.0;
    // std::cout << "Temp: " << temperature << " Hum: " << humidity << std::endl;
    std::cout << "Water Level: " << out << std::endl;
  }
  return 0;
}
