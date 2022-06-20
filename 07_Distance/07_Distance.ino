#include <Servo.h>

#include "Ultrasonic.h"


int led = 5;
Servo myservo; 
Ultrasonic ultrasonic(0);

int val;    // variable to read the value from the analog pin
int posa = 75;
int posb = 30;
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
    myservo.attach(5);  // attaches the servo on pin 4 to the servo object

myservo.write(posb);

}
void loop()
{
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.println(RangeInCentimeters);//0~400cm


myservo.write(posb);
 if (RangeInCentimeters < 15){
//    Serial.println(RangeInCentimeters);

 for (int i = posb; i < posa; i = i + 1) {
    myservo.write(i);
    Serial.begin(i);
    delay(2); // decrease this number in order to have a more fluid movement
  }
  for (int i = posa; i > posb; i = i - 1) {
    myservo.write(i);
    Serial.begin(i);
    delay(2); // decrease this number in order to have a more fluid movement
  }
delay(3000);
    
    }
  

  delay(25);
}
