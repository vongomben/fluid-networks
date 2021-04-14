// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "Ultrasonic.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);
int led = 5;
int val;
const int sensore = A0;
Ultrasonic ultrasonic(0);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print (F("Driver Ver: ")); Serial.println(sensor.version);
  Serial.print (F("Unique ID: ")); Serial.println(sensor.sensor_id);
  Serial.print (F("Max Value: ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print (F("Min Value: ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print (F("Resolution: ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print (F("Driver Ver: ")); Serial.println(sensor.version);
  Serial.print (F("Unique ID: ")); Serial.println(sensor.sensor_id);
  Serial.print (F("Max Value: ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print (F("Min Value: ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print (F("Resolution: ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  int luce = analogRead(sensore);
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print("Brightness: " );
    Serial.print(luce) ;
    Serial.print(" B.I. ");
    Serial.print(" Distance: ");//0400cm
    Serial.print(RangeInCentimeters);//0400cm
    Serial.print(" centimetres ");
    Serial.print(" Temperature: ");
    Serial.print(event.temperature);
    Serial.print("°C ");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F(" Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
