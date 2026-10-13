#include <Arduino.h>

// Define the global variable
int LEDPIN = 13;
int BUTTONPIN = 2;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT_PULLUP);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  Serial.println("Wait for the LED, Then press the button");
}

void loop() {
  digitalWrite(LEDPIN, LOW);
  delay(random(2000, 5000));
  if (digitalRead(BUTTONPIN) == LOW) {
    Serial.println("Too Soon! Let go of the button.");
    while (digitalRead(BUTTONPIN) == LOW) {
      return;
    }
  }
  digitalWrite(LEDPIN,HIGH);
  unsigned long start = millis();
  while (digitalRead(2) == HIGH) {}
  unsigned long t = millis() - start;
  digitalWrite(LEDPIN, LOW);
  Serial.print("Your time is: ");
  Serial.print(t);
  Serial.print(" ms");
  while (digitalRead(BUTTONPIN) == LOW) { }
  delay(1000);

}