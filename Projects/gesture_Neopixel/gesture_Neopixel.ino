#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 3

int topLeds[] =     {12, 13, 14, 15,  0,  1,  2, 3, 4};
int bottomLeds[] =  {12, 11, 10,  9,  8,  7,  6, 5, 4};
int leftLeds[] =    {0,  15, 14, 13, 12, 11, 10, 9, 8};
int rightLeds[] =   {0,   1,  2,  3,  4,  5,  6, 7, 8};

// gesture sensor stuff


#include <Wire.h>
#include "paj7620.h"



Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);


/*
  Notice: When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s).
        You also can adjust the reaction time according to the actual circumstance.
*/
#define GES_REACTION_TIME       500             // You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME          800             // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME           1000

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) {
    clock_prescale_set(clock_div_1);
  }
#endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'

  uint8_t error = 0;

  Serial.begin(9600);
  Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");

  error = paj7620Init();          // initialize Paj7620 registers
  if (error)
  {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else
  {
    Serial.println("INIT OK");
  }
  Serial.println("Please input your gestures:\n");


}

void loop() {

  uint8_t data = 0, data1 = 0, error;

  error = paj7620ReadReg(0x43, 1, &data);             // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error)
  {
    switch (data)                                   // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG)
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG)
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Right");
          directions(strip.Color(255, 0, 0), 50, "right");
        }
        break;
      case GES_LEFT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG)
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG)
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Left");
          directions(strip.Color(255, 0, 0), 50, "left");
        }
        break;
      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG)
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG)
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Up");
          directions(strip.Color(255, 0, 0), 50, "up");
        }
        break;
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG)
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if (data == GES_BACKWARD_FLAG)
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Down");
          directions(strip.Color(255, 0, 0), 50, "down");
        }
        break;
      case GES_FORWARD_FLAG:
        Serial.println("Forward");
        delay(GES_QUIT_TIME);
        break;
      case GES_BACKWARD_FLAG:
        Serial.println("Backward");
        delay(GES_QUIT_TIME);
        break;
      case GES_CLOCKWISE_FLAG:
        Serial.println("Clockwise");
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        Serial.println("anti-clockwise");
        break;
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG)
        {
          Serial.println("wave");
        }
        break;
    }
  }
  delay(100);



  /* // Some example procedures showing how to display to the pixels:
    colorWipe(strip.Color(255, 0, 0), 50); // Red
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
    //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
    // Send a theater pixel chase in...
    theaterChase(strip.Color(127, 127, 127), 50); // White
    theaterChase(strip.Color(127, 0, 0), 50); // Red
    theaterChase(strip.Color(0, 0, 127), 50); // Blue

    rainbow(20);
    rainbowCycle(20);
    theaterChaseRainbow(50);

  */

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void directions(uint32_t c, uint8_t wait, String d) {

  if (d == "up") {
    for (uint16_t i = 0; i < 8; i++) {
      strip.setPixelColor(topLeds[i], c);
      strip.setPixelColor(bottomLeds[i], c);
      strip.show();
      delay(wait);
    }

    for (uint16_t i = 0; i < 8; i++) {
      strip.setPixelColor(topLeds[i], 0, 0, 0);
      strip.setPixelColor(bottomLeds[i], 0, 0, 0);
      strip.show();
      delay(wait / 2);
    }
  }

  if (d == "down") {
    for (uint16_t i = 8; i > 0; i--) {
      strip.setPixelColor(topLeds[i], c);
      strip.setPixelColor(bottomLeds[i], c);
      strip.show();
      delay(wait);
    }

    for (uint16_t i = 8; i > 0; i--) {
      strip.setPixelColor(topLeds[i], 0, 0, 0);
      strip.setPixelColor(bottomLeds[i], 0, 0, 0);
      strip.show();
      delay(wait / 2);
    }
  }

  if (d == "left") {
    for (uint16_t i = 0; i < 8; i++) {
      strip.setPixelColor(leftLeds[i], c);
      strip.setPixelColor(rightLeds[i], c);
      strip.show();
      delay(wait);
    }

    for (uint16_t i = 0; i < 8; i++) {
      strip.setPixelColor(leftLeds[i], 0, 0, 0);
      strip.setPixelColor(rightLeds[i], 0, 0, 0);
      strip.show();
      delay(wait / 2);
    }
  }

  if (d == "right") {
    for (uint16_t i = 8; i > 0; i--) {
      strip.setPixelColor(leftLeds[i], c);
      strip.setPixelColor(rightLeds[i], c);
      strip.show();
      delay(wait);
    }

    for (uint16_t i = 8; i > 0; i--) {
      strip.setPixelColor(leftLeds[i], 0, 0, 0);
      strip.setPixelColor(rightLeds[i], 0, 0, 0);
      strip.show();
      delay(wait / 2);
    }
  }

}




void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel((i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
