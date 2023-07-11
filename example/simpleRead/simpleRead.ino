#include <OxygenNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/OxygenNAS/tree/master/OxygenNASLib
#include <Arduino.h>

OxygenNAS sensor(97); // replace 97 with your sensor's I2C address

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  float DO = sensor.getDoNAS();
  float saturacion = sensor.getSaturacionOxigenoNAS();
  
  Serial.print("DO: ");
  Serial.println(DO);
  
  Serial.print("Saturacion de oxigeno: ");
  Serial.println(saturacion);

  Serial.println("---Low power Mode Zzz---");
  sensor.sleepNAS(); // Put the sensor into low-power mode
  
  delay(10000); // Wait for 10 seconds before next update
}