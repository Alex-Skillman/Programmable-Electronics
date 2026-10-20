#include <Arduino.h>

void setup() {
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(10, HIGH);
  delay(1);
  digitalWrite(10, LOW);
  delay(1);
}
