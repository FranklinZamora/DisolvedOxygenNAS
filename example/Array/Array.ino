#include <SensorsNAS.h>

SensorsNAS DOsensor(97);
SensorsNAS PHsensor(99);
SensorsNAS ECsensor(100);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    ECsensor.generateArray();
}
