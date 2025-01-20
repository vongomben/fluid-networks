#include "TFT_eSPI.h"
#include <Ultrasonic.h>

TFT_eSPI tft;
Ultrasonic ult(BCM27);

void setup(){
  Serial.begin(9600);
  tft.begin();
  pinMode(WIO_LIGHT, INPUT);
  tft.setRotation(3);
  tft.setTextSize(3);

}



void loop(){

  float distanza = (long)ult.MeasureInCentimeters();

  tft.fillScreen(0xFFFF);
  tft.setTextColor(0x0);
  tft.drawString((String)"luce ", 0, 80);
  tft.drawString((String)analogRead(WIO_LIGHT), 160, 80);
  tft.drawString((String)"distanza", 0, 120);
  Serial.println(distanza);
  tft.drawString((String)distanza, 160, 120);

}