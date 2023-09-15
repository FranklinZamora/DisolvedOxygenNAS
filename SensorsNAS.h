#ifndef SensorsNAS_h
#define SensorsNAS_h

#include "Arduino.h"
#include "Wire.h"

class SensorsNAS
{
public:
  SensorsNAS(int add_DO, int add_PH, int add_EC, int add_ORP);
  float getORP();
  float getDO();
  float getSAT();
  float getPH();
  float getEC();
  float getTDS();
  float getSAL();
  float getSG();
  float getTempCompensationDO();
  float getSalCompensationDO();
  float getAtmosphericPressureCompensation();
  byte generateArray(byte MacID[8], SensorsNAS &sensors);
  void begin(SensorsNAS &sensors);
  void sleepNAS(int address);
  void ledControlNAS(bool state, int address);
  void enableMgO2();
  void disableMgO2();
  void enableSatO2();
  void disableSatO2();
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
  int _address1;
  int _address2;
  int _address3;
  int _address4;
  float _DO;
  float _saturacionOxigeno;
  float _PH;
  float _EC;
  float _TDS;
  float _SAL;
  float _SG;
  float _ORP;
  byte _array;
};

#endif
