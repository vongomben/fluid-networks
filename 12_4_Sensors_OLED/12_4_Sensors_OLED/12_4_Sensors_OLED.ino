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
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT11 // DHT 11
DHT_Unified dht(DHTPIN, DHTTYPE);

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,
    /* clock=*/ SCL,
    /* data=*/ SDA,
    /* reset=*/ U8X8_PIN_NONE);

u8g2_uint_t offset; // current offset for the scrolling text
u8g2_uint_t width; // pixel width of the scrolling text (must be lesser than 128 unless U8G2_16BIT is defined
const char *text = "U8g2 "; // scroll this text from right to left

void setup(void) {
  dht.begin();

  u8g2.begin();

  u8g2.setFont(u8g2_font_inb30_mr); // set the target font to calculate the pixel width
  width = u8g2.getUTF8Width(text); // calculate the pixel width of the text

  u8g2.setFontMode(0); // enable transparent mode, which is faster
}

void loop(void) {
  u8g2_uint_t x;
  long RangeInInches;
  long RangeInCentimeters;

  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.println(RangeInCentimeters);//0~400cm
  u8g2.firstPage();
  do {

    // draw the scrolling text at current offset
    x = offset;
    u8g2.setFont(u8g2_font_inb30_mr);   // set the target font
    //    do {                // repeated drawing of the scrolling text...
    //      u8g2.drawUTF8(x, 30, text);     // draw the scolling text
    //      x += width;           // add the pixel width of the scrolling text
    //    } while( x < u8g2.getDisplayWidth() );    // draw again until the complete display is filled
    //
    u8g2.setFont(u8g2_font_inb16_mr);   // draw the current pixel width
    u8g2.setCursor(0, 20);
    //u8g2.print(width++);          // this value must be lesser than 128 unless U8G2_16BIT is set
    u8g2.print(RangeInCentimeters);          // this value must be lesser than 128 unless U8G2_16BIT is set
    u8g2.setCursor(40, 20);
    u8g2.print("cm");


    //dht11
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    u8g2.setCursor(0, 40);
    u8g2.print(event.temperature) ;
    u8g2.setCursor(80, 40);
    u8g2.print("C") ;

    dht.humidity().getEvent(&event);
    u8g2.setCursor(0, 60);
    u8g2.print(event.relative_humidity) ;
    u8g2.setCursor(80, 60);
    u8g2.print("%") ;
  } while ( u8g2.nextPage() );

  offset -= 1; // scroll by one pixel
  if ( (u8g2_uint_t)offset < (u8g2_uint_t) - width )
    offset = 0; // start over again

  delay(10); // do some small delay
}
