#include "TFT_eSPI.h"

TFT_eSPI tft;

void setup(){
  tft.begin();
  pinMode(WIO_LIGHT, INPUT);
  tft.setRotation(3);
  tft.setTextSize(4);

}

void loop(){

  tft.fillScreen(0xFFFF);
  tft.setTextColor(0x0);
  tft.drawString((String)analogRead(WIO_LIGHT), 160, 120);

}