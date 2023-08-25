#include <SensorsNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/SensorsNAS

SensorsNAS sensor(97); //Replace 97 with your sensor's I2C address

void setup()
{
    Serial.begin(9600);
    //Set temperature compensation "28.0"
    bool success = sensor.setTempCompensationDO(28.0);

    if (success)
    {
        Serial.println("Compensacion de temperatura establecida con exito");
    }
    else
    {
        Serial.println("Fallo al establecer la compensacion de temperatura");
    }

    delay(1000); 

    //Get temperature compensatiuon
    Serial.print(sensor.getTempCompensationDO()); 
}

void loop()
{
}
