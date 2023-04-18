/*************************************************************

  You’ll need:
   - Blynk IoT app (download from App Store or Google Play)
   - Wio Terminal board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME         "Device"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <rpcWiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleWioTerminal.h>

BlynkTimer timer;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID";
char pass[] = "PASSWORD";


void sendSensor() {
  float l = analogRead(WIO_LIGHT);

  Blynk.virtualWrite(V0, l);
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V1) {
  int pinValue = param.asInt();  // assigning incoming value from pin V1 to a variable

  // process received value

  Serial.println(pinValue);

  if (pinValue == 0) {

    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)

    Serial.println("Led ON");

//  } else if (pinValue == 1) {
    
  } else {

    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW

    Serial.println("Led OFF");



  }
}




void setup() {
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);


  pinMode(WIO_LIGHT, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);


  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!

  timer.run();
}
