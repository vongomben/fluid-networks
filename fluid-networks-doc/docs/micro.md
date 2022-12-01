
## Kit (with wiki links)

Fluid Networks workshop started as an online-only remote workshop. Lately became requested by on-life courses and it slowly became diversified based on the different course applying for it. 

Up to now we have two microcontrollers heavily used and supported: [Seeedstudio's Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/) and [Arduino MKR 1010](https://store.arduino.cc/arduino-mkr-wifi-1010). 

Most (if not all) sensors and actuators nodes are part of the widest index of electronics nodes produced by **Seeedstudio**: the [Grove Prototyping System](http://wiki.seeedstudio.com/Grove_System/)


Note: some parts of the kit were dismissed, as labelled and versioned

| Ref | Description |      Label     |  Library | Version |
|:---:|:-------------------------------------------------------:|:--------------:|:-:|:-:|
|   1 |                         [MKR1010](https://store.arduino.cc/arduino-mkr-wifi-1010)                         |       MIC      |   | v.2
|   2 |                  [Grove connector carrier](https://www.arduino.cc/en/Guide/MKRConnectorCarrier)                 |      CONN      |   | v.2
|   3 |                     Micro USB cable                     |      CONN      |   | v.2
|   4 |                  [Grove - Red LED Button](https://wiki.seeedstudio.com/Grove-LED_Button/)                 | INPUT / OUTPUT |   | v.2
|   5 |                [Grove - OLED Display 0.96"](https://wiki.seeedstudio.com/Grove-OLED-Display-0.96-SSD1315/)               |     DISPLAY    |   | v.2
|   6 |                   [Grove - RGB LED Ring](https://wiki.seeedstudio.com/Grove%20-%20RGB%20LED%20Ring%20%2820%20-%20WS2813%20Mini%29/)                  |     OUTPUT     |  [Adafruit Neopixel Library](https://github.com/adafruit/adafruit_NeoPixel)  | v.2
|   7 |            [Grove - Ultrasonic Distance Sensor](https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/)           |      INPUT     |  [Grove Ultrasonic Library](https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger/archive/master.zip) | v.2
|   8 |    [Grove - Light Sensor v1.2 - LS06-S phototransistor](https://wiki.seeedstudio.com/Grove-Light_Sensor/)   |      INPUT     |   | v.2
|   9 |      [Grove - Temperature & Humidity Sensor (DHT11)](https://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/)      |      INPUT     | [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library) and [Adafruit Unified Sensor Lib](https://github.com/adafruit/Adafruit_Sensor)  | v.2
|  10 |                       [Grove - NFC](https://wiki.seeedstudio.com/Grove_NFC/)                       |      INPUT     | [Download Library from Repository](https://github.com/vongomben/fluid-networks/raw/master/Libraries/NFC.zip)  | v.2
|  11 |                      [Grove - Servo](https://wiki.seeedstudio.com/Grove-Servo/)                      |     OUTPUT     |   | v.2
|  12 |               [Grove - 2-Channel SPDT Relay](https://wiki.seeedstudio.com/Grove-2-Channel_SPDT_Relay/)              |     OUTPUT     |   | v.2
|  13 | Grove - Universal 4 Pin Buckled 50cm Cable (5 PCs Pack) |       HUB      |   | v.2
|  14 |                     [Grove - I2C Hub](https://wiki.seeedstudio.com/Grove-I2C_Hub/)                     |       HUB      |   | v.2
|  15 |      [Grove - Gesture Sensor for Arduino (PAJ7620U2)](https://wiki.seeedstudio.com/Grove-Gesture_v1.0/)     |      INPUT     |   | dismissed
|  16 |[Grove - IMU 9DOF v2.0 - MPU-9250](https://wiki.seeedstudio.com/Grove-IMU_9DOF_v2.0/)| INPUT |   | v.2
|  17 |[Grove - Analog Microphone (MEMS)](https://wiki.seeedstudio.com/Grove-Analog-Microphone/) |INPUT |  | v.2

# Examples

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


##

|<div style="width:1px">ref</div> |<div style="width:1px">description</div>|label|Category|Library|<div style="width:1px">v. 1</div> |<div style="width:1px">v.2</div>|<div style="width:1px">bio-tech</div>|<div style="width:1px">tinyML</div>|<div style="width:1px">home</div>|
|:----|:----|:----|:----|:----|:----|:----|:----|:----|:----|
|1|MKR1010|MIC| | |:material-check:|:material-check:| | | |
|2|Grove connector carrier|CONN| | |:material-check:|:material-check:| | | |
|3|Micro USB cable|CONN| | |:material-check:|:material-check:| | | |
|4|Grove - Red LED Button|I /O|sight, touch| |:material-check:|:material-check:| | | |
|5|Grove - OLED Display 0.96"|DIPLAY|sight| |:material-check:|:material-check:| | | |
|6|Grove - RGB LED Ring|OUTPUT|sight|Adafruit Neopixel Library|:material-check:|:material-check:| |:material-check:|:material-check:|
|7|Grove - Ultrasonic Distance Sensor|INPUT|proximity|Grove Ultrasonic Library|:material-check:|:material-check:| | | |
|8|Grove - Light Sensor v1.2 - LS06-S phototransistor|INPUT|sight, proximity| |:material-check:|:material-check:| |:material-check:| |
|9|Grove - Temperature & Humidity Sensor (DHT11)|INPUT|environmental|DHT Sensor Library and Adafruit Unified Sensor Lib|:material-check:|:material-check:| | |:material-check:|
|10|Grove - NFC|INPUT|proximity|Download Library from Repository|:material-check:|:material-check:| | | |
|11|Grove - Servo|OUTPUT|touch| |:material-check:|:material-check:| | |:material-check:|
|12|Grove - 2-Channel SPDT Relay|OUTPUT| | |:material-check:|:material-check:| | |:material-check:|
|13|Grove - Universal 4 Pin Buckled 50cm Cable (5 PCs Pack)|HUB| | |:material-check:|:material-check:| | | |
|14|Grove - I2C Hub|HUB| | |:material-check:|:material-check:| | | |
|15|Grove - Gesture Sensor for Arduino (PAJ7620U2)|INPUT|touch, proximity| |:material-check:| | | | |
|16|Grove - Analog Microphone (MEMS)|INPUT|sound| | |:material-check:| | | |
|17|Seeedstudio Wio Terminal |MIC| | | | |:material-check:|:material-check:|:material-check:|
|18|Grove - Thermal Imaging Camera IR-Array MLX90641|INPUT|vision, environmental| | | |:material-check:| |:material-check:|
|19|24GHz mmWave Sensor - Fall Detection Module|INPUT|vision, physical| | | |:material-check:| | |
|20|MR24BSD1 24GHz mmWave Sensor - Respiratory Sleep Detection Module|INPUT|vision, physical| | | |:material-check:| | |
|21|Grove - GSR Sensor|INPUT|physical| | | |:material-check:| | |
|22|Grove - EMG Detector|INPUT|physical| | | |:material-check:| | |
|23|60GHz mmWave Sensor - Human Resting Breathing and Heartbeat Module|INPUT|physical| | | |:material-check:| | |
|24|Grove - Multichannel Gas Sensor v2|INPUT|smell| | | |:material-check:|:material-check:| |
|25|Philips Hue|OUTPUT| | | | | | |:material-check:|
|26|Philips hub|HUB| | | | | | |:material-check:|
|27|Raspberry pi 4|SERVER| | | | | | |:material-check:|
|28|Grove Raspberry Pi HAT|CONN| | | | | | |:material-check:|
|29|Grove - Vision AI Module|INPUT|sight| | | | | |:material-check:|
|30|Shelly EM / Sonoff POW|INPUT|environmental| | | | | | |
