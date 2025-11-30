// ----------------------------------------------------------
// ESP32 Servo Motor Control
// ----------------------------------------------------------
// This program moves a servo motor from MIN to MAX position
// using the ESP32Servo library.
// ----------------------------------------------------------

#include <Arduino.h>
#include <ESP32Servo.h>

Servo myServo;

// Define servo movement limits (in degrees)
// Change these to test the custom range

int MIN_ANGLE = 90;    // minimum angle
int MAX_ANGLE = 120;  // maximum angle

int currentAngle = MIN_ANGLE;

void setup() {
  Serial.begin(115200);
  myServo.attach(14); // Attach servo to pin 14
  Serial.println("Servo Test: Moving from MIN to MAX");
}

void loop() {
  // Move from MIN to MAX
  for (int angle = MIN_ANGLE; angle <= MAX_ANGLE; angle++) {
    myServo.write(angle);
    delay(15); // adjust for speed of motion
  }

  // Pause briefly at max
  delay(500);

  // Move from MAX back to MIN
  for (int angle = MAX_ANGLE; angle >= MIN_ANGLE; angle--) {
    myServo.write(angle);
    delay(15);
  }

  // Pause briefly at min
  delay(500);
}