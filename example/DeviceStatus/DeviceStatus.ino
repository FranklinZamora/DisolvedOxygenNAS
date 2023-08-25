#include <SensorsNAS.h>

SensorsNAS O2Sensor(97);

void setup()
{
    Serial.begin(9600);
    Serial.println(O2Sensor.deviceStatus());
}

void loop()
{
}