#include <Arduino.h>
#include <Servo.h>

// Create a servo object
Servo myservo;

// Create positions for the servo
int SERVOHOME = 0;
int SERVODISPENSING = 90;

// Create variables for the pins
int SERVOPIN = 9;
int BUTTONPIN = 7;
int DISTANCETRIG = 5;
int DISTANCEEHCO = 6;

// Create variables for distance and duration
long duration;
float distance;

void setup() {
    // Configure the servo
    myservo.attach(SERVOPIN);
    myservo.write(SERVOHOME);
    
    // Configure pins
    pinMode(BUTTONPIN, INPUT_PULLUP);
    pinMode(DISTANCETRIG, OUTPUT);
    pinMode(DISTANCEEHCO, INPUT);

    Serial.begin(9600);
}

void loop() {
  // Clear the trigPin at the start of the loop
  digitalWrite(DISTANCETRIG, LOW);
  delayMicroseconds(2);

  // Manual override
  if (digitalRead(BUTTONPIN) == LOW) {
    myservo.write(SERVODISPENSING);
    Serial.print("Override detected");
  }

  // Trigger the sensor to find the time in microseconds
  digitalWrite(DISTANCETRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(DISTANCETRIG, LOW);

  // Read the pin and find the time in microseconds the sound wave took
  duration = pulseIn(DISTANCEEHCO, HIGH);

  // Calculate the distance
  distance = duration * 0.0344 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  // Automatically open when the sensor senses within distance
  if (distance < 15) {
    myservo.write(SERVODISPENSING);
  } else {
    myservo.write(SERVOHOME);
  }

}