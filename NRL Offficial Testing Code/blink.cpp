#include <Arduino.h>

// Step 1: Blink Built-in LED on ESP32
// This program will turn ON and OFF the LED every 1 second.

int ledPin = 2; // Define LED pin

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin as output
}

void loop() {
  digitalWrite(ledPin, HIGH); // Turn LED ON
  delay(1000);                // Wait 1 second
  digitalWrite(ledPin, LOW);  // Turn LED OFF
  delay(1000);                // Wait 1 second
}