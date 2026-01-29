#include <Arduino_JSON.h>
#include "LIS3DHTR.h"

JSONVar Object;
LIS3DHTR<TwoWire> lis;

void setup() {
  Serial.begin(9600);
  pinMode(WIO_LIGHT, INPUT);
  lis.begin(Wire1);
  lis.setOutputDataRate(LIS3DHTR_DATARATE_100HZ);
  lis.setFullScaleRange(LIS3DHTR_RANGE_4G);

  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
  pinMode(WIO_MIC, INPUT);
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
}



void loop() {

  Object["light"] = (String)analogRead(WIO_LIGHT);
  Object["X"] = (String)lis.getAccelerationX();
  Object["Y"] = (String)lis.getAccelerationY();
  Object["Z"] = (String)lis.getAccelerationZ();
  
  
    if (digitalRead(WIO_KEY_A) == LOW) {
    Object["A"] = (String)"1";
  } else {
    Object["A"] = (String)"0";
  }
    
    if (digitalRead(WIO_KEY_B) == LOW) {
    Object["B"] = (String)"1";
  } else {
    Object["B"] = (String)"0";
  }
    
    if (digitalRead(WIO_KEY_C) == LOW) {
    Object["C"] = (String)"1";
  } else {
    Object["C"] = (String)"0";
  }
  
  Object["audio"] = (String)analogRead(WIO_MIC);
  
  if (digitalRead(WIO_5S_UP) == LOW) {
    Object["UP"] = (String)"1";
  } else {
    Object["UP"] = (String)"0";
  }
  
    if (digitalRead(WIO_5S_DOWN) == LOW) {
    Object["DOWN"] = (String)"1";
  } else {
    Object["DOWN"] = (String)"0";
  }
  
    
    if (digitalRead(WIO_5S_LEFT) == LOW) {
    Object["LEFT"] = (String)"1";
  } else {
    Object["LEFT"] = (String)"0";
  }
    
      
    if (digitalRead(WIO_5S_RIGHT) == LOW) {
    Object["RIGHT"] = (String)"1";
  } else {
    Object["RIGHT"] = (String)"0";
  }
    
        
    if (digitalRead(WIO_5S_PRESS) == LOW) {
    Object["PRESSED"] = (String)"1";
  } else {
    Object["PRESSED"] = (String)"0";
  }
        
  
  
  
  
  Serial.println(JSON.stringify(Object));
  delay(20);
}