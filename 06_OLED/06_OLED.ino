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

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop(void) {

  long RangeInInches;
  long RangeInCentimeters;

  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.println(RangeInCentimeters);//0~400cm

  char cast = char(RangeInCentimeters);

  u8g2.clearBuffer();                   // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);   // choose a suitable font
  u8g2.drawStr(0, 10, "Hello World!");  // write something to the internal memory
  u8g2.setCursor(0, 40);
  u8g2.print(cast);
  //u8g2.drawStr(0, 20, cast);  // write something to the internal memory


  u8g2.sendBuffer();                    // transfer internal memory to the display
  delay(100);
  Serial.println(RangeInCentimeters);
}
