#include "SensorsNAS.h"
#include <Arduino.h>
#include <Wire.h>

SensorsNAS::SensorsNAS(int address)
{
  _address = address;
  Wire.begin();
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
byte SensorsNAS::generateArray()
{
  SensorsNAS DOsensor(97);
  SensorsNAS PHsensor(99);
  SensorsNAS ECsensor(100);

  String EC, TDS, SAL, SG, PH, DO, SAT;

  EC = ECsensor.getEC();
  TDS = ECsensor.getTDS();
  SAL = ECsensor.getSAL();
  SG = ECsensor.getSG();
  PH = PHsensor.getPH();
  DO = DOsensor.getDO();
  SAT = DOsensor.getSAT();

  String sensado = "H/" + EC + "/" + TDS + "/" + SAL + "/" + SG + "/" + PH + "/" + DO + "/" + SAT + "/";
  // String sensado = "AA";
  byte additionalBytes[] = {0x7E};
  byte fillerBytes[] = {0x10, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xFF, 0xFE, 0x00, 0x00};

  int originalLength = sensado.length();
  byte array[originalLength];
  // Convertir cada caracter a su valor en hexadecimal
  for (int i = 0; i < originalLength; i++)
  {
    if (sensado.charAt(i) == '.')
    { // Agregar el valor del punto decimal como 0x2E
      array[i] = 0x2E;
    }
    else
    {
      array[i] = sensado.charAt(i) - '0'; // Restar el valor ASCII de '0' para obtener el valor en decimal
      array[i] += 0x30;                   // Sumar 0x30 para obtener el valor en hexadecimal correspondiente
    }
  }

  int additionalLength = sizeof(additionalBytes);
  int fillerLength = sizeof(fillerBytes);
  int totalSize = originalLength + fillerLength;
  byte lengthBytes[] =
      {
          (byte)(totalSize >> 8),
          (byte)(totalSize)};

  byte concatenatedArray[additionalLength + 2 + totalSize + 1]; // 2 bytes for total size, 1 byte for checksum

  int resultIndex = 0;

  // Add additional bytes
  for (int i = 0; i < additionalLength; i++)
  {
    concatenatedArray[resultIndex++] = additionalBytes[i];
  }

  // Add total size bytes
  concatenatedArray[resultIndex++] = lengthBytes[0];
  concatenatedArray[resultIndex++] = lengthBytes[1];

  // Add filler bytes
  for (int i = 0; i < fillerLength; i++)
  {
    concatenatedArray[resultIndex++] = fillerBytes[i];
  }

  // Add array bytes
  for (int i = 0; i < originalLength; i++)
  {
    concatenatedArray[resultIndex++] = array[i];
  }

  // Calculate checksum
  byte checksum = calculateChecksum(concatenatedArray + 3, resultIndex - 3); // Exclude the first 3 bytes

  // Add checksum to the end
  concatenatedArray[resultIndex++] = checksum;

  // Print the concatenated array for verification
  for (int i = 0; i < resultIndex; i++)
  {
    Serial.print(concatenatedArray[i], HEX);
    Serial.print(" ");
  }

  Serial.println();
  Serial.println(sensado);
}

byte SensorsNAS::calculateChecksum(byte *data, int length)
{
  byte checksum = 0;
  for (int i = 0; i < length; i++)
  {
    checksum += data[i];
  }
  return 0xFF - checksum;
}