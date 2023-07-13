#include <SensorsNAS.h>

PhNAS PHsensor(99);
OxygenNAS DOsensor(97);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    float DO = DOsensor.getDoNAS();
    float sat = DOsensor.getSaturacionOxigenoNAS();
    float Ph = PHsensor.readPH();

    Serial.println(String(DO) + "/" + String(sat) + "/" + String(Ph));
    
}