#include <SensorsNAS.h>

SensorsNAS O2sensor(97);

void setup()
{
    Serial.begin(9600);
    O2sensor.setName("O2NAS");
    delay(1000);
    Serial.println(O2sensor.getName());
}

void loop()
{
}