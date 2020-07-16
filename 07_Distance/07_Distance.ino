/*

  Example taken from Seeestudio Wiki

  adapted to work with Arduino Grove Carrier (on MKR1010)
  
  https://www.arduino.cc/en/Guide/MKRConnectorCarrier
  by Davide Gomba

*/




#include "Ultrasonic.h"
 
Ultrasonic ultrasonic(0);
void setup()
{
    Serial.begin(9600);
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
    Serial.println(RangeInCentimeters);//0~400cm
  //  Serial.println(" cm");
    delay(25);
}
