#include <SensorsNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/SensorsNAS

SensorsNAS sensor(97); // Replace 97 with your sensor's I2C address

void setup()
{
    Serial.begin(9600);

    // Set salinity compensation "51000" in micro siemens
    bool success = sensor.setSalCompensationDO(51000);

    if (success)
    {
        Serial.println("Compensacion de salinidad establecida con exito");
    }
    else
    {
        Serial.println("Fallo al establecer la compensacion de salinidad");
    }

    delay(1000);

    // Read salinity compensation
    Serial.print(sensor.getSalCompensationDO());
    Serial.println(" uS");
}

void loop()
{
}