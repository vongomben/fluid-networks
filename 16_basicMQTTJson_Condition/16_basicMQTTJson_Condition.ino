/* This example shows how to use MQTT on the main dev boards on the market
  HOW TO USE:
  under connect method, add your subscribe channels.
  under messageReceived (callback method) add actions to be done when a msg is received.
  to publish, call client.publish(topic,msg)
  in loop take care of using non-blocking method or it will corrupt.
  Alberto Perro & DG - Officine Innesto 2019

  Updated to be the minimal parsing example to to control
  the Arduino behaviour throughout a json string sent to topic #hello

  The payload can be either

  {
    "name": "LED",
    "status": "open",
    "pin": 1,
    "color": "red"
  }

  or

  {
    "name": "LED",
    "status": "closed",
    "pin": 0,
    "color": "red"
  }


*/
#define BROKER_IP    "192.168.1.0"
#define DEV_NAME     "mqttdevice"
#define MQTT_USER    "user"
#define MQTT_PW      "password"
const char ssid[] = "wifi_ssid";
const char pass[] = "wifi_password";
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
  JSONVar myObject = JSON.parse(payload);
  //Serial.println(JSON.typeof(myObject));

  if (myObject.hasOwnProperty("name")) {
    Serial.print("myObject[\"name\"] = ");

    Serial.println((const char*) myObject["name"]);
  }

  if (myObject.hasOwnProperty("status")) {
    Serial.print("myObject[\"status\"] = ");

    Serial.println((const char*) myObject["status"]);
    //   Serial.println(myObject["status"]);

  }

  if (myObject.hasOwnProperty("pin")) {
    Serial.print("myObject[\"pin\"] = ");

    Serial.println((int) myObject["pin"]);
  }

  if (myObject.hasOwnProperty("color")) {
    Serial.print("myObject[\"color\"] = ");

    Serial.println((const char*) myObject["color"]);
  }

  if (topic == "/hello") {
    if (String((const char*)myObject["status"]) == "open") {
      
      Serial.println("open");
      digitalWrite(LED_BUILTIN, HIGH);
      
    } else if (String((const char*)myObject["status"]) == "closed") {

      Serial.println("closed");
      digitalWrite(LED_BUILTIN, LOW);
 
    }


    if ((int) myObject["pin"] == 1) {

      Serial.println("open");
      digitalWrite(LED_BUILTIN, HIGH);

    } else if ((int) myObject["pin"] == 0) {
 
      Serial.println("closed");
      digitalWrite(LED_BUILTIN, LOW);

    }

  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  pinMode(LED_BUILTIN, OUTPUT);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  //
  // MQTT brokers usually use port 8883 for secure connections.
  client.begin(BROKER_IP, 1883, net);
  client.onMessage(messageReceived);
  connect();
}
void loop() {
  client.loop();
  if (!client.connected()) {
    connect();
  }
  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    //  client.publish("/hello", "world"); //PUBLISH TO TOPIC /hello MSG world
  }
}
