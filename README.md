# Arduino Heart Rate Monitor

This is an embedded hardware project that reads and displays human heart rate (BPM) in real-time. The system uses an Arduino UNO microcontroller to interface with an optical pulse oximeter sensor and outputs the data to an LCD screen.

## Hardware Components
* Arduino UNO (ATmega328P)
* MAX30100 Pulse Oximeter and Heart-Rate Sensor
* 1602 LCD Display with I2C module
* Breadboard & Jumper wires

## Hardware Architecture
Both the display and the pulse sensor use the I2C communication protocol. To optimize the wiring, both devices share the same I2C bus on the Arduino:
* SDA (Data) -> Analog Pin A4
* SCL (Clock) -> Analog Pin A5
* Powered via the 5V Arduino pin.

## Software Implementation
The code is written in C++ using the Arduino IDE. 
A critical aspect of the software design was avoiding blocking functions like `delay()`. Since the MAX30100 requires continuous polling at a very high frequency to detect the optical peaks of the heartbeat, using delays would overflow the I2C buffer and freeze the sensor. Instead, I implemented a non-blocking timer using the `millis()` function, allowing the sensor's `update()` loop to run continuously while updating the LCD display only once per second.

## How to use
1. Wire the components according to the provided schematic.
2. Install the `LiquidCrystal_I2C` and `MAX30100_PulseOximeter` libraries in your Arduino IDE.
3. Flash the `.ino` code to the Arduino UNO.
4. Place your finger firmly on the MAX30100 sensor and wait a few seconds for the initial BPM reading to calibrate and appear on the screen.
