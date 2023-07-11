<h1 align="center"> Disolved Oxygen NAS lib </h1>


![Ochoa y nas](https://github.com/FranklinZamora/DisolvedOxygenNAS/assets/139190968/15cde0c5-1ac3-41b4-be1b-8bb1c6e12295) 

![Static Badge](https://img.shields.io/badge/NAS-green) ![Static Badge](https://img.shields.io/badge/pre_lease-v1-blue)


## Description

This repository contains a custom Arduino library and corresponding sketch for interfacing with a Dissolved Oxygen (DO) sensor via I2C. The `OxygenNAS` library, designed specifically for Ochoa Technology, simplifies reading dissolved oxygen and oxygen saturation values from the sensor, as well as controlling the sensor's low-power mode and LED state.

## Features

- Easy interface for reading dissolved oxygen and oxygen saturation values.
- Capability to put the sensor into a low-power ("sleep") mode.
- Functionality to control the sensor's built-in LED.
- The provided example sketch allows user interaction via the serial monitor to control the sleep mode and LED state of the sensor.
- Find sensor addres

## Usage

To use this library in your project, you should:

1. Clone this repository.
2. Include the `OxygenNAS.h` header file in your Arduino sketch.
```c++
#include <OxygenNAS.h>
```
3. Create an instance of the `OxygenNAS` class, specifying your sensor's I2C address.
```c++
OxygenNAS sensor(97); // replace 97 with your sensor's I2C address
```
4. Use the `update`, `getDO`, `getSaturacionOxigeno`, `sleep`, `find`, and `ledControl` methods to interact with the sensor.

The `ledControlNAS()` method is a function in the `OxygenNAS` library that takes a boolean as an argument. It sends a command over I2C to control the state of the sensor's built-in LED. If true is passed to this method, the LED will turn on. If false is passed, the LED will turn off. 

```c++
sensor.ledControlNAS(false); // Turn off the LED
sensor.ledControlNAS(true); // Turn on the LED
```

The  `void find()` method scans the I2C bus and prints out the addresses of all devices found. It can be useful for diagnosing connection issues. If a device is present on the bus and functioning correctly, its address will be displayed when this method is called. If the device's address is not displayed, this may indicate a problem with the device or its connection. After scanning, the method will delay for 5 seconds to give the user time to read the displayed addresses before the program continues. This method should be called in the `setup()` 

```c++
void setup()
{
  Serial.begin(9600);
  sensor.find(); // scans the I2C bus and prints out addresses of all found devices
}
```

Remember, this method does not stop the program from proceeding if no devices are found on the bus. After the 5-second delay, the program will continue with its usual operation.

## Note

This library has been developed to meet the needs of Ochoa Technology and may not be directly compatible with other companies' hardware.
