#include <Arduino.h>

// Setup pin variables
int REDPIN = 11;
int YELLOWPIN = 12;
int GREENPIN = 13;
int PLAYER1INPUT = 2;
int PLAYER2INPUT = 3;

// Game variables
int score1 = 0;
int score2 = 0;

// Setup functions for pressed
bool p1Pressed() {
  return digitalRead(PLAYER1INPUT) == LOW;
}

bool p2Pressed() {
  return digitalRead(PLAYER2INPUT) == HIGH;
}

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(YELLOWPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(PLAYER1INPUT, INPUT_PULLUP);
  pinMode(PLAYER2INPUT, INPUT);
  Serial.println(9600);
  randomSeed(analogRead(A0));
}

void loop() {
  Serial.println("Hands off the buttons");
  while (p1Pressed() || p2Pressed()) { }
  delay(1500);
  digitalWrite(REDPIN, HIGH);
  delay(1000);
  digitalWrite(12, HIGH);
  delay(random(1000, 4000));
  digitalWrite(REDPIN, LOW);
  digitalWrite(YELLOWPIN, LOW);
  digitalWrite(GREENPIN, HIGH);
  unsigned long start = millis();

  int winner = 0;
  while (winner == 0) {
    if (p1Pressed()) winner = 1;
    if (p2Pressed()) winner = 2;
  }
  unsigned long t = millis() - start;
  digitalWrite(13, LOW);

  if (winner == 1) score1 += 1;
  if (winner == 2) score2 += 1;

  Serial.print("Player "); Serial.print(winner);
  Serial.print(" wins in "); Serial.print(t);
  Serial.print(" ms. Score: "); Serial.print(score1);
}