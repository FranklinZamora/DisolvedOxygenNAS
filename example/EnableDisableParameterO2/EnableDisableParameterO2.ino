#include <SensorsNAS.h>

SensorsNAS O2sensor(97);
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    O2sensor.enableMgO2();
    Serial.println(O2sensor.getDO());
    delay(1000);
    O2sensor.disableMgO2();
    Serial.println(O2sensor.getDO());
    delay(1000);
    O2sensor.enableSatO2();
    Serial.println(O2sensor.getSAT());
    delay(1000);
    O2sensor.disableSatO2();
    Serial.println(O2sensor.getSAT());
    delay(1000);
}