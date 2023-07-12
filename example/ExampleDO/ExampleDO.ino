#include <SensorsNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/DisolvedSensorsNAS.git
#include <Arduino.h>

OxygenNAS sensorDO(97); // replace 97 with your sensor's I2C address

void setup()
{
  Serial.begin(9600);
  sensorDO.find(); // Busca todos los dispositivos en el bus I2C
  sensorDO.ledControlNAS(true); // Turn off the LED
}

void loop()
{
  float DO = sensorDO.getDoNAS();
  float saturacion = sensorDO.getSaturacionOxigenoNAS();
  
  Serial.print("DO: ");
  Serial.println(DO);
  
  Serial.print("Saturacion de oxigeno: ");
  Serial.println(saturacion);

  Serial.println("---Low power Mode Zzz---");
  
  delay(5000); // Wait for 10 seconds before next update
}