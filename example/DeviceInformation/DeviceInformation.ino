#include <SensorsNAS.h>

SensorsNAS O2sensor(97);
void setup()
{
    Serial.begin(9600);
    Serial.println(O2sensor.deviceInformation());
}

void loop()
{
}