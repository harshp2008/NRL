# include <Arduino.h>

// Step 2: Set Servo at 90 Degrees
// This program sets one servo motor to 90 degrees (center position)

#include <ESP32Servo.h>  // Library to control servo motors

Servo servo1;            // Create a servo object
int servoPin = 14;       // Servo connected to pin 14 (Arm servo).
                         // To test Gripper servo, change this to 13.

void setup() {
  servo1.attach(servoPin);  // Attach servo to pin 14
  servo1.write(90);         // Move servo to 90 degrees
}

void loop() {
  // Nothing here. The servo will stay at 90 degrees.
}