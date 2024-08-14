#include <Arduino.h>
/*Example sketch to control a stepper motor 
  with DRV8825 stepper motor driver, AccelStepper library 
  and Arduino: number of steps or revolutions. 
  More info: https://www.makerguides.com */

#include "AccelStepper.h"

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1
int min_revs = 200;
int micro_steps = 16;
int steps_per_rev = min_revs * steps_per_rev;
int revs = 2;

int DIST_PIN = 7;
int lastState = HIGH;  

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);


void setup() {
  pinMode(DIST_PIN, INPUT);
  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(6400);
  stepper.setAcceleration(1600);
}

void loop() { 
  // Set the current position to 0:

    int currentState = digitalRead(DIST_PIN); // Read the current state of the signal pin

  if (currentState == LOW && lastState == HIGH) { // Check for falling edge
    // Rotate the stepper motor one revolution
    
  stepper.setCurrentPosition(0);

  // Run the motor forward at 200 steps/second until the motor reaches 400 steps (2 revolutions):
  while(stepper.currentPosition() != (6400))
  {
    stepper.setSpeed(6400);
    stepper.runSpeed();
  }

  delay(1000);
    // Wait for the signal to go high again
    while (digitalRead(DIST_PIN) == LOW) {
      delay(10);
    }
  }

  lastState = currentState; // Update the last state
  delay(10); // Small delay to debounce

}