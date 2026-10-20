#include <Arduino.h>
#include <Servo.h>

// Create a servo object
Servo myservo;

void setup() {
    myservo.attach(9);
    myservo.write(0);
    Serial.begin(9600);
}

void loop() {
    // Change the position of the servo to 0 degrees
    Serial.println("Moving to 0 degrees");
    myservo.write(0);
    delay(200);

    // Move it to 90 degrees
    myservo.write(90);
    delay(200);
}