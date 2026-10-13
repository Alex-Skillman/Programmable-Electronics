#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

int wait = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  wait = 500;
  if(digitalRead(2) == LOW) {
    wait = 100;
  }
  digitalWrite(12, HIGH);
  delay(wait);
  digitalWrite(12, LOW);
  delay(wait);
}
