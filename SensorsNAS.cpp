#include "SensorsNAS.h"
#include <Arduino.h>
#include <Wire.h>

SensorsNAS::SensorsNAS(int address)
{
  _address = address;
  Wire.begin();
  Serial2.begin(9600);
}

float SensorsNAS::getDO()
{
  byte DO_data[48];
  int i = 0;

  // Send command to read DO data to sensor
  Wire.beginTransmission(_address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 600)
  {
    // Wait
  }

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

float SensorsNAS::getSAT()
{
  byte DO_data[48];
  int i = 0;

  // Send command to read DO data to sensor
  Wire.beginTransmission(_address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 600)
  {
    // Wait
  }

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

  //_DO = DO_str.toFloat();
  _saturacionOxigeno = saturacion_str.toFloat();
  return _saturacionOxigeno;
}

void SensorsNAS::calibrateDO(String calibrationValue)
{
  String command = "CAL," + calibrationValue;
  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();
  Serial.println("Calibration command sent.");

  unsigned long startTime = millis();
  while (millis() - startTime < 1300)
  {
    // Wait
  }

  // Request data from sensor
  byte response;
  Wire.requestFrom(_address, 1);

  unsigned long startTime2 = millis();
  while (millis() - startTime2 < 100)
  {
    // Wait
  }

  if (Wire.available())
  {
    response = Wire.read();
    if (response == 1)
    {
      Serial.println("Successful calibration.");
    }
    else if (response == 2)
    {
      Serial.println("Calibration failed.");
    }
    else
    {
      Serial.println("Invalid answer.");
    }
  }
  else
  {
    Serial.println("No response received from sensor.");
  }
}

void SensorsNAS::clearCalibrationDO()
{
  String command = "CAL,CLEAR";
  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }

  // Request data from sensor
  byte response;
  Wire.requestFrom(_address, 1);
  if (Wire.available())
  {
    response = Wire.read();
  }

  if (response == 1)
  {
    Serial.println("Calibration cleared successfully.");
  }
  else if (response == 2)
  {
    Serial.println("Failed when trying to clear calibration.");
  }
  else
  {
    Serial.println("Invalid answer.");
  }
}

String SensorsNAS::exportCalibrationDO()
{
  String command = "Export";
  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
    // Wait
  }

  // Request data from sensor
  Wire.requestFrom(_address, 32, 1);

  byte code = 0;

  code = Wire.read();

  switch (code)
  {                            // switch case based on what the response code is.
  case 1:                      // decimal 1.
    Serial.println("Success"); // means the command was successful.
    break;                     // exits the switch case.

  case 2:                     // decimal 2.
    Serial.println("Failed"); // means the command has failed.
    break;                    // exits the switch case.

  case 254:                    // decimal 254.
    Serial.println("Pending"); // means the command has not yet been finished calculating.
    break;                     // exits the switch case.

  case 255:                    // decimal 255.
    Serial.println("No Data"); // means there is no further data to send.
    break;                     // exits the switch case.
  }
  // String para almacenar la respuesta del sensor
  String response = "";

  char do_data[32];
  byte i = 0;
  // Leer cada byte recibido
  while (Wire.available())
  {                             // are there bytes to receive.
    byte in_char = Wire.read(); // receive a byte.
    do_data[i] = in_char;       // load this byte into our array.
    i += 1;                     // incur the counter for the array element.
    if (in_char == 0)
    {        // if we see that we have been sent a null command.
      i = 0; // reset the counter i to 0.
      break; // exit the while loop.
    }
  }

  return do_data;
}

bool SensorsNAS::importCalibrationDO(String calibrationData)
{
  String command = "IMPORT,";
  command += calibrationData;

  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 900)
  {
    // Wait
  }

  // Request data from sensor
  byte response[20];
  Wire.requestFrom(_address, 20);
  if (Wire.available())
  {
    byte i = 0;
    while (Wire.available() && i < 20)
    {
      response[i++] = Wire.read();
    }

    // Evaluate if the answer is 1
    if (response[0] == 1)
    {
      return true;
    }
  }

  return false;
}

bool SensorsNAS::setTempCompensationDO(float temperature)
{
  String command = "T,";
  command += String(temperature, 1); // Convert value to string

  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 300)
  {
    // Wait
  }

  // Request data from sensor
  byte response[20];
  Wire.requestFrom(_address, 20);
  if (Wire.available())
  {
    byte i = 0;
    while (Wire.available() && i < 20)
    {
      response[i++] = Wire.read();
    }

    if (response[0] == 1)
    {
      return true;
    }
  }

  return false;
}

float SensorsNAS::getTempCompensationDO()
{
  String command = "T,?";
  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 500)
  {
    // Wait
  }

  // Request data from sensor
  Wire.requestFrom(_address, 20);
  String response = "";
  while (Wire.available())
  {
    char c = Wire.read();
    response += c;
  }

  for (int i = 0; i < response.length(); i++)
  {
    if (isdigit(response.charAt(i)))
    {
      float temperature = response.substring(i).toFloat();
      return temperature;
    }
  }

  return -999.0;
}

bool SensorsNAS::setSalCompensationDO(float saladditionalBytesy)
{
  String command = "S,";
  command += String(saladditionalBytesy, 1);

  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 300)
  {
    // Wait
  }

  // Request data from sensor
  byte response[20];
  Wire.requestFrom(_address, 20);
  if (Wire.available())
  {
    byte i = 0;
    while (Wire.available() && i < 20)
    {
      response[i++] = Wire.read();
    }

    if (response[0] == 1)
    {
      return true;
    }
  }

  return false;
}

float SensorsNAS::getSalCompensationDO()
{
  String command = "S,?";
  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 500)
  {
    // Wait
  }
  // Request data from sensor
  Wire.requestFrom(_address, 20);
  String response = "";
  while (Wire.available())
  {
    char c = Wire.read();
    response += c;
  }

  for (int i = 0; i < response.length(); i++)
  {
    if (isdigit(response.charAt(i)))
    {
      float saladditionalBytesy = response.substring(i).toFloat();
      return saladditionalBytesy;
    }
  }
  return -999.0;
}

bool SensorsNAS::setAtmosphericPressureCompensation(float atPressure)
{
  String command = "P,";
  command += String(atPressure, 1);

  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 300)
  {
    // Wait
  }

  // Request data from sensorr
  byte response[20];
  Wire.requestFrom(_address, 20);
  if (Wire.available())
  {
    byte i = 0;
    while (Wire.available() && i < 20)
    {
      response[i++] = Wire.read();
    }

    if (response[0] == 1)
    {
      return true;
    }
  }

  return false;
}

float SensorsNAS::getAtmosphericPressureCompensation()
{
  String command = "P,?";
  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 500)
  {
    // Wait
  }

  // Request data from sensor
  Wire.requestFrom(_address, 20);
  String response = "";

  while (Wire.available())
  {
    char c = Wire.read();
    response += c;
  }

  for (int i = 0; i < response.length(); i++)
  {
    if (isdigit(response.charAt(i)) || response.charAt(i) == '.')
    {
      float pressure = response.substring(i).toFloat();
      return pressure;
    }
  }

  return -999.0;
}

void SensorsNAS::setName(String name)
{
  String command = "Name," + name;
  Wire.beginTransmission(_address);
  Wire.write(command.c_str());
  Wire.endTransmission();
  Serial.println("The name has been assigned.");

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }

  byte response;
  Wire.requestFrom(_address, 1);
  unsigned long startTime2 = millis();
  while (millis() - startTime2 < 100)
  {
    // Wait
  }

  if (Wire.available())
  {
    response = Wire.read();
    if (response == 1)
    {
      Serial.println("Name set");
    }
    else if (response == 2)
    {
      Serial.println("Name failed");
    }
    else
    {
      Serial.println("Invalid answer");
    }
  }
  else
  {
    Serial.println("No response received from sensor.");
  }
}

String SensorsNAS::getName()
{
  Wire.beginTransmission(_address);
  Wire.write("name,?");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 500)
  {
    // Wait
  }
  // Leer la respuesta del sensor
  Wire.requestFrom(_address, 20);
  String response = "";
  while (Wire.available())
  {
    char c = Wire.read();
    response += c;
  }

  return response;
}

void SensorsNAS::enableMgO2()
{
  Wire.beginTransmission(_address);
  Wire.write("O,mg,1"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }
}

void SensorsNAS::disableMgO2()
{
  Wire.beginTransmission(_address);
  Wire.write("O,mg,0"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();
  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }
}

void SensorsNAS::enableSatO2()
{
  Wire.beginTransmission(_address);
  Wire.write("O,%,1"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();
  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }
}

void SensorsNAS::disableSatO2()
{
  Wire.beginTransmission(_address);
  Wire.write("O,%,0"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();
  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

float SensorsNAS::getPH()
{
  byte data[6];

  Wire.beginTransmission(_address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
  }

  Wire.requestFrom(_address, 6, 1);
  x = "";
  for (int i = 0; i <= 5; i++)
  {
    data[i] = Wire.read();
    if (i != 0)
    {
      x += char(data[i]);
    }
    // x += String(data[i]);
    // Serial.println(data[i]);
  }
  _PH = x.toFloat();
  return _PH;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

float SensorsNAS::getEC()
{
  byte code = 0;
  char ec_data[32]; // we make a 32 byte character array to hold incoming data from the EC circuit.
  byte in_char = 0;
  byte i = 0;
  byte serial_event = 0;
  char *ec;

  Wire.beginTransmission(_address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
  }

  Wire.requestFrom(_address, 32, 1);
  code = Wire.read();

  switch (code)
  {                   // switch case based on what the response code is.
  case 1:             // decimal 1.
    Serial.print(""); // means the command was successful.
    break;            // exits the switch case.
  }

  while (Wire.available())
  {                        // are there bytes to receive.
    in_char = Wire.read(); // receive a byte.
    ec_data[i] = in_char;  // load this byte into our array.
    i += 1;                // incur the counter for the array element.
    if (in_char == 0)
    {        // if we see that we have been sent a null command.
      i = 0; // reset the counter i to 0.
      break; // exit the while loop.
    }
  }
  ec = strtok(ec_data, ","); // let's pars the string at each comma.
  _EC = atof(ec);
  return _EC;
} // End

float SensorsNAS::getTDS()
{
  byte code = 0;
  char ec_data[32]; // we make a 32 byte character array to hold incoming data from the EC circuit.
  byte in_char = 0;
  byte i = 0;
  byte serial_event = 0;
  char *tds;

  Wire.beginTransmission(_address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
  }

  Wire.requestFrom(_address, 32, 1);
  code = Wire.read();

  switch (code)
  {                   // switch case based on what the response code is.
  case 1:             // decimal 1.
    Serial.print(""); // means the command was successful.
    break;            // exits the switch case.
  }

  while (Wire.available())
  {                        // are there bytes to receive.
    in_char = Wire.read(); // receive a byte.
    ec_data[i] = in_char;  // load this byte into our array.
    i += 1;                // incur the counter for the array element.
    if (in_char == 0)
    {        // if we see that we have been sent a null command.
      i = 0; // reset the counter i to 0.
      break; // exit the while loop.
    }
  }
  tds = strtok(NULL, ","); // let's pars the string at each comma.
  _TDS = atof(tds);
  return _TDS;
}

float SensorsNAS::getSAL()
{
  byte code = 0;
  char ec_data[32]; // we make a 32 byte character array to hold incoming data from the EC circuit.
  byte in_char = 0;
  byte i = 0;
  byte serial_event = 0;
  char *sal;

  Wire.beginTransmission(_address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
  }

  Wire.requestFrom(_address, 32, 1);
  code = Wire.read();

  switch (code)
  {                   // switch case based on what the response code is.
  case 1:             // decimal 1.
    Serial.print(""); // means the command was successful.
    break;            // exits the switch case.
  }

  while (Wire.available())
  {                        // are there bytes to receive.
    in_char = Wire.read(); // receive a byte.
    ec_data[i] = in_char;  // load this byte into our array.
    i += 1;                // incur the counter for the array element.
    if (in_char == 0)
    {        // if we see that we have been sent a null command.
      i = 0; // reset the counter i to 0.
      break; // exit the while loop.
    }
  }
  sal = strtok(NULL, ","); // let's pars the string at each comma.
  _SAL = atof(sal);
  return _SAL;
}

float SensorsNAS::getSG()
{
  byte code = 0;
  char ec_data[32]; // we make a 32 byte character array to hold incoming data from the EC circuit.
  byte in_char = 0;
  byte i = 0;
  byte serial_event = 0;
  char *sg;

  Wire.beginTransmission(_address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
  }

  Wire.requestFrom(_address, 32, 1);
  code = Wire.read();

  switch (code)
  {                   // switch case based on what the response code is.
  case 1:             // decimal 1.
    Serial.print(""); // means the command was successful.
    break;            // exits the switch case.
  }

  while (Wire.available())
  {                        // are there bytes to receive.
    in_char = Wire.read(); // receive a byte.
    ec_data[i] = in_char;  // load this byte into our array.
    i += 1;                // incur the counter for the array element.
    if (in_char == 0)
    {        // if we see that we have been sent a null command.
      i = 0; // reset the counter i to 0.
      break; // exit the while loop.
    }
  }
  sg = strtok(NULL, ","); // let's pars the string at each comma.
  _SG = atof(sg);
  return _SG;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SensorsNAS::sleepNAS()
{
  byte DO_data[48];
  int i = 0;

  // Send command to read DO data to sensor
  Wire.beginTransmission(_address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 1000)
  {
    // Wait
  }

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

void SensorsNAS::ledControlNAS(bool state)
{
  Wire.beginTransmission(_address);

  if (state)
  {
    Wire.write("L,1");
  }
  else
  {
    Wire.write("L,0");
  }

  Wire.endTransmission();
}

String SensorsNAS::find()
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
      Serial.print("I2C device found at address: ");
      if (address < 16)
        Serial.print("0");
      Serial.print(address);
      Serial.println(" !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("Done");
}

String SensorsNAS::deviceInformation()
{
  Wire.beginTransmission(_address);
  Wire.write("I");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }

  Wire.requestFrom(_address, 20);
  String response = "";
  while (Wire.available())
  {
    char c = Wire.read();
    response += c;
  }

  return response;
}

String SensorsNAS::deviceStatus()
{
  Wire.beginTransmission(_address);
  Wire.write("Status");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }

  Wire.requestFrom(_address, 20);
  String response = "";
  while (Wire.available())
  {
    char c = Wire.read();
    response += c;
  }

  return response;
}

float SensorsNAS::getORP()
{
  byte code = 0;
  char ORP_data[32];
  byte in_char = 0;
  byte i = 0;
  byte serial_event = 0;

  Wire.beginTransmission(_address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
  }

  Wire.requestFrom(_address, 32, 1);
  code = Wire.read();

  switch (code)
  {
  case 1:
    Serial.print("");
    break;
  }

  while (Wire.available())
  {                        // are there bytes to receive.
    in_char = Wire.read(); // receive a byte.
    ORP_data[i] = in_char; // load this byte into our array.
    i += 1;                // incur the counter for the array element.
    if (in_char == 0)
    {        // if we see that we have been sent a null command.
      i = 0; // reset the counter i to 0.
      break; // exit the while loop.
    }
  }

  _ORP = atof(ORP_data);
  return _ORP;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
byte SensorsNAS::generateArray(byte MacID[8], SensorsNAS &sensorDO, SensorsNAS &sensorPH, SensorsNAS &sensorEC, SensorsNAS &sensorORP)
{

  UINT32_t EC, TDS, ORP, UNSIG;
  UINT16_t DisolvedOx, SaturationOx, Ph, SAL;
  UINT8_t SG;

  randomSeed(analogRead(A0));
  int virtualERC = (random(-1019.9, 1019.9)) * 100;

  DisolvedOx.value = sensorDO.getDO() * 100;
  SaturationOx.value = sensorDO.getSAT() * 100;
  EC.value = sensorEC.getEC() * 100;
  TDS.value = sensorEC.getTDS() * 100;
  SAL.value = sensorEC.getSAL() * 100;
  SG.value = sensorEC.getSG() * 100;
  Ph.value = sensorPH.getPH() * 100;
  ORP.value = sensorORP.getORP() * 100;

  if (ORP.value < 0)
  {
    ORP.value = ORP.value * -1;
    UNSIG.bytes[0] = 0x00;
  }
  else
  {
    UNSIG.bytes[0] = 0x01;
  }

  byte arrayBytes[40];

  arrayBytes[0] = 0x7E;     // Start
  arrayBytes[1] = 0x00;     // length 1
  arrayBytes[2] = 0x24;     // Length 2
  arrayBytes[3] = 0x10;     // Frametype
  arrayBytes[4] = 0x00;     // Frame ID
  arrayBytes[5] = MacID[0]; // Start Mac ID
  arrayBytes[6] = MacID[1];
  arrayBytes[7] = MacID[2];
  arrayBytes[8] = MacID[3];
  arrayBytes[9] = MacID[4];
  arrayBytes[10] = MacID[5];
  arrayBytes[11] = MacID[6];
  arrayBytes[12] = MacID[7]; // End Mac ID
  arrayBytes[13] = 0xFF;     // 8bit Add
  arrayBytes[14] = 0xFE;     // 8bit ADD
  arrayBytes[15] = 0x00;     // Broadcast radio
  arrayBytes[16] = 0x00;     // Option

  arrayBytes[17] = 0x48; // Payload Start

  arrayBytes[18] = DisolvedOx.bytes[1];
  arrayBytes[19] = DisolvedOx.bytes[0];

  arrayBytes[20] = SaturationOx.bytes[1];
  arrayBytes[21] = SaturationOx.bytes[0];

  arrayBytes[22] = Ph.bytes[1];
  arrayBytes[23] = Ph.bytes[0];

  arrayBytes[24] = EC.bytes[3];
  arrayBytes[25] = EC.bytes[2];
  arrayBytes[26] = EC.bytes[1];
  arrayBytes[27] = EC.bytes[0];

  arrayBytes[28] = TDS.bytes[3];
  arrayBytes[29] = TDS.bytes[2];
  arrayBytes[30] = TDS.bytes[1];
  arrayBytes[31] = TDS.bytes[0];

  arrayBytes[32] = SAL.bytes[1];
  arrayBytes[33] = SAL.bytes[0];

  arrayBytes[34] = SG.bytes[0]; // End payload
  arrayBytes[35] = UNSIG.bytes[0];
  arrayBytes[36] = ORP.bytes[2];
  arrayBytes[37] = ORP.bytes[1];
  arrayBytes[38] = ORP.bytes[0];

  uint16_t checksum = 0;

  // Calcular la suma de los bytes
  for (int i = 3; i <= 38; i++)
  {
    checksum += arrayBytes[i];
    // Serial.print(checksum, HEX);
    // Serial.print(" ");
  }
  // Serial.println();

  // Serial.println(checksum, HEX);

  // Tomar los 8 bits menos significativos de la suma
  checksum = checksum & 0xFF;

  // Calcular el complemento a dos
  checksum = (0xFF - checksum);

  arrayBytes[39] = checksum;

  // Serial.println(checksum, HEX);

  for (int i = 0; i < sizeof(arrayBytes); i++)
  {
    if (arrayBytes[i] < 0x10)
    {
      Serial.print("0"); // Agregar un 0 en caso necesario para el formato
    }
    Serial.print(arrayBytes[i], HEX);
    Serial2.write(arrayBytes[i]);

    Serial.print(" ");
    // Serial2.write(arrayBytes[i], HEX);
  }

  Serial.println();
  sensorDO.sleepNAS();
  sensorEC.sleepNAS();
  sensorPH.sleepNAS();

  // Serial.println("***********************************");
}
