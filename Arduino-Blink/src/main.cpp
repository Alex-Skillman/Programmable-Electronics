#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

int wait = 500;
int LEDPIN = 13;
int BUTTONPIN = 2;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT_PULLUP);
}

void loop() {
  wait = 500;
  if(digitalRead(BUTTONPIN) == LOW) {
    wait = 50;
  }
  digitalWrite(LEDPIN, HIGH);
  delay(wait);
  digitalWrite(LEDPIN, LOW);
  delay(wait);
}
