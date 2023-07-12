#include <SensorsNAS.h>

PhNAS phSensor(99);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
  Serial.print("PH: ");
  Serial.println(phSensor.readPH());  // Lee el valor de pH como flotante
  
  delay(1000);
}   