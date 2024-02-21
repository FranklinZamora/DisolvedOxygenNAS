<h1 align="center"> AquaNode </h1>

![Sin título (1000 x 500 px)](https://github.com/FranklinZamora/SensorsNAS/assets/139190968/dd34b7ae-60c4-4c73-b87e-0187c1f9dfec)

[![NAS-Board - Library](https://img.shields.io/badge/NAS--Board-Library-blue?logo=c%2B%2B)](https://)
[![NAS - Technology](https://img.shields.io/badge/NAS-Technology-2ea44f)](https://) [![AquaNode](https://img.shields.io/badge/AquaNode-2ea44f)](https://) [![V - 1.0](https://img.shields.io/badge/V-1.0-red)](https://)

## Description

This repository contains a custom Arduino library and corresponding sketch for interfacing with a different sensors via I2C. The `SensorNAS` library, designed specifically for Ochoa Technology, simplifies reading O2, SAT, EC, TDS, SAL, SG, ORP and PH values from the sensor, as well as controlling the sensor's low-power mode and LED state.

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

<h4> Individual values </h4>
/example/Reading.ino

```c++
sensors.updateValue(sensors);
delay(500); // Time to read the variables individually
float _DO = sensors.takingreadDO();
float _SAT = sensors.takingreadSAT();
float _EC = sensors.takingreadEC();
float _TDS = sensors.takingreadTDS();
float _SAL = sensors.takingreadSAL();
float _SG = sensors.takingreadSG();
float _PH = sensors.takingreadPH();
float _ORP = sensors.takingreadORP();
```

## Note

This library has been developed to meet the needs of Ochoa Technology and may not be directly compatible with other companies' hardware.
