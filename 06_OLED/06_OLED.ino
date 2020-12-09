#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,
    /* clock=*/ SCL,
    /* data=*/ SDA,
    /* reset=*/ U8X8_PIN_NONE);


void setup(void) {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R2);          // rotations --> https://github.com/olikraus/u8g2/wiki/u8g2reference#setdisplayrotation
  u8g2.setFont(u8g2_font_fub11_tf);         // here --> https://github.com/olikraus/u8g2/wiki/fntlistall

  u8g2.drawStr(10, 40, "Fluid Networks");   // here --> https://github.com/olikraus/u8g2/wiki/u8g2reference#drawstr
  u8g2.sendBuffer();                         // transfer internal memory to the display

}

void loop(void) {

}
