
Fluid Networks workshop is using at least 3 different boards, two microcontrollers (MKR 1010 from Arduino, and lately Wio Terminal from Seeedstudio) and a Single Board PC, namely a Raspberry PI (running Node-RED)

## Examples for Wio Terminal

After introducing the different parts of the kit, we started discovering the different uses of the board and of Arduino code using [Tinkergen (online)](https://ide.tinkergen.com/).

Later, we primarly focused on making the board connecrting to the internet, [sending readings in JSON format, using MQTT](https://github.com/vongomben/fluid-networks/blob/master/23_Wio-Terminal-Json-over-MQTT/23_Wio-Terminal-Json-over-MQTT.ino), also [using the screen](https://github.com/vongomben/fluid-networks/blob/master/24_Wio-Terminal-Json-over-MQTT-screen/24_Wio-Terminal-Json-over-MQTT-screen.ino).  


## Examples (for MKR 1010)

Most examples start with a number, and are willing to give a concise and self-explanatory guide to use the sensor with the corresponding board of the kit hookoed up with the MKR Connector Carrier-

- 01 Blink LED
- 02 Pushbutton
- 03 Debounce a Pushbutton
- 04 Servo (loop, knob)
- 05 Analog In & Oit with Serial Port, and how to process data using smoothing and sorting
- 06 OLED uses
- 07 Distance Sensor
- 08 Basic Use of Neopixel
- 09 Basic use of Gesture Sensor
- 10 Using MKR as HID device
- 11 DHT (Temperature & Humidity Sensor)
- 12 Exercise: reading 4 sensors in the serial port
- 13 Basic Use of NFC reader (using Serial)
- 14 TBD
- 15 Basic MQTT use
- 16 MQTT with JSON condition
- 17 Sending a NFC reading using MQTT via JSON
- 18 [Exercise: Sending 2 sensors readings via JSON over MQTT](https://github.com/vongomben/fluid-networks/tree/master/18_2-sensors-Json-over-MQTT)
- 19 [Exercise: Sending 3 sensors readings via JSON over MQTT](https://github.com/vongomben/fluid-networks/tree/master/19_3-sensors-Json-over-MQTT)
- 20 [Exercise: Sending 4 sensors readings via JSON over MQTT](https://github.com/vongomben/fluid-networks/blob/master/20_4-sensors-Json-over-MQTT/20_4-sensors-Json-over-MQTT.ino)
- 21 Blynk Neopixel Example

