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

    Serial.print("~/");
    Serial.print(DO);
    Serial.print("/");
    Serial.print(sat);
    Serial.print("/");
    Serial.print(Ph);
    Serial.print("/");
    Serial.println("");
    
}