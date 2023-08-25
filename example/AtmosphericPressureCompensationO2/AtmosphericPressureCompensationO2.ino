#include <SensorsNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/SensorsNAS

SensorsNAS sensor(97); //Replace 97 with your sensor's I2C address

void setup()
{
    Serial.begin(9600);

    // Set Atmospheritc Pressure Compensation
    bool success = sensor.setAtmosphericPressureCompensation(97.2);

    if (success)
    {
        Serial.println("Compensacion de presion atmosferica establecida con exito");
    }
    else
    {
        Serial.println("Fallo al establecer la compensacion de presion atmosferica");
    }

    delay(1000); 

    Serial.print(sensor.getAtmosphericPressureCompensation());
}

void loop()
{
}