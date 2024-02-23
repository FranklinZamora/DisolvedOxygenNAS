#include "SensorsNAS.h"

SensorsNAS::SensorsNAS(int add_DO, int add_PH, int add_EC, int add_ORP) : xbeeSerial(12, 11)
{
  DO_Address = add_DO;
  PH_Address = add_PH;
  EC_Address = add_EC;
  ORP_Address = add_ORP;

#ifdef __AVR_ATmega2560__
  Serial2.begin(9600);
#endif
#ifdef __AVR_ATmega328P__
  xbeeSerial.begin(9600);
#endif
}

void SensorsNAS::begin(SensorsNAS &sensors)
{
  Wire.begin();
  enableMgO2();
  enableSatO2();
  enableEC();
  enableTDS();
  enableSAL();
  enableSG();

  sensors.sleepNAS(97);
  sensors.sleepNAS(98);
  sensors.sleepNAS(99);
  sensors.sleepNAS(100);
}

float SensorsNAS::getDO()
{
  byte code = 0;
  char do_data[32];
  byte in_char = 0;
  int i = 0;

  char *DO;
  char *sat;

  // Send command to read DO data to sensor
  Wire.beginTransmission(DO_Address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 600)
  {
    // Wait
  }
  Wire.requestFrom(DO_Address, 32, 1);
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
    do_data[i] = in_char;  // load this byte into our array.
    i += 1;                // incur the counter for the array element.
    if (in_char == 0)
    {        // if we see that we have been sent a null command.
      i = 0; // reset the counter i to 0.
      break; // exit the while loop.
    }
  }

  DO = strtok(do_data, ",");
  sat = strtok(NULL, ",");

  _DO = atof(DO);
  _SAT = atof(sat);
}

float SensorsNAS::takingreadDO()
{
  return _DO;
}

float SensorsNAS::takingreadSAT()
{
  return _SAT;
}

void SensorsNAS::calibrateDO(String calibrationValue)
{
  String command = "CAL," + calibrationValue;
  Wire.beginTransmission(DO_Address);
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
  Wire.requestFrom(DO_Address, 1);

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
  Wire.beginTransmission(DO_Address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }

  // Request data from sensor
  byte response;
  Wire.requestFrom(DO_Address, 1);
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
  Wire.beginTransmission(DO_Address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
    // Wait
  }

  // Request data from sensor
  Wire.requestFrom(DO_Address, 32, 1);

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

  Wire.beginTransmission(DO_Address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 900)
  {
    // Wait
  }

  // Request data from sensor
  byte response[20];
  Wire.requestFrom(DO_Address, 20);
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

float SensorsNAS::setTempCompensationDO(float temperature)
{
  String command = "T,";
  command += String(temperature, 1); // Convert value to string

  Wire.beginTransmission(DO_Address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 300)
  {
    // Wait
  }

  // Request data from sensor
  byte response[20];
  Wire.requestFrom(DO_Address, 20);
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
  Wire.beginTransmission(DO_Address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 500)
  {
    // Wait
  }

  // Request data from sensor
  Wire.requestFrom(DO_Address, 20);
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

float SensorsNAS::setSalCompensationDO(float saladditionalBytesy)
{
  String command = "S,";
  command += String(saladditionalBytesy, 1);

  Wire.beginTransmission(DO_Address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 300)
  {
    // Wait
  }

  // Request data from sensor
  byte response[20];
  Wire.requestFrom(DO_Address, 20);
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
  Wire.beginTransmission(DO_Address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 500)
  {
    // Wait
  }
  // Request data from sensor
  Wire.requestFrom(DO_Address, 20);
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

  Wire.beginTransmission(DO_Address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 300)
  {
    // Wait
  }

  // Request data from sensorr
  byte response[20];
  Wire.requestFrom(DO_Address, 20);
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
  Wire.beginTransmission(DO_Address);
  Wire.write(command.c_str());
  Wire.endTransmission();

  unsigned long startTime = millis();

  while (millis() - startTime < 500)
  {
    // Wait
  }

  // Request data from sensor
  Wire.requestFrom(DO_Address, 20);
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

void SensorsNAS::setName(String name, int address)
{
  address = _address;
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

String SensorsNAS::getName(int address)
{
  _address = address;
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
  Wire.beginTransmission(DO_Address);
  Wire.write("O,mg,1"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }
  Serial.println("[SENSORS]: O2 Enable");
}

void SensorsNAS::disableMgO2()
{
  Wire.beginTransmission(DO_Address);
  Wire.write("O,mg,0"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();
  unsigned long startTime = millis();
  while (millis() - startTime < 400)
  {
    // Wait
  }
  Serial.println("[SENSORS]: O2 Disable");
}

void SensorsNAS::enableSatO2()
{
  Wire.beginTransmission(DO_Address);
  Wire.write("O,%,1"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();
  unsigned long startTime = millis();
  while (millis() - startTime < 400)
  {
    // Wait
  }
  Serial.println("[SENSORS]: SAT Enable");
}

void SensorsNAS::disableSatO2()
{
  Wire.beginTransmission(DO_Address);
  Wire.write("O,%,0"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();
  unsigned long startTime = millis();
  while (millis() - startTime < 400)
  {
    // Wait
  }
  Serial.println("[SENSORS]: SAT Disable");
}

float SensorsNAS::getPH()
{
  byte data[6];

  Wire.beginTransmission(PH_Address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
  }

  Wire.requestFrom(PH_Address, 6, 1);
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

float SensorsNAS::takingreadPH()
{
  return _PH;
}

float SensorsNAS::getEC()
{
  byte code = 0;
  char ec_data[32]; // we make a 32 byte character array to hold incoming data from the EC circuit.
  byte in_char = 0;
  byte i = 0;
  char *ec;
  char *tds;
  char *sal;
  char *sg;

  Wire.beginTransmission(EC_Address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
  }

  Wire.requestFrom(EC_Address, 32, 1);
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
  tds = strtok(NULL, ",");
  sal = strtok(NULL, ",");
  sg = strtok(NULL, ",");

  _EC = atof(ec);
  _TDS = atof(tds);
  _SAL = atof(sal);
  _SG = atof(sg);

} // End

void SensorsNAS::enableEC()
{
  Wire.beginTransmission(EC_Address);
  Wire.write("O,EC,1"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 400)
  {
    // Wait
  }
  Serial.println("[SENSORS]: EC Enable");
}

void SensorsNAS::disableEC()
{
  Wire.beginTransmission(EC_Address);
  Wire.write("O,EC,0"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 400)
  {
    // Wait
  }
  Serial.println("[SENSORS]: EC Disable");
}

void SensorsNAS::enableTDS()
{
  Wire.beginTransmission(EC_Address);
  Wire.write("O,TDS,1"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 400)
  {
    // Wait
  }
  Serial.println("[SENSORS]: TDS Enable");
}

void SensorsNAS::disableTDS()
{
  Wire.beginTransmission(EC_Address);
  Wire.write("O,TDS,0"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }
  Serial.println("[SENSORS]: TDS Disable");
}

void SensorsNAS::enableSAL()
{
  Wire.beginTransmission(EC_Address);
  Wire.write("O,S,1"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }
  Serial.println("[SENSORS]: SAL Enable");
}

void SensorsNAS::disableSAL()
{
  Wire.beginTransmission(EC_Address);
  Wire.write("O,S,0"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }
  Serial.println("[SENSORS]: SAL Disable");
}

void SensorsNAS::enableSG()
{
  Wire.beginTransmission(EC_Address);
  Wire.write("O,SG,1"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }
  Serial.println("[SENSORS]: SG Enable");
}

void SensorsNAS::disableSG()
{
  Wire.beginTransmission(EC_Address);
  Wire.write("O,SG,0"); // Habilitar parámetros en la cadena de salida
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 300)
  {
    // Wait
  }
  Serial.println("[SENSORS]: SG Disable");
}

float SensorsNAS::takingreadEC()
{
  return _EC;
}

float SensorsNAS::takingreadTDS()
{
  return _TDS;
}

float SensorsNAS::takingreadSAL()
{
  return _SAL;
}

float SensorsNAS::takingreadSG()
{
  return _SG;
}

void SensorsNAS::sleepNAS(int address)
{
  _address = address;
  Wire.beginTransmission(_address);
  Wire.write("sleep");
  Wire.endTransmission();
}

void SensorsNAS::ledControlNAS(bool state, int address)
{
  _address = address;
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

String SensorsNAS::deviceInformation(int address)
{
  _address = address;
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

String SensorsNAS::deviceStatus(int address)
{
  _address = address;
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

  Wire.beginTransmission(ORP_Address);
  Wire.write("R");
  Wire.endTransmission();

  unsigned long startTime = millis();
  while (millis() - startTime < 900)
  {
  }

  Wire.requestFrom(ORP_Address, 32, 1);
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

float SensorsNAS::takingreadORP()
{
  return _ORP;
}

byte SensorsNAS::generateArray(byte MacID[8], SensorsNAS &sensors)
{

  UINT32_t EC, TDS, ORP, UNSIG;
  UINT16_t DisolvedOx, SaturationOx, Ph, SAL;
  UINT8_t SG;

  sensors.getDO(); // Hablar a la funcion para obtener los 2 valores

  DisolvedOx.value = _DO * 100;
  SaturationOx.value = _SAT * 100;

  sensors.getEC(); // Hablar a la funcion para obtener los 4 valores

  EC.value = _EC * 100;
  TDS.value = _TDS * 100;
  SAL.value = _SAL * 100;
  SG.value = _SG * 100;
  Ph.value = sensors.getPH() * 100;
  ORP.value = sensors.getORP() * 100;

  if (ORP.value < 0)
  {
    ORP.value = ORP.value * -1;
    UNSIG.bytes[0] = 0x00;
  }
  else
  {
    UNSIG.bytes[0] = 0x01;
  }

  byte arrayBytes[41];

  arrayBytes[0] = 0x7E;     // Start
  arrayBytes[1] = 0x00;     // length 1
  arrayBytes[2] = 0x25;     // Length 2
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
  arrayBytes[18] = 0x3F;
  arrayBytes[19] = DisolvedOx.bytes[1];
  arrayBytes[20] = DisolvedOx.bytes[0];

  arrayBytes[21] = SaturationOx.bytes[1];
  arrayBytes[22] = SaturationOx.bytes[0];

  arrayBytes[23] = Ph.bytes[1];
  arrayBytes[24] = Ph.bytes[0];

  arrayBytes[25] = EC.bytes[3];
  arrayBytes[26] = EC.bytes[2];
  arrayBytes[27] = EC.bytes[1];
  arrayBytes[28] = EC.bytes[0];

  arrayBytes[29] = TDS.bytes[3];
  arrayBytes[30] = TDS.bytes[2];
  arrayBytes[31] = TDS.bytes[1];
  arrayBytes[32] = TDS.bytes[0];

  arrayBytes[33] = SAL.bytes[1];
  arrayBytes[34] = SAL.bytes[0];

  arrayBytes[35] = SG.bytes[0]; // End payload
  arrayBytes[36] = UNSIG.bytes[0];
  arrayBytes[37] = ORP.bytes[2];
  arrayBytes[38] = ORP.bytes[1];
  arrayBytes[39] = ORP.bytes[0];

  uint16_t checksum = 0;

  // Calcular la suma de los bytes
  for (int i = 3; i <= 39; i++)
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

  arrayBytes[40] = checksum;

  // Serial.println(checksum, HEX);

  for (int i = 0; i < sizeof(arrayBytes); i++)
  {
    if (arrayBytes[i] < 0x10)
    {
      Serial.print("0"); // Agregar un 0 en caso necesario para el formato
    }
    Serial.print(arrayBytes[i], HEX);

#ifdef __AVR_ATmega5660__
    Serial2.write(arrayBytes[i]);
    Serial2.print(" ");
#endif
    Serial.print(" ");
  }

  Serial.println();

#ifdef __AVR_ATmega2560__
  Serial2.write(arrayBytes, sizeof(arrayBytes));
#endif

#ifdef __AVR_ATmega328P__
  xbeeSerial.write(arrayBytes, sizeof(arrayBytes));
#endif

  sensors.sleepNAS(97);
  sensors.sleepNAS(98);
  sensors.sleepNAS(99);
  sensors.sleepNAS(100);

  // Serial.println("***********************************");
}

void SensorsNAS::updateValue(SensorsNAS &sensors) // This method is for WaterWise
{
  getDO();
  getEC();
  getPH();
  getORP();
}
