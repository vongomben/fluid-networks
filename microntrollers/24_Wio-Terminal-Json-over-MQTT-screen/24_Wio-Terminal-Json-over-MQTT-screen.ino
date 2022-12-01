// This codes assumes you have:
//
// A WIO TERMINAL
//
// REQUIRES the following Arduino libraries:
// - rcpWifi.h
// - Arduino_Json from Arduino
// - MQTT (LWMQTT) https://github.com/256dpi/arduino-mqtt
// - LIS3DHTR Library https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR
// - Follow LCD instructions from wonderful wio documentation --> https://wiki.seeedstudio.com/Wio-Terminal-LCD-Overview/
//
// node red flow
//
//[{"id":"11b29ac4408c235b","type":"mqtt in","z":"d17c141483c2dce8","name":"","topic":"/hello01","qos":"2","datatype":"auto-detect","broker":"b29d2b67cc1cf089","nl":false,"rap":true,"rh":0,"inputs":0,"x":510,"y":240,"wires":[["5bbf387071538f86"]]},{"id":"5bbf387071538f86","type":"debug","z":"d17c141483c2dce8","name":"debug 20","active":true,"tosidebar":true,"console":false,"tostatus":false,"complete":"false","statusVal":"","statusType":"auto","x":680,"y":240,"wires":[]},{"id":"ecacca4ef80fef73","type":"inject","z":"d17c141483c2dce8","name":"","props":[{"p":"payload"},{"p":"topic","vt":"str"}],"repeat":"","crontab":"","once":false,"onceDelay":0.1,"topic":"","payload":"open","payloadType":"str","x":510,"y":300,"wires":[["5d3d0f9287b7dadc"]]},{"id":"5d3d0f9287b7dadc","type":"mqtt out","z":"d17c141483c2dce8","name":"","topic":"/hello02","qos":"","retain":"","respTopic":"","contentType":"","userProps":"","correl":"","expiry":"","broker":"b29d2b67cc1cf089","x":680,"y":300,"wires":[]},{"id":"b29d2b67cc1cf089","type":"mqtt-broker","name":"","broker":"broker.hivemq.com","port":"1883","clientid":"","autoConnect":true,"usetls":false,"protocolVersion":"4","keepalive":"60","cleansession":true,"birthTopic":"","birthQos":"0","birthPayload":"","birthMsg":{},"closeTopic":"","closeQos":"0","closePayload":"","closeMsg":{},"willTopic":"","willQos":"0","willPayload":"","willMsg":{},"userProps":"","sessionExpiry":""}]

#define BROKER_IP "broker.hivemq.com"
#define DEV_NAME "mqttdevice"
#define MQTT_USER "mqtt_user"
#define MQTT_PW "mqtt_password"
#define MQTT_SUB "/hello02"
#define MQTT_PUB "/hello01"

const char ssid[] = "SSID-Name";
const char pass[] = "SSID-Password";

#include <MQTT.h>

#ifdef WIO_TERMINAL
#include "rpcWiFi.h"
#elif ARDUINO_SAMD_MKRWIFI1010
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

// Delaration of Sensors

#include "LIS3DHTR.h"

LIS3DHTR<TwoWire> lis;

// Delaration for LCD

#include "TFT_eSPI.h"

TFT_eSPI tft;

int light = WIO_LIGHT;
int mic = WIO_MIC;
int key_a = WIO_KEY_A;
int key_b = WIO_KEY_B;


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
  client.subscribe(MQTT_SUB);  //SUBSCRIBE TO TOPIC /hello
}
void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  if (topic == MQTT_SUB) {

    tft.fillScreen(0xFFFF);  // clean screen


    tft.setTextColor(0x0);
    tft.drawString((String)payload, 120, 100);
    //tft.fillScreen(0xFFFF);


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

  // TODO ADD WIO_LIGHT / DECLARE LIGHT INPUT


  client.begin(BROKER_IP, 1883, net);
  client.onMessage(messageReceived);
  connect();

  pinMode(light, INPUT);
  pinMode(mic, INPUT);
  pinMode(key_a, INPUT_PULLUP);
  pinMode(key_b, INPUT_PULLUP);
  lis.begin(Wire1);
  lis.setOutputDataRate(LIS3DHTR_DATARATE_100HZ);
  lis.setFullScaleRange(LIS3DHTR_RANGE_4G);

  tft.begin();
  tft.setRotation(3);
  tft.setTextSize(4);
  tft.setTextColor(0xFFFF);
  tft.drawString((String) "Wio MQTT", 50, 50);
  tft.fillScreen(0x0);
  delay(1000);

}

void loop() {

  client.loop();
  if (!client.connected()) {
    connect();
  }

  // create the JSON object 
  JSONVar myObject;

  // read the light, pass it to light_amount variable, assign it to "luce" key parameter
  int light_amount = analogRead(light);
  myObject["luce"] = (int)light_amount;

  int noise = analogRead(WIO_MIC);
  myObject["suono"] = (int)noise;

  int btn_a = digitalRead(WIO_KEY_A) == LOW;
  myObject["btn-a"] = (int)btn_a;

  int btn_b = digitalRead(WIO_KEY_B) == LOW;
  myObject["btn-b"] = (int)btn_b;

  int Z = lis.getAccelerationZ();
  myObject["z-acc"] = (int)Z;



  // JSON.stringify(myVar) can be used to convert the json var to a String
  String jsonString = JSON.stringify(myObject);

  // publish a message roughly every 5 seconds.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    Serial.println(myObject);

    client.publish(MQTT_PUB, jsonString);  // Publish to the topic
  }
}
