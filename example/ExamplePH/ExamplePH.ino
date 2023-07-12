#include <SensorsNAS.h>

PhNAS phSensor(99);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
  String pH = phSensor.readPH();  // Lee el valor de pH como flotante
  float pH_ = pH.toFloat();
  Serial.println(pH_);
  Serial.println(pH);

  delay(1000);
}   