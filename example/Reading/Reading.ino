#include <SensorsNAS.h>

#define O2 97
#define PH 99
#define EC 100
#define ORP 98
#define ONE_WIRE_BUS 2

SensorsNAS sensors(O2, PH, EC, ORP);

void setup()
{
    Serial.begin(9600);
    sensors.begin(sensors);
}

void loop()
{
    sensors.updateValue(sensors);
    delay(500);
    float _DO = sensors.takingreadDO();
    float _SAT = sensors.takingreadSAT();
    float _EC = sensors.takingreadEC();
    float _TDS = sensors.takingreadTDS();
    float _SAL = sensors.takingreadSAL();
    float _SG = sensors.takingreadSG();
    float _PH = sensors.takingreadPH();
    float _ORP = sensors.takingreadORP();

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