#include <SensorsNAS.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define O2 97
#define PH 99
#define EC 100
#define ORP 98

SensorsNAS sensors(O2, PH, EC, ORP);

const int pinDatosDQ = 2;

OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

float _waterTemp;
float _DO;
float _SAT;
float _SAL;

void setup()
{
    Serial.begin(9600);
    sensors.begin(sensors);
    sensorDS18B20.begin();           // DSB18 (Temperature)
    sensorDS18B20.setResolution(10); // Steps for Water Temperature
}

void loop()
{
    sensorDS18B20.requestTemperatures();
    _waterTemp = sensorDS18B20.getTempCByIndex(0);

    Serial.print("Temperature DSB18: ");
    Serial.println(_waterTemp);

    sensors.setTempCompensationDO(_waterTemp);
    Serial.print("Temperature Compensation: ");
    Serial.println(sensors.getTempCompensationDO());

    sensors.updateValue(sensors);
    _DO = sensors.takingreadDO();
    _SAT = sensors.takingreadSAT();
    _SAL = sensors.takingreadSAL();

    sensors.setSalCompensationDO(_SAL);
    Serial.print("Salinity Compensation: ");
    Serial.println(sensors.getSalCompensationDO());
    Serial.print("Salinity: ");
    Serial.println(_SAL);

    Serial.print("Dissolved Oxygen: ");
    Serial.print(_DO);
    Serial.print("\tSaturation: ");
    Serial.println(_SAT);
}