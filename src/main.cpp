#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <unistd.h>
#include <stdio.h>

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
  uint8_t config[2] = {0xC3, 0x83};
  I2CDevice i2c;
  i2c.openI2CBus("/dev/i2c-1", id);
  // Write on config register 01, gain of 4.096V
  i2c.writeBytes(0x01, 2, config);
  usleep(100);

  uint8_t raw[2];
  // Read conversion register
  i2c.readBytes(0x00, 6, raw);
  uint16_t result = (static_cast<uint16_t>(raw[0]) << 8) | raw[1];
  std::cout << "ADC: " << result << std::endl;
  if (result > 32767){
    result -= 65536;
  }

  double out = result * 4.096 / 32768.0;
  std::cout << "Voltage: " << out << std::endl;
  return 0;
}
