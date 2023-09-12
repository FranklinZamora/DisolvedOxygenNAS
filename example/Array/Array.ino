#include <SensorsNAS.h>
#include <Arduino.h>

SensorsNAS DOsensor(97);
SensorsNAS ORPsensor(98);
SensorsNAS PHsensor(99);
SensorsNAS ECsensor(100);

void setup()
{
    Serial.begin(9600);
    // Serial2.begin(9600);
}

void loop()
{
    byte MacID[8] = {0x00, 0x13, 0xA2, 0x00, 0x41, 0xEA, 0x56, 0x3F};
    ORPsensor.generateArray(MacID, DOsensor, PHsensor, ECsensor, ORPsensor);
    delay(2000);
}
