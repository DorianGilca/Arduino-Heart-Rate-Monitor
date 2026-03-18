# Smart Heart Rate Monitor (Arduino C++)

A hands-on hardware project I built to experiment with reading and processing physical sensor data in real-time. The system uses an Arduino UNO microcontroller to interface with an optical pulse oximeter sensor, calculating the human heart rate (BPM) and outputting the data to an LCD screen via the I2C protocol.

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

## Software Challenges
The main challenge was the sensor's polling requirement. The MAX30100 requires continuous, high-frequency polling to detect the optical peaks of a heartbeat. Using standard blocking functions like `delay()` for the screen refresh would overflow the I2C buffer and freeze the sensor entirely. 

To solve this, I wrote non-blocking timer logic using the `millis()` function. This allows the sensor's `update()` loop to run continuously in the background, while the LCD display is only triggered to update once per second.

## How to use
1. Wire the components according to the I2C schematic.
2. Install the `LiquidCrystal_I2C` and `MAX30100_PulseOximeter` libraries in the Arduino IDE.
3. Flash the `.ino` code to the Arduino UNO.
4. Place your finger firmly on the MAX30100 sensor and wait a few seconds for the initial BPM reading to calibrate.
