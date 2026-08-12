#include <Servo.h>

// =====================================================
// SERVO PIN
// =====================================================

const int SERVO_DOOR1 = 2;
const int SERVO_DOOR2 = 3;
const int SERVO_DOOR3 = 4;
const int SERVO_DOOR4 = 5;
const int SERVO_DOOR5 = 6;

// =====================================================
// SERVO
// =====================================================

Servo door1;
Servo door2;
Servo door3;
Servo door4;
Servo door5;

// =====================================================
// ANGLE
// =====================================================

const int CLOSED = 0;
const int OPEN = 90;

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(9600);

  // Attach Servo
  door1.attach(SERVO_DOOR1);
  door2.attach(SERVO_DOOR2);
  door3.attach(SERVO_DOOR3);
  door4.attach(SERVO_DOOR4);
  door5.attach(SERVO_DOOR5);

  // เริ่มต้นปิดทุกประตู
  door1.write(CLOSED);
  door2.write(CLOSED);
  door3.write(CLOSED);
  door4.write(CLOSED);
  door5.write(CLOSED);

  Serial.println();
  Serial.println("================================");
  Serial.println("       SERVO TEST START");
  Serial.println("================================");

  Serial.println("Door 1 : CLOSED");
  Serial.println("Door 2 : CLOSED");
  Serial.println("Door 3 : CLOSED");
  Serial.println("Door 4 : CLOSED");
  Serial.println("Door 5 : CLOSED");

  delay(2000);
}

// =====================================================
// LOOP
// =====================================================

void loop() {

  // ===================================================
  // DOOR 1
  // ===================================================

  Serial.println("DOOR 1 -> OPEN");
  door1.write(OPEN);

  delay(2000);

  Serial.println("DOOR 1 -> CLOSED");
  door1.write(CLOSED);

  delay(1000);


  // ===================================================
  // DOOR 2
  // ===================================================

  Serial.println("DOOR 2 -> OPEN");
  door2.write(OPEN);

  delay(2000);

  Serial.println("DOOR 2 -> CLOSED");
  door2.write(CLOSED);

  delay(1000);


  // ===================================================
  // DOOR 3
  // ===================================================

  Serial.println("DOOR 3 -> OPEN");
  door3.write(OPEN);

  delay(2000);

  Serial.println("DOOR 3 -> CLOSED");
  door3.write(CLOSED);

  delay(1000);


  // ===================================================
  // DOOR 4
  // ===================================================

  Serial.println("DOOR 4 -> OPEN");
  door4.write(OPEN);

  delay(2000);

  Serial.println("DOOR 4 -> CLOSED");
  door4.write(CLOSED);

  delay(1000);


  // ===================================================
  // DOOR 5
  // ===================================================

  Serial.println("DOOR 5 -> OPEN");
  door5.write(OPEN);

  delay(2000);

  Serial.println("DOOR 5 -> CLOSED");
  door5.write(CLOSED);

  delay(2000);


  // ===================================================
  // TEST COMPLETE
  // ===================================================

  Serial.println("================================");
  Serial.println("       TEST COMPLETE");
  Serial.println("================================");

  delay(2000);
}