/* This example shows how to use MQTT on the main dev boards on the market
  HOW TO USE:
  under connect method, add your subscribe channels.
  under messageReceived (callback method) add actions to be done when a msg is received.
  to publish, call client.publish(topic,msg)
  in loop take care of using non-blocking method or it will corrupt.
  Alberto Perro & DG - Officine Innesto 2019
*/

#define BROKER_IP    "broker.hivemq.com"
// #define BROKER_IP    "192.168.1.9"
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
  client.subscribe("/hello01"); //SUBSCRIBE TO TOPIC /hello
}
void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if (topic == "/hello01") {
    if (payload == "open") {
      Serial.println("open");
      digitalWrite(LED_BUILTIN, HIGH);
      client.publish("/alert01", "Led ON"); //PUBLISH TO TOPIC /hello MSG world
    } else if (payload == "closed") {
      Serial.println("closed");
      digitalWrite(LED_BUILTIN, LOW);
      client.publish("/alert01", "Led OFF"); //PUBLISH TO TOPIC /hello MSG world

    }
  }
}
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
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
    client.publish("/hello01", "world"); //PUBLISH TO TOPIC /hello MSG world
  }
}
