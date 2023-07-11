#ifndef OxygenNAS_h
#define OxygenNAS_h

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

#endif
