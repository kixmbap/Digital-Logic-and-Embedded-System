#include <Servo.h>

// servo PIN
const int SERVO_DOOR1 = 2;
const int SERVO_DOOR2 = 3;
const int SERVO_DOOR3 = 4;
const int SERVO_DOOR4 = 5;
const int SERVO_DOOR5 = 6;

// Led Traffic
const int yellow = 14;
const int green = 15;
const int red = 16;
unsigned long light = 0;
unsigned long mil;
unsigned long nowmillis;

// SWITCH
const int SWITCH1 = 7;
const int SWITCH2 = 8;

// LASER 1, 2
const int LASER_TX1 = 9;
const int LASER_RX1 = 10;
const int LASER_TX2 = 11;
const int LASER_RX2 = 12;

// SERVO
Servo door1;
Servo door2;
Servo door3;
Servo door4;
Servo door5;


// ANGLE
const int CLOSED = 0;
const int OPEN = 90;
const int motor2aclosed = 90;
const int motor2aopen = 180;

// Switch
bool lastSwitch1 = HIGH;
bool lastSwitch2 = HIGH;

// ประตู 1,2,3,4,5
bool door1Opened = false;
bool door2Locked = false;
bool door3Locked = false;
bool door4Opened = false;
bool door5Opened = false;
bool door5Locked = false;

// Laser
bool laser1Detected = false;
bool laser2Detected = false;

// TIMER ประตู 5
unsigned long door5Timer = 0;

const unsigned long DOOR5_INTERVAL = 5000;

const int swpin = 17;
const int IRpin = 18;

bool startround = false;
int lastIR = 0;
bool endround = false;

unsigned long runtimer = 0;
unsigned long interval = 1000;
unsigned long totalTime = 0;

void setup() {
  Serial.begin(9600);
  timerPinSetup();

  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(yellow, HIGH);

  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SWITCH2, INPUT_PULLUP);

  pinMode(LASER_TX1, OUTPUT);
  pinMode(LASER_RX1, INPUT);
  pinMode(LASER_TX2, OUTPUT);
  pinMode(LASER_RX2, INPUT);

  digitalWrite(LASER_TX1, HIGH);
  digitalWrite(LASER_TX2, HIGH);

  door1.attach(SERVO_DOOR1);
  door2.attach(SERVO_DOOR2);
  door3.attach(SERVO_DOOR3);
  door4.attach(SERVO_DOOR4);
  door5.attach(SERVO_DOOR5);

  // RESET → ปิดประตูทั้งหมด
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

  // MESSAGE
  Serial.println();
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

//LOOP
void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'R' || cmd == 'r') {
      resetField();
    }
  }
  timerCount(runtimer, interval, totalTime, startround, endround);
  checkIRstart(IRpin, lastIR, runtimer, startround);
  checkSWEND(swpin, totalTime, startround, endround);

  // Led Traffic
  if(door5Locked == true){
    door5.write(CLOSED);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  } else {
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
  }

  // SWITCH 1 → เปิดประตู 1
  int switch1State = digitalRead(SWITCH1);
  if (lastSwitch1 == HIGH &&
      switch1State == LOW &&
      !door1Opened) {
    Serial.println("SWITCH 1");
    Serial.println("DOOR 1 -> OPEN");
    door1.write(OPEN);
    door1Opened = true;
    delay(300);
  }
  lastSwitch1 = switch1State;
  // ถ้าเปิดแล้ว → เปิดค้าง
  if (door1Opened) {
    door1.write(OPEN);
  }

  // LASER 1 → DOOR 2
  //HIGH = เจอ Laser, LOW  = ไม่เจอ Laser
  int laser1State = digitalRead(LASER_RX1);
  // Laser เจอ → เปิดประตู 2
  if (laser1State == HIGH &&
      !laser1Detected &&
      !door2Locked) {
    laser1Detected = true;
    Serial.println("LASER 1 DETECTED");
    Serial.println("DOOR 2 -> OPEN");
    door2.write(motor2aopen);
  }
  // Laser ขาด → ปิดประตู 2 → ล็อกค้าง
  if (laser1Detected &&
      laser1State == LOW &&
      !door2Locked) {
    Serial.println("LASER 1 LOST");
    Serial.println("DOOR 2 -> CLOSED");
    Serial.println("DOOR 2 -> LOCKED");
    door2.write(motor2aclosed);
    door2Locked = true;
  }
  // ล็อกแล้ว → ปิดค้าง
  if (door2Locked) {
    door2.write(motor2aclosed);
  }



  // LASER 2 → DOOR 3
  // HIGH = เจอ Laser, LOW  = ไม่เจอ Laser
  int laser2State = digitalRead(LASER_RX2);
  // Laser เจอ → เปิดประตู 3
  if (laser2State == HIGH &&
      !laser2Detected &&
      !door3Locked) {
    laser2Detected = true;
    Serial.println("LASER 2 DETECTED");
    Serial.println("DOOR 3 -> OPEN");
    door3.write(OPEN);
  }
  // Laser ขาด → ปิดประตู 3 → ล็อกค้าง → ปิดประตู 5
  if (laser2Detected &&
      laser2State == LOW &&
      !door3Locked) {
    Serial.println("LASER 2 LOST");
    Serial.println("DOOR 3 -> CLOSED");
    Serial.println("DOOR 3 -> LOCKED");
    door3.write(CLOSED);
    door3Locked = true;

    // ประตู 3 ถูกปิด → ประตู 5 ปิดค้าง
    Serial.println("DOOR 5 -> CLOSED");
    Serial.println("DOOR 5 -> LOCKED");
    door5.write(CLOSED);
    door5Opened = false;
    door5Locked = true;
  }
  // ประตู 3 ล็อก → ปิดค้าง
  if (door3Locked) {
    door3.write(CLOSED);
  }

  // SWITCH 2 → DOOR 4
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

  // DOOR5 เปิด/ปิดทุก 5 วินาที จนกว่าจะถูก Lock
  if (!door5Locked) {
    if (millis() - door5Timer >= DOOR5_INTERVAL) {
      door5Timer = millis();
      // ปิด → เปิด
      if (!door5Opened) {
        door5.write(OPEN);
        door5Opened = true;
        Serial.println("DOOR 5 -> OPEN");
      }
      // เปิด → ปิด
      else {
        door5.write(CLOSED);
        door5Opened = false;
        Serial.println("DOOR 5 -> CLOSED");
      }
    }
  }
  // ถ้า Door 5 ถูก Lock → ปิดตลอด
  if (door5Locked) {
    door5.write(CLOSED);
    door5Opened = false;
  }

  delay(50);
}

void timerPinSetup(){
  pinMode(swpin, INPUT_PULLUP);
  pinMode(IRpin, INPUT);
}

void timerCount(unsigned long &timer, unsigned long interval, unsigned long &totalTime, bool startround, bool endround){
  if(millis() - timer >= interval && startround && !endround){
    timer = millis();
    totalTime += interval/1000;
    unsigned long mins, secs;
    convertTime(totalTime, mins, secs);
    Serial.print(" Time : ");
    printTime(mins, secs);
    Serial.println();
  }
}

unsigned long convertTime(unsigned long totalTime, unsigned long &mins, unsigned long &secs){
  mins = (totalTime) / 60;
  secs = (totalTime) % 60;
  if(mins < 1){
    mins = 0;
    secs = totalTime;
  }
}

void printTime(unsigned long mins, unsigned long secs){
  if(mins >= 1){
    Serial.print(mins);
    Serial.print(":");
    if(secs < 10){
      Serial.print("0");
    }
    Serial.print(secs);
    Serial.print(" minutes");
  } else {
    Serial.print(secs);
    Serial.print(" seconds");
  }
}

void checkIRstart(const int IRpin, int &lastIR, unsigned long &timer, bool &startround){
  int nowIR = digitalRead(IRpin);
  if(nowIR == 1){
    if(lastIR == 0 && !startround){
      timer = millis();
      Serial.print("Time start now. (");
      Serial.print(timer);
      Serial.println(")");
      startround = true;
    }
  } else {
    lastIR = nowIR;
  }
}

void checkSWEND(const int swPin, unsigned long totaltime, bool &startround, bool &endround){
  if(startround && digitalRead(swPin) == 0 && !endround){
    endround = true;
        Serial.print("Time end. using ");
        unsigned long mins, secs;
        convertTime(totalTime, mins, secs);
        printTime(mins, secs);
        Serial.print(" (");
        Serial.print(millis());
        Serial.println(")");  
  }
}

void resetField() {
  // RESET -> ปิดประตูทั้งหมด
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

  // เริ่ม Timer ประตู 5 ใหม่
  door5Timer = millis();

  // รีเซ็ตสถานะการเล่นรอบปัจจุบัน
  startround = false;
  endround = false;
  totalTime = 0;
  runtimer = 0;
  lastIR = 0;

  // รีเซ็ตไฟจราจรเป็นสถานะเริ่มต้น
  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);

  Serial.println("SYSTEM_RESET_COMPLETE");
  Serial.println("System Ready");
  Serial.println("================================");
}