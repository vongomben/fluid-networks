/*

  Example taken from Seeestudio Wiki

  adapted to work with Arduino Grove Carrier (on MKR1010)

  https://www.arduino.cc/en/Guide/MKRConnectorCarrier
  by Davide Gomba

*/




#include "Ultrasonic.h"
#include "Keyboard.h"
Ultrasonic ultrasonic(0);
void setup()
{
  Serial.begin(9600);
  Keyboard.begin();
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

  if (RangeInCentimeters < 10) {
    Serial.println("help");
     Keyboard.print("hello");hello
    delay(25);
  }


  //  Serial.println(" cm");
  delay(25);
}
