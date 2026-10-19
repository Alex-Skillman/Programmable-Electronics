#include <Arduino.h>

int BUZZERPIN = 10;
int REDLEDPIN = 11;
int YELLOWLEDPIN = 12;
int GREENLEDPIN = 13;

void setup() {
  pinMode(REDLEDPIN, OUTPUT);
  pinMode(YELLOWLEDPIN, OUTPUT);
  pinMode(GREENLEDPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Ready...");
  digitalWrite(REDLEDPIN, HIGH);
  tone(BUZZERPIN, 660);
  delay(350);
  noTone(BUZZERPIN);
  delay(1000);
  tone(BUZZERPIN, 660);
  delay(250);
  noTone(BUZZERPIN);
  delay(1000);
  Serial.println("Set...");
  digitalWrite(YELLOWLEDPIN, HIGH);
  digitalWrite(REDLEDPIN, LOW);
  tone(BUZZERPIN, 510);
  delay(250);
  noTone(BUZZERPIN);
  delay(1000);
  Serial.println("GO!");
  digitalWrite(YELLOWLEDPIN, LOW);
  digitalWrite(GREENLEDPIN, HIGH);
  tone(BUZZERPIN, 880);
  delay(1000);
  noTone(BUZZERPIN);
  digitalWrite(GREENLEDPIN, LOW);
  delay(2000);
}
