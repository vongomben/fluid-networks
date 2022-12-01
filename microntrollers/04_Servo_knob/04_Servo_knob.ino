/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob

  fluid networks changed in order to work with a servo on pin 4
  added some serial port explanatory print of the double use of the variable val

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
  /* val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
    Serial.print(" analog input is = ");
    Serial.print(val);
    val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    Serial.print(" while the val remapped is = ");
    // myservo.write(val);                  // sets the servo position according to the scaled value
    Serial.println(val);
    delay(15);                           // waits for the servo to get there

  */

  for (int i = 0; i < 180; i = i + 1) {
    myservo.write(i);
    delay(25);
  }
  for (int i = 180; i > 0; i = i - 1) {
    myservo.write(i);
    delay(10);
  }



}
