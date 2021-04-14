# Fluid Networks
Teaching Physical Computing Remotely / A Syllabus and Educational Proposal
This is the official repository and documentation for the **Fluid Networks Workshop**

## What is the Fluid Networks Workshop?

Fluid Networks is a list of lessons and good practices, divided in 4 educational units, where students will learn the basic usage of the latest Arduino MKR boards, together with a selection of sensors and actuators that will eventually help them create interactive projects that will be connected to the internet in various different ways.

We’ll learn how to connect things together, design conversations or add emotional behaviours to products and experiences.

## Educational Tools

The course will use a a [Flipped Classroom](https://en.wikipedia.org/wiki/Flipped_classroom).
The goal is giving all students the same, personal, one to one educational experience, while discussing with them (in groups or classroom-wide) the problems they may have found in their Units Deliverables. Almost each Learning Unit has a deliverables.

We also defined some special Learning Units which are called **Projects**. The Student will see how a little project is done, and will be asked to customize or reproduce a similar behaviour - editing and customizing codes Uis to fulfill her/his personal accomplishment.

The Fluid Networks Workshop has been developed and tested during the first Pandemic in 2020, and addressed to several [Istituto Marangoni](https://www.istitutomarangoni.com/en) students, while is being reshaped for Mozilla / Northumrbia University Open Hardware Workshop for the [OpenDoTT PhD Programme](https://opendott.org/) ad well as being used for the first and second year of [Cloud Computing as Internet of Things Development Kit at the ITS ICT of Turin](https://www.its-ictpiemonte.it/corsi/cloud-specialist/)    

# Kit (with wiki links)

We’ve scouted all the best tools around, with several goals in mind: good yet inexpensive materials, easily reusable nodes. We’ve also chosen to exclude the breadboard - the most important design tool in Physical Computing and Electronics - from this proposal. Very difficult to debug a short circuit from the Internet.

We’ve selected what we think is the most easy to use platform nowadays, [Arduino MKR 1010](https://store.arduino.cc/arduino-mkr-wifi-1010) (which is part of the broader [MKR family](https://www.arduino.cc/pro/hardware/product-family/mkr-family?id=1996559)), allowing brave students to shift connectivity and uses for their final project) with the widest index of electronics nodes produced by well known Shenzhen based company, **Seeedstudio**: the [Grove Prototyping System](http://wiki.seeedstudio.com/Grove_System/)


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
|  10 |                       [Grove - NFC](https://wiki.seeedstudio.com/Grove_NFC/)                       |      INPUT     |   | v.2
|  11 |                      [Grove - Servo](https://wiki.seeedstudio.com/Grove-Servo/)                      |     OUTPUT     |   | v.2
|  12 |               [Grove - 2-Channel SPDT Relay](https://wiki.seeedstudio.com/Grove-2-Channel_SPDT_Relay/)              |     OUTPUT     |   | v.2
|  13 | Grove - Universal 4 Pin Buckled 50cm Cable (5 PCs Pack) |       HUB      |   | v.2
|  14 |                     [Grove - I2C Hub](https://wiki.seeedstudio.com/Grove-I2C_Hub/)                     |       HUB      |   | v.2
|  15 |      [Grove - Gesture Sensor for Arduino (PAJ7620U2)](https://wiki.seeedstudio.com/Grove-Gesture_v1.0/)     |      INPUT     |   | dismissed
|  16 |[Grove - IMU 9DOF v2.0 - MPU-9250](https://wiki.seeedstudio.com/Grove-IMU_9DOF_v2.0/)| INPUT |   | v.2
|  17 |[Grove - Analog Microphone (MEMS)](https://wiki.seeedstudio.com/Grove-Analog-Microphone/) |INPUT |  | v.2
