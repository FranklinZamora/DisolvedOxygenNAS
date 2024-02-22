#ifndef SensorsNAS_h
#define SensorsNAS_h

#include "Arduino.h"
#include "Wire.h"
#include "SoftwareSerial.h"

class SensorsNAS
{
public:
  SensorsNAS(int add_DO, int add_PH, int add_EC, int add_ORP);
  float getDO();
  float getORP();
  float getPH();
  float getEC();
  float getTempCompensationDO();
  float getSalCompensationDO();
  float getAtmosphericPressureCompensation();
  float takingreadDO();
  float takingreadSAT();
  float takingreadEC();
  float takingreadTDS();
  float takingreadSAL();
  float takingreadSG();
  float takingreadPH();
  float takingreadORP();
  byte generateArray(byte MacID[8], SensorsNAS &sensors);
  void begin(SensorsNAS &sensors);
  void updateValue(SensorsNAS &sensors);
  void sleepNAS(int address);
  void ledControlNAS(bool state, int address);
  void enableMgO2();
  void disableMgO2();
  void enableSatO2();
  void disableSatO2();
  void enableEC();
  void disableEC();
  void enableTDS();
  void disableTDS();
  void enableSAL();
  void disableSAL();
  void enableSG();
  void disableSG();
  void clearCalibrationDO();
  void calibrateDO(String calibrationValue);
  void setName(String name, int address);
  bool importCalibrationDO(String calibrationData);
  bool setTempCompensationDO(float temperature);
  bool setSalCompensationDO(float salinity);
  bool setAtmosphericPressureCompensation(float atPressure);
  String exportCalibrationDO();
  String getName(int address);
  String deviceInformation(int address);
  String deviceStatus(int address);

  typedef union
  {
    uint8_t value;
    uint8_t bytes[1];
  } UINT8_t;

  typedef union
  {
    uint16_t value;
    uint8_t bytes[4];
  } UINT16_t;

  typedef union
  {
    uint32_t value;
    uint8_t bytes[4];
  } UINT32_t;

private:
  int time;
  String x; // Variable to save received data
  int _address;
  int DO_Address;
  int PH_Address;
  int EC_Address;
  int ORP_Address;
  float _DO;
  float _SAT;
  float _PH;
  float _EC;
  float _TDS;
  float _SAL;
  float _SG;
  float _ORP;
  byte _array;

  SoftwareSerial xbeeSerial;
};

#endif
