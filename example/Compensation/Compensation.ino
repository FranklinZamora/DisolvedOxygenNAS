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

float _waterTemp = 0;
float _DO = 0;
float _SAT = 0;
float _EC = 0;
float _TDS = 0;
float _SAL = 0;
float _SG = 0;
float _PH = 0;
float _ORP = 0;

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

    sensors.setTempCompensationDO(_waterTemp); // Temperature compensation for Dissolved Oxygen
    sensors.setTempCompensationEC(_waterTemp); // Temperature compensation for Electric Conductivity
    sensors.setTempCompensationPH(_waterTemp); // Temperature compensation for PH

    Serial.println("Temperature Compensation: ");
    Serial.print("DO: ");
    Serial.print(sensors.getTempCompensationDO());
    Serial.print("\tEC: ");
    Serial.print(sensors.getTempCompensationEC());
    Serial.print("\tPH: ");
    Serial.println(sensors.getTempCompensationPH());

    Serial.println("Pressure Compensation for DO: ");
    Serial.println(sensors.getAtmosphericPressureCompensationDO()); // Pressure compensation for Disolved Oxygen

    Serial.println("\nRequesting data, please wait a moment...");

    sensors.updateValue(sensors);
    sensors.setSalCompensationDO(sensors.takingreadSAL()); // Salinity compensation for Dissolved Oxygen
    Serial.print("Salinity compensation for DO: ");
    Serial.println(sensors.getSalCompensationDO());

    _DO = sensors.takingreadDO();
    _SAT = sensors.takingreadSAT();
    _EC = sensors.takingreadEC();
    _TDS = sensors.takingreadTDS();
    _SAL = sensors.takingreadSAL();
    _SG = sensors.takingreadSG();
    _PH = sensors.takingreadPH();
    _ORP = sensors.takingreadORP();

    Serial.print("DO: ");
    Serial.print(_DO);
    Serial.print("\tSAT: ");
    Serial.print(_SAT);
    Serial.print("\tEC: ");
    Serial.print(_EC);
    Serial.print("\tTDS: ");
    Serial.print(_TDS);
    Serial.print("\tSAL: ");
    Serial.print(_SAL);
    Serial.print("\tSG: ");
    Serial.print(_SG);
    Serial.print("\tPH: ");
    Serial.print(_PH);
    Serial.print("\tORP: ");
    Serial.print(_ORP);
    Serial.println();
    Serial.println("-----------------------------------------------------------------------------------------------------------------------------");
}