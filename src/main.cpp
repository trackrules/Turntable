#include <Arduino.h>
/*Example sketch to control a stepper motor
  with DRV8825 stepper motor driver, AccelStepper library
  and Arduino: number of steps or revolutions.
  More info: https://www.makerguides.com */

#include "AccelStepper.h"

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 4
#define stepPin 3
#define motorInterfaceType 1

#define l_pwn 7 // blue
#define l_en 8  // green
#define r_pwn 9 // yellow
#define r_en 10 // orange

int min_revs = 200;
int micro_steps = 16;
int steps_per_rev = min_revs * steps_per_rev;
int revs = 2;

int DIST_PIN = 7;
int lastState = HIGH;
int downtime = 1000;
// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void motors()
{
  // put your main code here, to run repeatedly:

  // Use an analogWrite(pin,  which tells it to send a modulated
  // signal (PWM) to specific pin at a specific "duty cycle".
  // Valid values are 0 to 255.  0 means always off(or no power) and 255 means always on(full power)
  // https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
  analogWrite(r_pwn, 64); // pulse a signal continually at the rate of 64
  Serial.println("r_pwn: 64");
  // the analogWrite line above should start the motor turning in one direction at about 1/4 of power.
  delay(downtime);         // wait 5 seconds, motor continues to move because the analogWrite is still pulsing
  analogWrite(r_pwn, 128); // pulse signal now at 128 (about half power... half of max 255).
  Serial.println("r_pwn: 128");
  delay(downtime);

  // after 5 seconds at half power, stop the motor moving
  analogWrite(r_pwn, 0);
  Serial.println("r_pwn: 0");

  delay(downtime);

  // // now start moving in opposite direction.
  // analogWrite(l_pwn, 64);
  // delay(downtime);
  // analogWrite(l_pwn, 128);
  // delay(downtime);
  // analogWrite(l_pwn, 0); // Stop moving in this direction

  // at this point should be no movement.

  delay(downtime);
}
void read_encoder(){
  
}

void setup()
{
  pinMode(DIST_PIN, INPUT);
  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(6400);
  stepper.setAcceleration(1600);

  for (int i = 7; i <= 10; i++)
  {
    pinMode(i, OUTPUT);
  }
  // set all the pins you want to use to LOW
  for (int i = 7; i <= 10; i++)
  {
    digitalWrite(i, LOW);
  }
  digitalWrite(l_en, HIGH);
  digitalWrite(r_en, HIGH);
}

void loop()
{
  // Set the current position to 0:
  // motors();
  int currentState = digitalRead(DIST_PIN); // Read the current state of the signal pin

  // if (true) // currentState == LOW && lastState == HIGH)
  // {         // Check for falling edge
  //   // Rotate the stepper motor one revolution

  //   stepper.setCurrentPosition(0);

  //   // Run the motor forward at 200 steps/second until the motor reaches 400 steps (2 revolutions):
  //   while (stepper.currentPosition() != (6400))
  //   {
  //     stepper.setSpeed(6400);
  //     stepper.runSpeed();
  //   }

  //   delay(2000);
  //   // // Wait for the signal to go high again
  //   // while (digitalRead(DIST_PIN) == LOW)
  //   // {
  //   //   delay(10);
  //   // }
  // }

  lastState = currentState; // Update the last state
  delay(10);                // Small delay to debounce
}