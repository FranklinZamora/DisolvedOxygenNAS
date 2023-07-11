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
    void ledControlNAS(bool state); // nuevo método para controlar el LED
  private:
    int _address;
    float _DO;
    float _saturacionOxigeno;
};

#endif
