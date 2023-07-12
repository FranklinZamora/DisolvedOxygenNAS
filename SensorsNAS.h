#ifndef SensorsNAS_h
#define SensorsNAS_h

#include "Arduino.h"
#include "Wire.h"

class OxygenNAS
{
  public:
    OxygenNAS(int address);
    float getDoNAS();
    float getSaturacionOxigenoNAS();
    void sleepNAS();
    void ledControlNAS(bool state); 
    String find();
  private:
    int _address;
    float _DO;
    float _saturacionOxigeno;
};

class pH_EZO {
public:
  pH_EZO(uint8_t sensorAddress = 0x63);
  float readpH();

private:
  uint8_t _sensorAddress;
};



#endif
