#include <SensorsNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/SensorsNAS

SensorsNAS phSensor(99); // Replace 97 with your sensor's I2C address

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("PH: ");
  Serial.println(phSensor.getPH());
}