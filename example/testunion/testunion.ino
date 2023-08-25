#include <SensorsNAS.h>

SensorsNAS sensorDO(97);
SensorsNAS sensorPH(99);
SensorsNAS sensorEC(100);

typedef union
{
    uint16_t value;
    uint8_t bytes[2];
} FLOAT16_t;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    FLOAT16_t DisolvedOx, SaturationOx, Ph;

    DisolvedOx.value = sensorDO.getDO() * 100;
    SaturationOx.value = sensorDO.getSAT() * 100;
    Ph.value = sensorPH.getPH() * 100;

    Serial.println("-------------");
    Serial.println(DisolvedOx.bytes[1], HEX);
    Serial.println(DisolvedOx.bytes[0], HEX);
    Serial.println("-------------");
    Serial.println(SaturationOx.bytes[1], HEX);
    Serial.println(SaturationOx.bytes[0], HEX);
    Serial.println("-------------");
    Serial.println(Ph.bytes[1], HEX);
    Serial.println(Ph.bytes[0], HEX);
    Serial.println("-------------");

    Serial.println(sensorEC.getEC());

    delay(1000);
}
