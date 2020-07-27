/*
  fluid networks changed in order to work with a servo on pin 4

  basic for loop inside of a servo
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the light dependant resistor
int val;    // variable to read the value from the analog pin

void setup() {
  Serial.begin(9600);
  myservo.attach(4);  // attaches the servo on pin 4 to the servo object
}

void loop() {

  for (int i = 0; i < 180; i = i + 1) {
    myservo.write(i);
    Serial.begin(i);
    delay(25); // decrease this number in order to have a more fluid movement
  }
  for (int i = 180; i > 0; i = i - 1) {
    myservo.write(i);
    Serial.begin(i);
    delay(25); // decrease this number in order to have a more fluid movement
  }



}
