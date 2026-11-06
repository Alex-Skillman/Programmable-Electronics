#include <Arduino.h>

// Define the states of the backup sensor
enum class State {
  NotVisible,
  Far,
  Close,
  Stop
};

// Variable that holds the state
State currentState = State::NotVisible;

// Pins for the distance sensor
int const TRIG = 5;
int const ECHO = 6;

// Pin for the servo
int const SERVOPIN = 11;

// Pins for the LEDs
int const GREENLEDPIN = 8;
int const YELLOWLEDPIN = 9;
int const REDLEDPIN = 10;

// Pins for the speaker
int const SPEAKER = 7;

// Variables for distance and duration
long duration;
float distance;

// Function that reads the distance from the ultrasonic sensor 
long readDistance() {
  // Clear the DISTANCETRIG first for a clean pulse
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor to find the time in microseconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Read the pin and find the time in microseconds the sound wave took
  duration = pulseIn(ECHO, HIGH, 30000); // 30ms timeout prevents freezing if no echo

  // Calculate the distance
  distance = duration * 0.0344 / 2;
  
  // Handle out-of-range sensor readings (pulseIn returns 0 on timeout)
  if (distance == 0) {
    distance = 999; 
  }

  Serial.print("Distance: ");
  Serial.println(distance);

  // Return the distance in cm
  return distance;
}

// Find the current state of the robot
void findState(float distance) {
  if (distance > 100) {
    currentState = State::NotVisible;
  } if (distance > 50) {
    currentState = State::Far;
  } if (distance > 25) {
    currentState = State::Close;
  } else {
    currentState = State::Stop;
  }
}

// Flash Leds a certain time per second
void flashLED(int flashPerSecond, int LEDPIN) {
  // Set the amount of delay
  float modifiedDelay = round(500/flashPerSecond);

  for (int i = 0; i < flashPerSecond; i++) {
    pinMode(LEDPIN, HIGH);
    delay(modifiedDelay);
    pinMode(LEDPIN, LOW);
    delay(modifiedDelay);
  }
}

void setup() {
  // Configure the distance sensor pins
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Configure the LED pins
  pinMode(GREENLEDPIN, OUTPUT);
  pinMode(YELLOWLEDPIN, OUTPUT);
  pinMode(REDLEDPIN, OUTPUT);
}

void loop() {
  // Read distance
  distance = readDistance();
  // Find the current state of the build
  findState(distance);

  // Handles the logic for what the tone and everything will do
  switch(currentState) {
    case::State::NotVisible:
      break;
    case::State::Far:
      
    case::State::Close:

    case::State::Stop:
  }
}
