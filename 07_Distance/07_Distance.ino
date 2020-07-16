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
void setup()
{
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}
void loop()
{
    long RangeInInches;
    long RangeInCentimeters;
 
   /* Serial.println("The distance to obstacles in front is: ");
    RangeInInches = ultrasonic.MeasureInInches();
    Serial.print(RangeInInches);//0~157 inches
    Serial.println(" inch");
    delay(250);
 */
    RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
    Serial.print(RangeInCentimeters);//0~400cm
    //Serial.println(" cm");
    int value = map(RangeInCentimeters, 10, 210, 255, 0);
    Serial.print(" - ");
    Serial.println(value);
    analogWrite(led, value);
    
    delay(25);
}
