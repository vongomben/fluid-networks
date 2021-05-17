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

#include "Ultrasonic.h"


int led = 5;

Ultrasonic ultrasonic(0);

int val;    // variable to read the value from the analog pin

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);


}
void loop()
{
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.println(RangeInCentimeters);//0~400cm

//  if (RangeInCentimeters < 15){
//
//   
//    Serial.println(RangeInCentimeters);
//    
//    }
  

  delay(25);
}
