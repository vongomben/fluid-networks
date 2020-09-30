/*

  Example taken from Seeestudio Wiki
  for the Grove Ultrasonic Ranger
  https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/
  adapted to work with Arduino Grove Carrier (on MKR1010)

  https://www.arduino.cc/en/Guide/MKRConnectorCarrier
  by Davide Gomba

  Library here
  https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger/archive/master.zip

  Install Library Sketch>include Library> Add Zip Library
*/



//#include <Servo.h>
#include "Ultrasonic.h"

int led = 5;

//Servo myservo;  // create servo object to control a servo
Ultrasonic ultrasonic(0);

int val;    // variable to read the value from the analog pin

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
//  myservo.attach(4);  // attaches the servo on pin 4 to the servo object

}
void loop()
{
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.println(RangeInCentimeters);//0~400cm
  val = map(RangeInCentimeters, 0, 250, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
 // myservo.write(val);
  delay(25);
}
