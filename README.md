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

## Usage

To use this library in your project, you should:

1. Clone this repository.
2. Include the `OxygenNAS.h` header file in your Arduino sketch.
3. Create an instance of the `OxygenNAS` class, specifying your sensor's I2C address.
4. Use the `update`, `getDO`, `getSaturacionOxigeno`, `sleep`, and `ledControl` methods to interact with the sensor.

The `ledControl` method is a function in the `OxygenNAS` library that takes a boolean as an argument. It sends a command over I2C to control the state of the sensor's built-in LED. If true is passed to this method, the LED will turn on. If false is passed, the LED will turn off. Please refer to your sensor's documentation to ensure the correct command is sent for your specific model.

## Note

This library has been developed to meet the needs of Ochoa Technology and may not be directly compatible with other companies' hardware.
