/*
 * =====================================================================
 *  PROJECT      : Autonomous Line Following Robot
 *  SYSTEM / ENG : AJ-ORBIT
 *  AUTHOR       : AJ_ORBIT (The Bhadohi Coder)
 *  VERSION      : 1.0.0
 *  HARDWARE     : Arduino Uno R3 | L298N H-Bridge | Dual IR Sensors
 *  DATE         : 2026
 *  DESCRIPTION  : Dual-sensor line tracking algorithm with differential
 *                 PWM drive control for high-precision autonomous navigation.
 * =====================================================================
 */

// ======================= MOTOR PIN CONFIGURATION =======================
// Motor A (Left Track/Wheel)
const int ENA = 11; // PWM Speed Control
const int IN1 = 10; // Direction Pin 1
const int IN2 = 9;  // Direction Pin 2

// Motor B (Right Track/Wheel)
const int ENB = 6;  // PWM Speed Control
const int IN3 = 8;  // Direction Pin 3
const int IN4 = 7;  // Direction Pin 4

// ========================== SPEED PARAMETERS ==========================
#define BASE_SPEED    100  // Base cruising speed (PWM 0-255)
#define TURN_SPEED    130  // Differential turning speed (PWM 0-255)

// ======================= SENSOR PIN CONFIGURATION ======================
const int IRSensorLeft  = 2;  // Left IR Tracker Digital Pin
const int IRSensorRight = 3;  // Right IR Tracker Digital Pin

// ========================== FUNCTION PROTOTYPES ========================
void moveForward();
void turnRight();
void turnLeft();
void stopMotors();
void printOrbitBanner();

// ================================ SETUP ================================
void setup() {
  // Motor Driver Control Outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Digital Sensor Inputs
  pinMode(IRSensorLeft, INPUT);
  pinMode(IRSensorRight, INPUT);

  // Initialize AJ-ORBIT Diagnostics Console
  Serial.begin(9600);
  printOrbitBanner();
}

// ============================== MAIN LOOP ==============================
void loop() {
  bool leftSensor  = digitalRead(IRSensorLeft);
  bool rightSensor = digitalRead(IRSensorRight);

  // Real-time telemetry feed
  Serial.print(F("[AJ-ORBIT] L: "));
  Serial.print(leftSensor);
  Serial.print(F(" | R: "));
  Serial.print(rightSensor);
  Serial.print(F(" -> Status: "));

  // Navigation Logic (White Surface = LOW, Black Line = HIGH)
  if (leftSensor == LOW && rightSensor == LOW) {
    Serial.println(F("FORWARD"));
    moveForward();
  } 
  else if (leftSensor == LOW && rightSensor == HIGH) {
    Serial.println(F("CORRECTING RIGHT"));
    turnRight();
  } 
  else if (leftSensor == HIGH && rightSensor == LOW) {
    Serial.println(F("CORRECTING LEFT"));
    turnLeft();
  } 
  else {
    Serial.println(F("LINE LOST / STOPPED"));
    stopMotors();
  }

  delay(20); // Low latency response loop
}

// ========================= NAVIGATION ROUTINES =========================

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, BASE_SPEED);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, BASE_SPEED);
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, TURN_SPEED);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, TURN_SPEED);
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, TURN_SPEED);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, TURN_SPEED);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

// ======================= SERIAL BRANDING BANNER =======================
void printOrbitBanner() {
  Serial.println(F("=================================================="));
  Serial.println(F("              >>>  AJ-ORBIT CORE  <<<            "));
  Serial.println(F("       AUTONOMOUS LINE TRACKING SYSTEM v1.0       "));
  Serial.println(F("          Developed by: Anant Jaiswal         "));
  Serial.println(F("=================================================="));
  Serial.println(F("[SYSTEM] Motor drivers initialized..."));
  Serial.println(F("[SYSTEM] IR sensors active..."));
  Serial.println(F("[SYSTEM] Ready to trace line.\n"));
}