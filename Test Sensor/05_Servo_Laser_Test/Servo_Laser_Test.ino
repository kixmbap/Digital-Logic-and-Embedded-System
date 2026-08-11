#include <Servo.h>

Servo door;

const int SERVO_PIN = 3;

const int LASER_TX_PIN = 9;
const int LASER_RX_PIN = 10;

const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE = 90;

bool laserDetected = false;
bool doorLocked = false;

void setup() {

  Serial.begin(9600);

  pinMode(LASER_TX_PIN, OUTPUT);
  pinMode(LASER_RX_PIN, INPUT);

  // เปิด Laser
  digitalWrite(LASER_TX_PIN, HIGH);

  door.attach(SERVO_PIN);

  // เริ่มต้นประตูปิด
  door.write(CLOSED_ANGLE);

  Serial.println("=== SERVO + LASER TEST ===");
  Serial.println("Door CLOSED");
  Serial.println("System Ready");
}

void loop() {

  int laserState = digitalRead(LASER_RX_PIN);

  // Laser ตรวจพบ
  if (laserState == HIGH &&
      !laserDetected &&
      !doorLocked) {

    laserDetected = true;

    Serial.println("LASER DETECTED");
    Serial.println("DOOR OPEN");

    door.write(OPEN_ANGLE);
  }

  // Laser ขาดการตรวจจับ
  if (laserDetected &&
      laserState == LOW &&
      !doorLocked) {

    Serial.println("LASER LOST");
    Serial.println("DOOR CLOSED");
    Serial.println("DOOR LOCKED");

    door.write(CLOSED_ANGLE);

    doorLocked = true;
  }

  // Lock แล้วให้ปิดค้าง
  if (doorLocked) {

    door.write(CLOSED_ANGLE);
  }

  delay(50);
}
