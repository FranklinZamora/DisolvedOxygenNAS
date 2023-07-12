#include <SensorsNAS.h>

const uint8_t sensorAddress = 99;
pH_EZO phSensor(sensorAddress);

void setup()
{
    Wire.begin();
    Serial.begin(9600);
}

void loop()
{
  float pH = phSensor.readpH();
  Serial.print("pH: ");
  Serial.println(pH);

  delay(1000);
}   