#include <SensorsNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/SensorsNAS

SensorsNAS O2sensor(97); // Replace 97 with your sensor's I2C address

void setup()
{
    Serial.begin(9600);
    Wire.begin();
}

void loop()
{
    // Replace "00000066A6CA"
    bool success = O2sensor.importCalibrationDO("00000066A6CA");

    if (success)
    {
        Serial.println("Importación de calibración exitosa");
    }
    else
    {
        Serial.println("Importación de calibración fallida");
    }

    delay(1000);
}
