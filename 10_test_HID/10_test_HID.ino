#include <Keyboard.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Keyboard.begin();
}

void loop() {
  delay(5000);
  Keyboard.print("hello");

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

}
