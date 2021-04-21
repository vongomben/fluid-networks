/*

  Simple variable writing on screen based on U8g2 Library Print function
  --> https://github.com/olikraus/u8g2/wiki/u8g2reference#print

  The Variable is displayed if the distance is lower than X

  We are using
  - Seeedstudio Grove Oled Screen on TWI / I2C
  - Ultrasonic Distance Sensor on D0
  - Arduino Grove Carrier

  Fluid Networks / Davide Gomba 04/2021


*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "Ultrasonic.h"
Ultrasonic ultrasonic(0);

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,
    /* clock=*/ SCL,
    /* data=*/ SDA,
    /* reset=*/ U8X8_PIN_NONE);

void setup() {

  u8g2.begin();

  u8g2.setFont(u8g2_font_fub11_tf);	// set the target font to calculate the pixel width
}


void loop() {

  long RangeInInches;
  long RangeInCentimeters;

  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.println(RangeInCentimeters);//0~400cm

  if (RangeInCentimeters < 30) {

    u8g2.setCursor(0, 15);
    u8g2.print(RangeInCentimeters);
    u8g2.setCursor(40, 15);
    u8g2.print("cm");
    u8g2.sendBuffer();
    u8g2.clearBuffer(); // this clear the screen for the next frame to be drawn

  } else if (RangeInCentimeters >=30) {

    u8g2.setCursor(0, 15);
    u8g2.print("    ");
    u8g2.setCursor(40, 15);
    u8g2.print("    ");
    u8g2.sendBuffer();
    u8g2.clearBuffer(); // this clear the screen for the next frame to be drawn


  }



}
