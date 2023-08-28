#ifndef SensorsNAS_h
#define SensorsNAS_h

#include "Arduino.h"
#include "Wire.h"

class SensorsNAS
{
public:
  SensorsNAS(int address);
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
  byte generateArray();
  byte calculateChecksum(byte *data, int length);
  void sleepNAS();
  void ledControlNAS(bool state);
  void enableMgO2();
  void disableMgO2();
  void enableSatO2();
  void disableSatO2();
  void clearCalibrationDO();
  void calibrateDO(String calibrationValue);
  void setName(String name);
  bool importCalibrationDO(String calibrationData);
  bool setTempCompensationDO(float temperature);
  bool setSalCompensationDO(float salinity);
  bool setAtmosphericPressureCompensation(float atPressure);
  String find();
  String exportCalibrationDO();
  String getName();
  String deviceInformation();
  String deviceStatus();

private:
  int time;
  String x; // Variable to save received data
  int _address;
  float _DO;
  float _saturacionOxigeno;
  float _PH;
  float _EC;
  float _TDS;
  float _SAL;
  float _SG;
  byte _array;
};

#endif
