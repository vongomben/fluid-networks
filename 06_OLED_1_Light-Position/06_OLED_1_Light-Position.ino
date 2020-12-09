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

const int analogInPin = A0; // GPIO on which the light sensor is attached to

int sensorValue = 0;        // value read from the light sensor
int newSensorValue = 0;     // value to update the value of the sensor

void setup(void) {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R2);          // rotations --> https://github.com/olikraus/u8g2/wiki/u8g2reference#setdisplayrotation
  u8g2.setFont(u8g2_font_fub11_tf);         // here --> https://github.com/olikraus/u8g2/wiki/fntlistall



}

void loop(void) {
  sensorValue = analogRead(analogInPin);

  int x_position = map(sensorValue, 10, 800, 0, 128);

  Serial.println(x_position);

  u8g2.drawStr(x_position, 40, "Fluid Networks");   // here --> https://github.com/olikraus/u8g2/wiki/u8g2reference#drawstr
  u8g2.sendBuffer();                         // transfer internal memory to the display

  if (sensorValue != newSensorValue) {

    newSensorValue = sensorValue;
    Serial.println("updated");
    u8g2.clearBuffer(); // clean the display
  }



}
