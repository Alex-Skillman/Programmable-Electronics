#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <FastEspnow.h>

// Used to set it up for the type of driver we are using
#define DRIVER_INTERFACE 1

// Set Stepper 1 Pins
const int STEP_PIN_1 = 11;
const int DIR_PIN_1 = 12;
// Set Stepper 2 Pins
const int STEP_PIN_2= 13;
const int DIR_PIN_2 = 14;

// Create the stepper motor instances
AccelStepper stepper_1(DRIVER_INTERFACE, STEP_PIN_1, DIR_PIN_1);
AccelStepper stepper_2(DRIVER_INTERFACE, STEP_PIN_2, DIR_PIN_2);

// Joins both steppers into a multistepper
MultiStepper steppers;

// Create a variable to hold the amount of steps for each motor
long positions[2];

void setup() {
    // Max Speed for the steppers - steps/s
    stepper_1.setMaxSpeed(1000);
    stepper_2.setMaxSpeed(1000);
    // Max acelleration for the steppers - steps/s/s
    stepper_1.setAcceleration(500);
    stepper_2.setAcceleration(500);
}

void loop() {
}