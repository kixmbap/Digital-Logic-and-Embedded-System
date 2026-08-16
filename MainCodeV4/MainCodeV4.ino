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

// IR 1, 2
const int IR1 = 9;
const int IR2 = 10;                                                                                                                                                                                                              

// SERVO
Servo door1;
Servo door2;
Servo door3;
Servo door4;
Servo door5;


// ANGLE
const int CLOSED = 0;
const int OPEN = 90;

const int servo1close = 90;
const int servo1open = 180;

const int servo2close = 0;
const int servo2open = 95;

const int servo3close = 90;
const int servo3open = 0;

const int servo4close = 180;
const int servo4open = 90;

const int servo5close = 90;
const int servo5open = 0;



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

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  door1.attach(SERVO_DOOR1);
  door2.attach(SERVO_DOOR2);
  door3.attach(SERVO_DOOR3);
  door4.attach(SERVO_DOOR4);
  door5.attach(SERVO_DOOR5);

  // RESET → ปิดประตูทั้งหมด
  door1.write(servo1close);
  door2.write(servo2close);
  door3.write(servo3close);
  door4.write(servo4close);
  door5.write(servo5close);


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
  Serial.println("LIGHT -> YELLOW");
  Serial.println("System Ready");
  Serial.println("================================");

  // ให้ Servo กลับตำแหน่งปิด
  delay(1000);
}

//LOOP
void loop() {
  timerCount(runtimer, interval, totalTime, startround, endround);
  checkIRstart(IRpin, lastIR, runtimer, startround);
  checkSWEND(swpin, totalTime, startround, endround);

  // Led Traffic
  
  if(door5Locked == true){
    //door5.write(CLOSED);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  } else {
    nowmillis = millis();
    if(nowmillis - light >= mil){
      light = nowmillis;
      if(digitalRead(red) == HIGH){ //if it's now red check
        mil = 2500;
        door5.write(servo5close);
        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(green, HIGH);
        Serial.println("LIGHT -> GREEN");
        Serial.println("DOOR 5 -> CLOSED");
      }else if(digitalRead(green) == HIGH){ //if it's now green check
        mil = 2500;
        digitalWrite(red, LOW);
        digitalWrite(yellow, HIGH);
        digitalWrite(green, LOW);
        Serial.println("LIGHT -> YELLOW");
      }
      else if(digitalRead(yellow) == HIGH){ //if it's now yellow check
        mil = 5000;
        door5.write(servo5open);
        digitalWrite(red, HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);
        Serial.println("LIGHT -> RED");
        Serial.println("DOOR 5 -> OPEN");
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
    door1.write(servo1open);
    door1Opened = true;
    delay(300);
  }
  lastSwitch1 = switch1State;
  // ถ้าเปิดแล้ว → เปิดค้าง
  if (door1Opened) {
    door1.write(servo1open);
  }

  checkIRservo(IR1, door2, servo2open, door2Locked);
  
  // SWITCH 2 → DOOR 4
  int switch2State = digitalRead(SWITCH2);
  if (lastSwitch2 == HIGH &&
      switch2State == LOW &&
      !door4Opened) {
    Serial.println("SWITCH 2");
    Serial.println("DOOR 4 -> OPEN");
    door4.write(servo4open);
    // เปิดค้าง
    door4Opened = true;
    delay(300);
  }
  lastSwitch2 = switch2State;
  // ถ้าเปิดแล้ว → เปิดค้าง
  if (door4Opened) {
    door4.write(servo4open);
  }
  checkIRservo3(IR2, door3, servo3close, door3Locked);
  checkIRservo2(IR2, door5, servo5close, door5Locked);
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

void checkIRservo(const int IRpin, Servo door, const int angle, bool &doorlocked){
  int nowIR = digitalRead(IRpin);
  if(!doorlocked){
    if(nowIR == LOW){
      doorlocked = true;
      door.write(angle);
      Serial.println("DOOR 2 -> OPEN");
    } 
  }
}

void checkIRservo2(const int IRpin, Servo door, const int angle, bool &doorlocked){
  int nowIR = digitalRead(IRpin);
  if(!doorlocked){
    if(nowIR == LOW){
      doorlocked = true;
      door.write(angle);
      Serial.println("DOOR 5 -> LOCKED");
      Serial.println("LIGHT -> RED");
    }
  }
}

void checkIRservo3(const int IRpin, Servo door, const int angle, bool &doorlocked){
  int nowIR = digitalRead(IRpin);
  if(!doorlocked){
    if(nowIR == LOW){
      doorlocked = true;
      door.write(angle);
      Serial.println("DOOR 3 -> CLOSED");
    } 
  }
}


void checkAutoservo2(const int IRpin, Servo door, unsigned long interval, const int openangle, const int closeangle, bool &doorclosed, bool &doorlocked, unsigned long &timer){
  int nowIR = digitalRead(IRpin);
  if(!doorlocked)
  {
    if(nowIR == LOW){
      Serial.println("Auto door locked");
      doorlocked = true;
      door.write(openangle);
    }
    if(millis() - timer >= interval){
      timer = millis();
      doorclosed = !doorclosed;
      if(doorclosed){
        Serial.println("Close");
        door.write(closeangle);
      } else {
        door.write(openangle);
        Serial.println("Open");
      }
    }
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