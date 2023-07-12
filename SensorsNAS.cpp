#include "SensorsNAS.h"
#include <Arduino.h>
#include <Wire.h>

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
    if (b == 0x00)
    { // Stop reading when the first null byte is encountered
      break;
    }
    else if (b != 0x01 && b != 0x02)
    { // Ignore the STX (0x02) and SOH (0x01) characters
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
    if (b == 0x00)
    { // Stop reading when the first null byte is encountered
      break;
    }
    else if (b != 0x01 && b != 0x02)
    { // Ignore the STX (0x02) and SOH (0x01) characters
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
    if (b == 0x00)
    { // Stop reading when the first null byte is encountered
      break;
    }
    else if (b != 0x01 && b != 0x02)
    { // Ignore the STX (0x02) and SOH (0x01) characters
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

void OxygenNAS::ledControlNAS(bool state)
{
  Wire.beginTransmission(_address);

  if (state)
  {
    Wire.write("L,1"); // remplaza "L,1" con el comando correcto para tu sensor
  }
  else
  {
    Wire.write("L,0"); // remplaza "L,0" con el comando correcto para tu sensor
  }

  Wire.endTransmission();
}

String OxygenNAS::find()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("Done");
}

pH_EZO::pH_EZO(uint8_t sensorAddress) {
  _sensorAddress = sensorAddress;
  Wire.begin();
}

float pH_EZO::readpH() {
  Wire.beginTransmission(_sensorAddress);
  Wire.write('r');
  Wire.endTransmission(false);

  delay(1000);

  Wire.requestFrom(_sensorAddress, 7);
  while (Wire.available() < 7);

  char data[7];
  for (int i = 0; i < 7; i++) {
    data[i] = Wire.read();
  }

  if (data[0] == 'R') {
    float pHValue = atof(&data[1]);
    return pHValue;
  }

  return -1.0;
}
