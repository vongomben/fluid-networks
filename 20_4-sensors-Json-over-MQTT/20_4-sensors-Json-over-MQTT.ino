// This codes assumes you have:
// - Light sensor on A0
// - Grove Ultrasonic Ranger on D0
// - DHT11 on D2
// - Grove NFC on Serial Port
//
//
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
// - Grove Ultrasonic Ranger Library: https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger
// - NFC Lirabries for Grove NFC: https://github.com/Seeed-Studio/Seeed_Arduino_NFC

#define BROKER_IP    "broker.hivemq.com"
#define DEV_NAME     "mqttdevice"
#define MQTT_USER    "mqtt_user"
#define MQTT_PW      "mqtt_password"

#include "arduino_secrets.h" 


const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;

#include <MQTT.h>
#ifdef ARDUINO_SAMD_MKRWIFI1010
#include <WiFiNINA.h>
#elif ARDUINO_SAMD_MKR1000
#include <WiFi101.h>
#elif ESP8266
#include <ESP8266WiFi.h>
#else
#error unknown board
#endif
WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;



#include <Arduino_JSON.h>


#if 0
#include <SPI.h>
#include <PN532_SPI.h>
#include "PN532.h"

PN532_SPI pn532spi(SPI, 10);
PN532 nfc(pn532spi);
#elif 1
#include <PN532_HSU.h>
#include <PN532.h>

PN532_HSU pn532hsu(Serial1);
PN532 nfc(pn532hsu);
#else
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);
#endif

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "Ultrasonic.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

String code = "unkwonwn";
int val;
const int sensore = A0;
Ultrasonic ultrasonic(0);

uint32_t delayMS;

float temp;
float hum;

void connect() {
 Serial.print("checking wifi...");
 while (WiFi.status() != WL_CONNECTED) {
   Serial.print(".");
   delay(1000);
 }
 Serial.print("\nconnecting...");
 while (!client.connect(DEV_NAME, MQTT_USER, MQTT_PW)) {
   Serial.print(".");
   delay(1000);
 }
 Serial.println("\nconnected!");
 client.subscribe("/hello"); //SUBSCRIBE TO TOPIC /hello
}
void messageReceived(String &topic, String &payload) {
 Serial.println("incoming: " + topic + " - " + payload);
 if (topic == "/hello") {
   if (payload == "open") {
     Serial.println("open");
     digitalWrite(LED_BUILTIN, HIGH); 
   } else if (payload == "closed") {
     Serial.println("closed");
     digitalWrite(LED_BUILTIN, LOW); 
   }
 }
}


void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, pass);
 // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
 // You need to set the IP address directly.
 //
 // MQTT brokers usually use port 8883 for secure connections.
 client.begin(BROKER_IP, 1883, net);
 client.onMessage(messageReceived);
 connect();

  
  // Initialize device.
  dht.begin();



  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

 

}

void loop() {

  client.loop();
 if (!client.connected()) {
   connect();
 }

  
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {

    temp = event.temperature;

  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {

    hum = event.relative_humidity;

  }
 

  // read distance

  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters();

  // read light
  int light = analogRead(sensore);

  // read temperature
  delay(delayMS);
  //  sensors_event_t event;
  //  dht.temperature().getEvent(&event);

  // Read humidity
  //  dht.humidity().getEvent(&event);

  // put everything ina Json Object

  JSONVar myObject;

  myObject["Brightness"] = light;
  myObject["Distance"] = RangeInCentimeters;
  myObject["Temperature"] = temp;
  myObject["Humidity"] = hum;

// JSON.stringify(myVar) can be used to convert the json var to a String
  String jsonString = JSON.stringify(myObject);

    Serial.println(myObject);
    client.publish("/hello", jsonString);
    delay(5000);
// publish a message roughly every second.
// if (millis() - lastMillis > 1000) {
//   lastMillis = millis();
//  client.publish("/hello", myObject); //PUBLISH TO TOPIC /hello MSG world
// }
  


}
