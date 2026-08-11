#include <Servo.h>

Servo door;

const int SERVO_PIN = 2;
const int SWITCH_PIN = 7;

const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE = 90;

bool doorOpened = false;

void setup() {

  Serial.begin(9600);

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  door.attach(SERVO_PIN);

  // เริ่มต้นประตูปิด
  door.write(CLOSED_ANGLE);

  Serial.println("=== SERVO + SWITCH TEST ===");
  Serial.println("Door CLOSED");
  Serial.println("System Ready");
}

void loop() {

  int switchState = digitalRead(SWITCH_PIN);

  // กด Switch ครั้งแรก
  if (switchState == LOW && !doorOpened) {

    Serial.println("SWITCH PRESSED");
    Serial.println("DOOR OPEN");

    door.write(OPEN_ANGLE);

    doorOpened = true;

    delay(300);
  }

  // เมื่อเปิดแล้วให้เปิดค้าง
  if (doorOpened) {

    door.write(OPEN_ANGLE);
  }
}
