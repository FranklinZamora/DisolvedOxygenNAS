#include <SensorsNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/SensorsNAS

SensorsNAS sensorDO(97); // Replace 97 with your sensor's I2C address

void setup()
{
  Serial.begin(9600);
  sensorDO.ledControlNAS(true); // Turn ON the LED
}

void loop()
{
  String DO = sensorDO.getDO();
  String saturacion = sensorDO.getSAT();

  Serial.print("DO: ");
  Serial.println(DO);

  Serial.print("Saturacion de oxigeno: ");
  Serial.println(saturacion);
}