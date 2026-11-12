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

// Pin for the speaker
int const SPEAKER = 7;

// Variables for distance and duration
long duration;
float distance;

// Function that reads the distance from the ultrasonic sensor (changed to float)
float readDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000); // 30ms timeout prevents freezing
  float dist = duration * 0.0344 / 2.0;
  
  // Handle out-of-range sensor readings
  if (dist == 0) {
    dist = 999; 
  }

  Serial.print("Distance: ");
  Serial.println(dist);

  return dist;
}

// Find the current state of the robot
void findState(float dist) {
  if (dist > 100) {
    currentState = State::NotVisible;
  } else if (dist > 50) {
    currentState = State::Far;
  } else if (dist > 25) {
    currentState = State::Close;
  } else {
    currentState = State::Stop;
  }
}

// Pulse LED and Speaker simultaneously
void alertPulse(int pulsesPerSecond, int ledPin, int toneFrequency, int speakerPin) {
  int modifiedDelay = round(500.0 / pulsesPerSecond);

  for (int i = 0; i < pulsesPerSecond; i++) {
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, toneFrequency);
    delay(modifiedDelay);

    digitalWrite(ledPin, LOW);
    noTone(speakerPin);
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

  // Configure the speaker pin
  pinMode(SPEAKER, OUTPUT);

  // Configure serial
  Serial.begin(9600);
}

void loop() {
  distance = readDistance();
  findState(distance);

  switch(currentState) {
    case State::NotVisible: {
      digitalWrite(GREENLEDPIN, LOW);
      digitalWrite(YELLOWLEDPIN, LOW); // Fixed typo (was GREENLEDPIN)
      digitalWrite(REDLEDPIN, LOW);
      noTone(SPEAKER);
      delay(50); // Short delay to prevent ultrasonic echo interference
      break;
    }
    case State::Far: {
      digitalWrite(YELLOWLEDPIN, LOW);
      digitalWrite(REDLEDPIN, LOW);
      alertPulse(1, GREENLEDPIN, 500, SPEAKER);
      break;
    }      
    case State::Close: {
      digitalWrite(GREENLEDPIN, LOW);
      digitalWrite(REDLEDPIN, LOW);
      alertPulse(3, YELLOWLEDPIN, 800, SPEAKER);
      break;
    }
    case State::Stop: {
      digitalWrite(GREENLEDPIN, LOW);
      digitalWrite(YELLOWLEDPIN, LOW);
      digitalWrite(REDLEDPIN, HIGH);
      tone(SPEAKER, 1500);
      delay(50); // Short delay to prevent ultrasonic echo interference
      break;
    }
  }
}
