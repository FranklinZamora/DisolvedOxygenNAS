#include "OxygenNAS.h"
#include <Arduino.h>

OxygenNAS::OxygenNAS(int address)
{
  _address = address;
  Wire.begin();
}

float OxygenNAS::getDoNAS()
{
  byte DO_data[48];
  int i = 0;
  
  // Send command to read DO data to sensor
  Wire.beginTransmission(_address); 
  Wire.write("R");
  Wire.endTransmission(); 
  delay(1000);
  
  // Request data from sensor
  Wire.requestFrom(_address, 48, 1); 
  
  while (Wire.available()) 
  {
    byte b = Wire.read();
    if (b == 0x00) { // Stop reading when the first null byte is encountered
      break;
    }
    else if(b != 0x01 && b != 0x02) { // Ignore the STX (0x02) and SOH (0x01) characters
      DO_data[i] = b;
      i++;
    }
  }
  
  DO_data[i] = '\0'; // Null-terminate the array
  
  String data = ""; // Empty string to hold the data
  // Convert the data into a String
  for (int j = 0; j < i; j++)
  {
    data += (char)DO_data[j];
  }
  
  int commaIndex = data.indexOf(',');
  String DO_str = data.substring(0, commaIndex);
  String saturacion_str = data.substring(commaIndex + 1);

  _DO = DO_str.toFloat();
  _saturacionOxigeno = saturacion_str.toFloat();
  return _DO;
}

float OxygenNAS::getSaturacionOxigenoNAS()
{
  byte DO_data[48];
  int i = 0;
  
  // Send command to read DO data to sensor
  Wire.beginTransmission(_address); 
  Wire.write("R");
  Wire.endTransmission(); 
  delay(1000);
  
  // Request data from sensor
  Wire.requestFrom(_address, 48, 1); 
  
  while (Wire.available()) 
  {
    byte b = Wire.read();
    if (b == 0x00) { // Stop reading when the first null byte is encountered
      break;
    }
    else if(b != 0x01 && b != 0x02) { // Ignore the STX (0x02) and SOH (0x01) characters
      DO_data[i] = b;
      i++;
    }
  }
  
  DO_data[i] = '\0'; // Null-terminate the array
  
  String data = ""; // Empty string to hold the data
  // Convert the data into a String
  for (int j = 0; j < i; j++)
  {
    data += (char)DO_data[j];
  }
  
  int commaIndex = data.indexOf(',');
  String DO_str = data.substring(0, commaIndex);
  String saturacion_str = data.substring(commaIndex + 1);

  _DO = DO_str.toFloat();
  _saturacionOxigeno = saturacion_str.toFloat();
  return _saturacionOxigeno;
}

void OxygenNAS::sleepNAS()
{
  byte DO_data[48];
  int i = 0;
  
  // Send command to read DO data to sensor
  Wire.beginTransmission(_address); 
  Wire.write("R");
  Wire.endTransmission(); 
  delay(1000);
  
  // Request data from sensor
  Wire.requestFrom(_address, 48, 1); 
  
  while (Wire.available()) 
  {
    byte b = Wire.read();
    if (b == 0x00) { // Stop reading when the first null byte is encountered
      break;
    }
    else if(b != 0x01 && b != 0x02) { // Ignore the STX (0x02) and SOH (0x01) characters
      DO_data[i] = b;
      i++;
    }
  }
  
  DO_data[i] = '\0'; // Null-terminate the array
  
  String data = ""; // Empty string to hold the data
  // Convert the data into a String
  for (int j = 0; j < i; j++)
  {
    data += (char)DO_data[j];
  }
  
  int commaIndex = data.indexOf(',');
  String DO_str = data.substring(0, commaIndex);
  String saturacion_str = data.substring(commaIndex + 1);

  _DO = DO_str.toFloat();
  _saturacionOxigeno = saturacion_str.toFloat();
  // Send "Sleep" command to the sensor
  Wire.beginTransmission(_address);
  Wire.write("Sleep");
  Wire.endTransmission();
}