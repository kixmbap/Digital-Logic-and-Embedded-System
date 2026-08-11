#include <Servo.h>

Servo myServo;

const int SERVO_PIN = 2;

const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE = 90;

void setup() {
  Serial.begin(9600);

  myServo.attach(SERVO_PIN);

  // เริ่มต้นที่ตำแหน่งปิด
  myServo.write(CLOSED_ANGLE);

  Serial.println("=== SERVO TEST ===");
  Serial.println("Door CLOSED");

  delay(2000);
}

void loop() {

  Serial.println("Door OPEN");
  myServo.write(OPEN_ANGLE);

  delay(2000);

  Serial.println("Door CLOSED");
  myServo.write(CLOSED_ANGLE);

  delay(2000);
}
