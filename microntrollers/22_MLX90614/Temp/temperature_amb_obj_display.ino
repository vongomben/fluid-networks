#include"TFT_eSPI.h"
#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> //Click here to get the library: http://librarymanager/All#Qwiic_IR_Thermometer by SparkFun

TFT_eSPI tft;
IRTherm therm; // Create an IRTherm object to interact with throughout

void setup(){
  tft.begin();
  tft.setTextSize(2);
  tft.setRotation(3);
  tft.fillScreen(0x0);

  Serial.begin(115200); // Initialize Serial to log output
  Wire.begin(); //Joing I2C bus
  
  if (therm.begin() == false){ // Initialize thermal IR sensor
    Serial.println("Qwiic IR thermometer did not acknowledge! Freezing!");
    while(1);
  }
  Serial.println("Qwiic IR Thermometer did acknowledge.");
  
  therm.setUnit(TEMP_C); // Set the library's units to Farenheit
  // Alternatively, TEMP_F can be replaced with TEMP_C for Celsius or
  // TEMP_K for Kelvin.
  
  pinMode(LED_BUILTIN, OUTPUT); // LED pin as output
}

void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);
    
  // Call therm.read() to read object and ambient temperatures from the sensor.
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    // Use the object() and ambient() functions to grab the object and ambient
  // temperatures.
  // They'll be floats, calculated out to the unit you set with setUnit().
    tft.drawString((String)("Object: " + String(therm.object(), 2)),0,0);
    tft.drawString((String)"C",180,0);
    tft.drawString((String)("Ambient: " + String(therm.ambient(), 2)),0,50);
    tft.drawString((String)"C",180,50);
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
