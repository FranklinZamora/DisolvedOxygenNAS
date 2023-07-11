<h1 align="center"> Disolved Ocygen NAS lib </h1>
# Description 
This repository contains a custom Arduino library and corresponding sketch for interfacing with a Dissolved Oxygen (DO) sensor via I2C. The OxygenNAS library, designed specifically for Ochoa Technology, simplifies reading dissolved oxygen and oxygen saturation values from the sensor, as well as controlling the sensor's low-power mode.

# Features
Easy interface for reading dissolved oxygen and oxygen saturation values.
Capability to put the sensor into a low-power ("sleep") mode.
The provided example sketch allows user interaction via the serial monitor to control the sleep mode of the sensor.

# Usage
To use this library in your project, you should:

Clone this repository.
Include the OxygenNAS.h header file in your Arduino sketch.
Create an instance of the OxygenNAS class, specifying your sensor's I2C address.
Use the update, getDO, getSaturacionOxigeno, and sleep methods to interact with the sensor.

# Example
An example sketch is included, which demonstrates how to read values from the sensor and put the sensor into sleep mode based on user input from the serial monitor.

Remember, the actual usage may vary depending on the specifics of your sensor and project requirements. This library has been developed to meet the needs of Ochoa Technology and may not be directly compatible with other companies' hardware.