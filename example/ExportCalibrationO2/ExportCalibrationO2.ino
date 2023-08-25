#include <SensorsNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/SensorsNAS

SensorsNAS O2sensor(97); // Replace 97 with your sensor's I2C address

void setup()
{
    Serial.begin(9600);

    O2sensor.calibrateDO("0");

    delay(1000);

    Serial.println(O2sensor.getDO());

    delay(1000);

    Serial.println("Calibration export: " + String(O2sensor.exportCalibrationDO()));

    delay(1000);
}

void loop()
{
}