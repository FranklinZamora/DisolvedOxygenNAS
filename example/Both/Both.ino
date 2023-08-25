#include <SensorsNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/SensorsNAS

SensorsNAS O2sensor(97); // Replace 97 with your sensor's I2C address
SensorsNAS PHsensor(99); // Replace 99 with your sensor's I2C address

void setup()
{
    Serial.begin(9600);
    O2sensor.ledControlNAS(true);
    PHsensor.ledControlNAS(true);
}

void loop()
{
    Serial.print("@/");
    Serial.print(O2sensor.getDO());
    Serial.print("/");
    Serial.print(O2sensor.getSAT());
    Serial.print("/");
    Serial.print(PHsensor.getPH());
    Serial.print("/");
    Serial.println("");
}