#include <OxygenNAS.h>

OxygenNAS sensor(97); // replace 97 with your sensor's I2C address hex (0x61)

void setup()
{
  Serial.begin(9600);
  sensor.find(); // Busca todos los dispositivos en el bus I2C
}

void loop()
{
  float DO = sensor.getDoNAS();
  float saturacion = sensor.getSaturacionOxigenoNAS();
  
  Serial.print("DO: ");
  Serial.println(DO);
  
  Serial.print("Saturacion de oxigeno: ");
  Serial.println(saturacion);
  
  delay(1000);
}