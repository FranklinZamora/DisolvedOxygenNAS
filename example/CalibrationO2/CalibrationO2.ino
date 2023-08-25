#include <SensorsNAS.h> //Download library made by ochoa technology in: https://github.com/FranklinZamora/SensorsNAS

SensorsNAS O2sensor(97); //Replace 97 with your sensor's I2C address

void setup()
{
    Serial.begin(9600);

}

void loop()
{
    O2sensor.calibrateDO("0");
    float DO = O2sensor.getDoNAS();
    Serial.println(DO);
    delay(1000);

    O2sensor.clearCalibrationDO();
    float DO2 = O2sensor.getDoNAS();
    Serial.println(DO2);

    delay(1000);
}