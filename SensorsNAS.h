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

class PhNAS {
public:
  PhNAS(int address);
  String readPH();

private:
  int _address;
};



#endif
