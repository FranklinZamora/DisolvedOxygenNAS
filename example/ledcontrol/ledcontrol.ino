#include <OxygenNAS.h>

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
  sensor.ledControlNAS(false); // Turn off the LED
  
  //delay(3000);
  //sensor.ledControlNAS(true); // Turn on the LED
  //Serial.println("LED is on.");
  
}