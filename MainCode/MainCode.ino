#include <Servo.h>

// =====================================================
// PIN
// =====================================================

// -------------------------
// SERVO
// -------------------------
const int SERVO_DOOR1 = 2;
const int SERVO_DOOR2 = 3;
const int SERVO_DOOR3 = 4;
const int SERVO_DOOR4 = 5;
const int SERVO_DOOR5 = 6;

// ----------------
// Led Traffic
// ----------------
const int yellow = 13;
const int green = 14;
const int red = 15;
unsigned long light = 0;
unsigned long mil;
unsigned long nowmillis;


// -------------------------
// SWITCH
// -------------------------
const int SWITCH1 = 7;
const int SWITCH2 = 8;


// -------------------------
// LASER 1
// TX = D9
// RX = D10
// -------------------------
const int LASER_TX1 = 9;
const int LASER_RX1 = 10;


// -------------------------
// LASER 2
// TX = D11
// RX = D12
// -------------------------
const int LASER_TX2 = 11;
const int LASER_RX2 = 12;


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
// STATE
// =====================================================

// Switch
bool lastSwitch1 = HIGH;
bool lastSwitch2 = HIGH;

// ประตู 1
bool door1Opened = false;

// ประตู 2
bool door2Locked = false;

// ประตู 3
bool door3Locked = false;

// ประตู 4
bool door4Opened = false;

// ประตู 5
bool door5Opened = false;
bool door5Locked = false;

// Laser
bool laser1Detected = false;
bool laser2Detected = false;


// =====================================================
// TIMER ประตู 5
// =====================================================

unsigned long door5Timer = 0;

const unsigned long DOOR5_INTERVAL = 5000;


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(9600);


  //=======================
  // Led Traffic
  // ======================
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(yellow, HIGH);


  // ===================================================
  // SWITCH
  // ===================================================

  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SWITCH2, INPUT_PULLUP);


  // ===================================================
  // LASER
  // ===================================================

  pinMode(LASER_TX1, OUTPUT);
  pinMode(LASER_RX1, INPUT);

  pinMode(LASER_TX2, OUTPUT);
  pinMode(LASER_RX2, INPUT);


  // เปิด Laser
  digitalWrite(LASER_TX1, HIGH);
  digitalWrite(LASER_TX2, HIGH);


  // ===================================================
  // SERVO
  // ===================================================

  door1.attach(SERVO_DOOR1);
  door2.attach(SERVO_DOOR2);
  door3.attach(SERVO_DOOR3);
  door4.attach(SERVO_DOOR4);
  door5.attach(SERVO_DOOR5);


  // ===================================================
  // RESET → ปิดประตูทั้งหมด
  // ===================================================

  door1.write(CLOSED);
  door2.write(CLOSED);
  door3.write(CLOSED);
  door4.write(CLOSED);
  door5.write(CLOSED);


  // Reset state

  door1Opened = false;

  door2Locked = false;

  door3Locked = false;

  door4Opened = false;

  door5Opened = false;

  door5Locked = false;

  laser1Detected = false;

  laser2Detected = false;


  // เริ่ม Timer ประตู 5

  door5Timer = millis();


  // ===================================================
  // MESSAGE
  // ===================================================

  Serial.println();
  Serial.println("================================");
  Serial.println("       ROBOT FIELD START");
  Serial.println("================================");

  Serial.println("Door 1 : CLOSED");
  Serial.println("Door 2 : CLOSED");
  Serial.println("Door 3 : CLOSED");
  Serial.println("Door 4 : CLOSED");
  Serial.println("Door 5 : CLOSED");

  Serial.println("System Ready");
  Serial.println("================================");


  // ให้ Servo กลับตำแหน่งปิด
  delay(1000);
}


// =====================================================
// LOOP
// =====================================================

void loop() {

  //=============================
  // Led Traffic
  //=============================
  nowmillis = millis();
  mil = 5000;
  if(nowmillis - light >= mil){
    light = nowmillis;
    if(digitalRead(yellow) == HIGH){
      door5.write(OPEN);
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
    }else if(digitalRead(green) == HIGH){
      door5.write(CLOSED);
      digitalWrite(yellow, HIGH);
      digitalWrite(green, LOW);
    }
  }


  // ===================================================
  // DOOR 1
  // SWITCH 1 → เปิดประตู 1
  // ===================================================

  int switch1State = digitalRead(SWITCH1);


  if (lastSwitch1 == HIGH &&
      switch1State == LOW &&
      !door1Opened) {

    Serial.println("SWITCH 1");
    Serial.println("DOOR 1 -> OPEN");

    door1.write(OPEN);

    // เปิดค้าง
    door1Opened = true;

    delay(300);
  }

  lastSwitch1 = switch1State;


  // ถ้าเปิดแล้ว → เปิดค้าง
  if (door1Opened) {
    door1.write(OPEN);
  }


  // ===================================================
  // LASER 1 → DOOR 2
  //
  // HIGH = เจอ Laser
  // LOW  = ไม่เจอ Laser
  // ===================================================

  int laser1State = digitalRead(LASER_RX1);


  // -----------------------------------------------
  // Laser เจอ
  // → เปิดประตู 2
  // -----------------------------------------------

  if (laser1State == HIGH &&
      !laser1Detected &&
      !door2Locked) {

    laser1Detected = true;

    Serial.println("LASER 1 DETECTED");
    Serial.println("DOOR 2 -> OPEN");

    door2.write(OPEN);
  }


  // -----------------------------------------------
  // Laser ขาด
  // → ปิดประตู 2
  // → ล็อกค้าง
  // -----------------------------------------------

  if (laser1Detected &&
      laser1State == LOW &&
      !door2Locked) {

    Serial.println("LASER 1 LOST");
    Serial.println("DOOR 2 -> CLOSED");
    Serial.println("DOOR 2 -> LOCKED");

    door2.write(CLOSED);

    door2Locked = true;
  }


  // -----------------------------------------------
  // ล็อกแล้ว → ปิดค้าง
  // -----------------------------------------------

  if (door2Locked) {
    door2.write(CLOSED);
  }


  // ===================================================
  // LASER 2 → DOOR 3
  //
  // HIGH = เจอ Laser
  // LOW  = ไม่เจอ Laser
  // ===================================================

  int laser2State = digitalRead(LASER_RX2);


  // -----------------------------------------------
  // Laser เจอ
  // → เปิดประตู 3
  // -----------------------------------------------

  if (laser2State == HIGH &&
      !laser2Detected &&
      !door3Locked) {

    laser2Detected = true;

    Serial.println("LASER 2 DETECTED");
    Serial.println("DOOR 3 -> OPEN");

    door3.write(OPEN);
  }


  // -----------------------------------------------
  // Laser ขาด
  // → ปิดประตู 3
  // → ล็อกค้าง
  // → ปิดประตู 5
  // -----------------------------------------------

  if (laser2Detected &&
      laser2State == LOW &&
      !door3Locked) {

    Serial.println("LASER 2 LOST");
    Serial.println("DOOR 3 -> CLOSED");
    Serial.println("DOOR 3 -> LOCKED");

    door3.write(CLOSED);

    door3Locked = true;


    // ---------------------------------------------
    // ประตู 3 ถูกปิด
    // → ประตู 5 ปิดค้าง
    // ---------------------------------------------

    Serial.println("DOOR 5 -> CLOSED");
    Serial.println("DOOR 5 -> LOCKED");

    door5.write(CLOSED);

    door5Opened = false;
    door5Locked = true;
  }


  // -----------------------------------------------
  // ประตู 3 ล็อก → ปิดค้าง
  // -----------------------------------------------

  if (door3Locked) {
    door3.write(CLOSED);
  }


  // ===================================================
  // SWITCH 2 → DOOR 4
  // ===================================================

  int switch2State = digitalRead(SWITCH2);


  if (lastSwitch2 == HIGH &&
      switch2State == LOW &&
      !door4Opened) {

    Serial.println("SWITCH 2");
    Serial.println("DOOR 4 -> OPEN");

    door4.write(OPEN);

    // เปิดค้าง
    door4Opened = true;

    delay(300);
  }

  lastSwitch2 = switch2State;


  // ถ้าเปิดแล้ว → เปิดค้าง
  if (door4Opened) {
    door4.write(OPEN);
  }


  // ===================================================
  // DOOR 5
  //
  // เปิด/ปิดทุก 5 วินาที
  // จนกว่าจะถูก Lock
  // ===================================================

  if (!door5Locked) {

    if (millis() - door5Timer >= DOOR5_INTERVAL) {

      door5Timer = millis();


      // ---------------------------------------------
      // ปิด → เปิด
      // ---------------------------------------------

      if (!door5Opened) {

        door5.write(OPEN);

        door5Opened = true;

        Serial.println("DOOR 5 -> OPEN");
      }


      // ---------------------------------------------
      // เปิด → ปิด
      // ---------------------------------------------

      else {

        door5.write(CLOSED);

        door5Opened = false;

        Serial.println("DOOR 5 -> CLOSED");
      }
    }
  }


  // ===================================================
  // ถ้า Door 5 ถูก Lock
  // → ปิดตลอด
  // ===================================================

  if (door5Locked) {

    door5.write(CLOSED);

    door5Opened = false;
  }


  delay(50);
}
