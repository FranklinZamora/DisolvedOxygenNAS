<h1 align="center"> AquaNode Library </h1>

<a href="https://ibb.co/ngNbR3C"><img src="https://i.ibb.co/6n7mNvB/Banner-git.png" alt="Banner-git" border="0" align = "center"></a>

[![NAS-Board - Library](https://img.shields.io/badge/NAS--Board-Library-blue?logo=c%2B%2B)](https://)
[![NAS - Technology](https://img.shields.io/badge/NAS-Technology-2ea44f)](https://) [![AquaNode](https://img.shields.io/badge/AquaNode-2ea44f)](https://) [![V - 1.0](https://img.shields.io/badge/V-1.0-red)](https://)

## Description

This repository contains a custom Arduino library and correspondingtakingreadDO sketch for interfacing with a different sensors via I2C. The `SensorNAS` library use Atlas Scientific sensors and is designed specifically for Ochoa Technology, simplifies reading O2, SAT, EC, TDS, SAL, SG, ORP and PH values from the sensor, as well as controlling the sensor's low-power mode and LED state.

- Easy interface for reading dissolved oxygen and oxygen saturation values.
- Capability to put the sensor into a low-power ("sleep") mode.
- Functionality to control the sensor's built-in LED.
- The provided example sketch allows user interaction via the serial monitor to control the sleep mode and LED state of the sensor.

## Usage

To use this library in your project, you should:

1. Clone this repository.
2. Include the `SensorsNAS.h` header file in your Script.

```c++
#include <SensorsNAS.h>
```

3. Instantiate the sensors in a class with these addresses:

```c++
#define O2 97
#define PH 98
#define EC 99
#define ORP 100

SensorsNAS sensors(O2, PH, EC, ORP);

```

4. In the setup add begin to sleep the sensors by default

```c++
sensors.begin(sensors);
```

5. Use the generate array method to generate an xbee frame.

```c++
byte MacID[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
sensors.generateArray(MacID, sensors);
```

6. If use this library in Water Wase, use this method:

```c++
sensors.updateValue(sensors);
```

7. Then you can manipulate each value separately.
<h4> Individual values </h4>
/example/Reading.ino

```c++
sensors.updateValue(sensors);
float _DO = sensors.takingreadDO();
float _SAT = sensors.takingreadSAT();
float _EC = sensors.takingreadEC();
float _TDS = sensors.takingreadTDS();
float _SAL = sensors.takingreadSAL();
float _SG = sensors.takingreadSG();
float _PH = sensors.takingreadPH();
float _ORP = sensors.takingreadORP();
```

<h4> Compensation </h4>
Compensation helps us adjust changes in thermal variations, salinity and atmospheric pressure.
Compensation helps us adjust changes in thermal variations, salinity and atmospheric pressure.

```c++
sensorDS18B20.requestTemperatures();
_waterTemp = sensorDS18B20.getTempCByIndex(0);
```

```c++
sensors.setTempCompensationDO(_waterTemp); // Temperature compensation for Dissolved Oxygen
sensors.setTempCompensationEC(_waterTemp); // Temperature compensation for Electric Conductivity
sensors.setTempCompensationPH(_waterTemp); // Temperature compensation for PH
sensors.AtmosphericPressureCompensationDO(pressure); // Pressure compensation for Disolved Oxygen (add sensor value in "pressure")
sensors.setSalCompensationDO(sensors.takingreadSAL()); // Salinity compensation for Dissolved Oxygen
sensors.setTempCompensationDO(_waterTemp); // Temperature compensation for Dissolved Oxygen
sensors.setTempCompensationEC(_waterTemp); // Temperature compensation for Electric Conductivity
sensors.setTempCompensationPH(_waterTemp); // Temperature compensation for PH
sensors.AtmosphericPressureCompensationDO(pressure); // Pressure compensation for Disolved Oxygen (add sensor value in "pressure")
sensors.setSalCompensationDO(sensors.takingreadSAL()); // Salinity compensation for Dissolved Oxygen
```

## Note

This library has been developed to meet the needs of Ochoa Technology and may not be directly compatible with other companies' hardware.
