#include <Arduino.h>
#include <Servo.h>

// Create a servo object
Servo myservo;

// Create positions for the servo
int SERVOHOME = 110;
int SERVODISPENSING = SERVOHOME - 50;

// Create variables for the pins
int SERVOPIN = 9;
int BUTTONPIN = 7;
int DISTANCETRIG = 5;
int DISTANCEEHCO = 6;

// Create variables for distance and duration
long duration;
float distance;

// Variable that holds the current button state: 1-Not pressed, 0-Pressed
int ButtonState;

// Function that reads the distance from the ultrasonic sensor 
long readDistance() {
  // Clear the DISTANCETRIG first for a clean pulse
  digitalWrite(DISTANCETRIG, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor to find the time in microseconds
  digitalWrite(DISTANCETRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(DISTANCETRIG, LOW);

  // Read the pin and find the time in microseconds the sound wave took
  duration = pulseIn(DISTANCEEHCO, HIGH, 30000); // 30ms timeout prevents freezing if no echo

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

void setup() {
    // Configure the servo
    myservo.attach(SERVOPIN);
    myservo.write(SERVOHOME);
    
    // Configure pins
    pinMode(DISTANCETRIG, OUTPUT);
    pinMode(DISTANCEEHCO, INPUT);
    pinMode(BUTTONPIN, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
  // Manual override read
  ButtonState = digitalRead(BUTTONPIN);

  // Read the distance from the sensor
  distance = readDistance();

  // Logic gate: Activate if the button is pressed OR an object is close (<= 15cm)
  bool is_activated = (ButtonState == LOW) || (distance <= 10);
  
  // Move servo based on activation state
  if (is_activated) {
    myservo.write(SERVOHOME);
  } else {
    delay(700);
    myservo.write(SERVODISPENSING);
  }
}
