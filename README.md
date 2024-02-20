<h1 align="center"> Sensors NAS lib </h1>


![Ochoa y nas](https://github.com/FranklinZamora/DisolvedOxygenNAS/assets/139190968/15cde0c5-1ac3-41b4-be1b-8bb1c6e12295) 

![Static Badge](https://img.shields.io/badge/NAS-green) ![Static Badge](https://img.shields.io/badge/pre_lease-v1-blue)

![Static Badge](https://img.shields.io/badge/AquaNode?style=flat&color=%2303AC13)



## Description

This repository contains a custom Arduino library and corresponding sketch for interfacing with a different sensors via I2C. The `SensorNAS` library, designed specifically for Ochoa Technology, simplifies reading O2, SAT, EC, TDS, SAL, SG, ORP and PH values from the sensor, as well as controlling the sensor's low-power mode and LED state.

## Features

- Easy interface for reading dissolved oxygen and oxygen saturation values.
- Capability to put the sensor into a low-power ("sleep") mode.
- Functionality to control the sensor's built-in LED.
- The provided example sketch allows user interaction via the serial monitor to control the sleep mode and LED state of the sensor.

## Usage

To use this library in your project, you should:

1. Clone this repository.
2. Include the `SensorsNAS.h` header file in your Arduino sketch.
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

## Note

This library has been developed to meet the needs of Ochoa Technology and may not be directly compatible with other companies' hardware.
