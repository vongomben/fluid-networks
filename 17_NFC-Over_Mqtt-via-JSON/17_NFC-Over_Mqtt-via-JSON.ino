/**************************************************************************/
/*!

Reading a card and sending it, as a json string, to a NOde-REd server via MQTT

[{"id":"b0ea04d4.e7e008","type":"mqtt in","z":"fd04a8e8.b4e6d8","name":"","topic":"/hello","qos":"2","datatype":"json","broker":"a9de244f.3f22e","x":330,"y":160,"wires":[["9ca6ade7.6be3a"]]},{"id":"9ca6ade7.6be3a","type":"debug","z":"fd04a8e8.b4e6d8","name":"","active":true,"tosidebar":true,"console":false,"tostatus":false,"complete":"false","x":510,"y":160,"wires":[]},{"id":"89293660.f058e8","type":"mqtt out","z":"fd04a8e8.b4e6d8","name":"","topic":"/hello","qos":"","retain":"","broker":"a9de244f.3f22e","x":490,"y":100,"wires":[]},{"id":"38ec37e4.694968","type":"inject","z":"fd04a8e8.b4e6d8","name":"","topic":"","payload":"","payloadType":"date","repeat":"","crontab":"","once":false,"onceDelay":0.1,"x":320,"y":100,"wires":[["89293660.f058e8"]]},{"id":"d47e35bc.41b128","type":"mosca in","z":"fd04a8e8.b4e6d8","mqtt_port":1883,"mqtt_ws_port":8080,"name":"novo-1","username":"mqtt_user","password":"mqtt_password","dburl":"","x":410,"y":40,"wires":[[]]},{"id":"a9de244f.3f22e","type":"mqtt-broker","z":"","name":"novo","broker":"localhost","port":"1883","clientid":"","usetls":false,"compatmode":true,"keepalive":"60","cleansession":true,"birthTopic":"","birthQos":"0","birthPayload":"","closeTopic":"","closePayload":"","willTopic":"","willQos":"0","willPayload":""}]


*/
/**************************************************************************/



#define BROKER_IP    "ipaddress"
#define DEV_NAME     "mqttdevice"
#define MQTT_USER    "mqtt_user"
#define MQTT_PW      "mqtt_password"

const char ssid[] = "SSID";
const char pass[] = "Password";


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

#include <Arduino_JSON.h>

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
  client.subscribe("/hello"); //SUBSCRIBE TO TOPIC /hello
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}



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


void setup(void) {

  Serial.begin(115200);
  Serial.println("Hello!");

  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  //
  // MQTT brokers usually use port 8883 for secure connections.
  client.begin(BROKER_IP, 1883, net);
  client.onMessage(messageReceived);
  connect();

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  // configure board to read RFID tags
  nfc.SAMConfig();

  Serial.println("Waiting for an ISO14443A Card ...");
}


void loop(void) {


  JSONVar readings;

  readings["id"] = "Accesso 1";

  //  print_number(0, 20, "ciao");

  client.loop();
  if (!client.connected()) {
    connect();
  }

  //  if (millis() - lastMillis > 1000) {
  //    lastMillis = millis();
  //    client.publish("/hello", "world"); //PUBLISH TO TOPIC /hello MSG world
  //    }

  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);

    Serial.println(uid[0], DEC);
    Serial.println(uid[0], HEX);



    Serial.println("");

    if (uidLength == 4)
    {
      // Code to String

      String code = String(uid[0]);
      code += String(uid[1]);
      code += String(uid[2]);
      code += String(uid[3]);



      Serial.print("code = ");
      Serial.print(code);
      readings["lenght"] = uidLength;
      readings["tessera"] = code;
      String jsonString = JSON.stringify(readings);
      client.publish("/hello", jsonString);
      Serial.println(" - - - - - ");

      // We probably have a Mifare Classic card ...
      Serial.println("Seems to be a Mifare Classic card (4 byte UID)");

      // Now we need to try to authenticate it for read/write access
      // Try with the factory default KeyA: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
      Serial.println("Trying to authenticate block 4 with default KEYA value");
      uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

      // Start with block 4 (the first block of sector 1) since sector 0
      // contains the manufacturer data and it's probably better just
      // to leave it alone unless you know what you're doing
      success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya);

      if (success)
      {
        Serial.println("Sector 1 (Blocks 4..7) has been authenticated");
        uint8_t data[16];

        // If you want to write something to block 4 to test with, uncomment
        // the following line and this text should be read back in a minute
        // data = { 'a', 'd', 'a', 'f', 'r', 'u', 'i', 't', '.', 'c', 'o', 'm', 0, 0, 0, 0};
        // success = nfc.mifareclassic_WriteDataBlock (4, data);

        // Try to read the contents of block 4
        success = nfc.mifareclassic_ReadDataBlock(4, data);

        if (success)
        {
          // Data seems to have been read ... spit it out
          Serial.println("Reading Block 4:");
          nfc.PrintHexChar(data, 16);
          Serial.println("");

          // Wait a bit before reading the card again
          delay(1000);
        }
        else
        {
          Serial.println("Ooops ... unable to read the requested block.  Try another key?");
        }
      }
      else
      {
        Serial.println("Ooops ... authentication failed: Try another key?");
      }
    }

    if (uidLength == 7)
    {
      // Code to String

      String code = String(uid[0]);
      code += String(uid[1]);
      code += String(uid[2]);
      code += String(uid[3]);
      code += String(uid[4]);
      code += String(uid[5]);
      code += String(uid[6]);


      Serial.print("code = ");
      Serial.print(code);
      readings["lenght"] = uidLength;
      readings["tessera"] = code;
      String jsonString = JSON.stringify(readings);
      client.publish("/hello", jsonString);
      Serial.println(" - - - - - ");


      // We probably have a Mifare Ultralight card ...
      Serial.println("Seems to be a Mifare Ultralight tag (7 byte UID)");

      // Try to read the first general-purpose user page (#4)
      Serial.println("Reading page 4");
      uint8_t data[32];
      success = nfc.mifareultralight_ReadPage (4, data);
      if (success)
      {
        // Data seems to have been read ... spit it out
        nfc.PrintHexChar(data, 4);
        Serial.println("");

        // Wait a bit before reading the card again
        delay(1000);
      }
      else
      {
        Serial.println("Ooops ... unable to read the requested page!?");
      }
    }
  }
}
