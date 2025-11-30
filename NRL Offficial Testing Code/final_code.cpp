// =============================== 
// NRL Robot Base Code - PS5 

// Core Arduino library 
#include <Arduino.h>       
#include <ps5Controller.h> // PS5 controller library 
#include <ESP32Servo.h>    // Servo library for ESP32 

// ===== Motor Pins ===== 
const int left_DIR  = 32; 
const int left_PWM  = 33; 
const int right_DIR = 25; 
const int right_PWM = 26; 

const String PS5_MAC_ADDRESS = "50:EE:32:D9:71:37";

// Motor direction inversion (adjust if motors run backward) 
bool reverseLeftMotor  = false; 
bool reverseRightMotor = true; 

// ===== Servo Pins ===== 
const int ARM_PIN     = 14; 
const int GRIPPER_PIN = 13; 

// ===== Servo Objects ===== 
Servo armServo; 
Servo gripperServo;

// ===== Servo Positions ===== 
int ARM     = 90;   // initial arm position 
int GRIPPER = 90;   // initial gripper position 

// ===== Arm Positions =====
const int ARM_UP   = 180;  // Triangle → Arm up
const int ARM_DOWN = 0;    // Cross → Arm down

// ===== Gripper Open/Close Positions =====
const int GRIPPER_OPEN  = 20;  // Circle → Open
const int GRIPPER_CLOSE = 95;  // Square → Close

// ===== Motor Control Function ===== 
void setMotor(int pwmPin, int dirPin, int speed, bool reverse) { 
  speed = constrain(speed, -255, 255); 
  bool direction = speed >= 0; 
  if (reverse) direction = !direction; 
  digitalWrite(dirPin, direction); 
  analogWrite(pwmPin, abs(speed)); 
} 

void setup() { 
  Serial.begin(921600); 
  Serial.println("Robot Base Code Started"); 

  pinMode(left_DIR, OUTPUT); 
  pinMode(left_PWM, OUTPUT); 
  pinMode(right_DIR, OUTPUT); 
  pinMode(right_PWM, OUTPUT); 

  armServo.attach(ARM_PIN); 
  gripperServo.attach(GRIPPER_PIN); 

  armServo.write(ARM); 
  gripperServo.write(GRIPPER); 

  ps5.begin(PS5_MAC_ADDRESS.c_str()); 
  Serial.println("Waiting for PS5 Controller..."); 
} 

void loop() { 
  if (ps5.isConnected()) { 
    int speed = map(ps5.LStickY(), -128, 127, -255, 255); 
    int turn  = map(ps5.RStickX(), -128, 127, 255, -255); 

    if (abs(speed) < 20) speed = 0; 
    if (abs(turn)  < 20) turn  = 0; 

    int leftSpeed  = constrain(speed + turn, -255, 255); 
    int rightSpeed = constrain(speed - turn, -255, 255); 
    // Tip: If robot moves in reverse or turns incorrectly, swap the sign of the last two map() values (e.g., -255, 255 → 255, -255) for speed or turn


    setMotor(left_PWM, left_DIR, leftSpeed, reverseLeftMotor); 
    setMotor(right_PWM, right_DIR, rightSpeed, reverseRightMotor); 

    // ===== ARM CONTROL ===== 
    if (ps5.Triangle()) ARM = ARM_UP; 
    if (ps5.Cross())    ARM = ARM_DOWN; 
    armServo.write(ARM); 

    // ===== GRIPPER CONTROL ===== 
    if (ps5.Square())  GRIPPER = GRIPPER_CLOSE; 
    if (ps5.Circle())  GRIPPER = GRIPPER_OPEN; 
    gripperServo.write(GRIPPER); 

    delay(20); 
  } else { 
    Serial.println("Controller disconnected. Waiting to reconnect..."); 
    delay(1000); 
  } 
} 