#include <SensorsNAS.h>
#include <Arduino.h>

#define O2 97
#define PH 99
#define EC 100
#define ORP 98

SensorsNAS sensors(O2, PH, EC, ORP);

void setup()
{
    Serial.begin(9600);
    sensors.begin(sensors);
}

void loop()
{
    byte MacID[8] = {0x00, 0x13, 0xA2, 0x00, 0x41, 0xEA, 0x56, 0x3F};
    sensors.generateArray(MacID, sensors);

    delay(2000);
}
