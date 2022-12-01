/*

  Example taken / adapted from Seeestudio Wiki
  for the Grove Ultrasonic Ranger
  https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/
  adapted to work with Arduino Grove Carrier (on MKR1010)

  https://www.arduino.cc/en/Guide/MKRConnectorCarrier
  
  by Davide Gomba for the Fluid Networks Workshop

  Library here
  https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger/archive/master.zip

  Install Library Sketch>include Library> Add Zip Library

  Add Ultrasonic Ragnfinder to pin D0 of MKR Carrier
  Add LED / Pushbutton to pin D5-D6 of MKR Carrier

  
*/

#include "Ultrasonic.h"

int led = 5;

Ultrasonic ultrasonic(0);

int val;    // variable to host the value

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);

}
void loop()
{
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.print(RangeInCentimeters);//0~400cm

  // Distance (measures under 1 meter)
  // Is represented through Light
  // Above one meter, do nothing!

  val = map(RangeInCentimeters, 0, 60, 255, 0);  // mapping values

  Serial.print(" - ");
  Serial.println(val);// Priting the Value

  if (RangeInCentimeters > 60) { // if the distance is above 60 cm...

    analogWrite(led, 0); // keep the LED switched off

  } else { // otherwise
    
    analogWrite(led, val); //light up the LED on its val value
  
  }
  
  delay(25);
}
