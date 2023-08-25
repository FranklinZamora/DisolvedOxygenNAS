#include <SensorsNAS.h>

SensorsNAS ECsensor(100);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println(ECsensor.getEC());
    Serial.println(ECsensor.getTDS());
    Serial.println(ECsensor.getSAL());
    Serial.println(ECsensor.getSG());
    // ECsensor.getEC();
    delay(1000);
}