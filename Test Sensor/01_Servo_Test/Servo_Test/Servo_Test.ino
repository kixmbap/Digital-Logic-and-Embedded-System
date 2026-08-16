#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

// กำหนดขา Servo
const int SERVO1_PIN = 2;
const int SERVO2_PIN = 3;
const int SERVO3_PIN = 4;
const int SERVO4_PIN = 5;
const int SERVO5_PIN = 6;

// มุม Servo
const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE = 90;

void setup() {

  Serial.begin(9600);

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);
  servo5.attach(SERVO5_PIN);

  // เริ่มต้นให้ทุกประตูปิด
  servo1.write(CLOSED_ANGLE);
  
  servo2.write(CLOSED_ANGLE);
  servo3.write(CLOSED_ANGLE);
  servo4.write(CLOSED_ANGLE);
  servo5.write(CLOSED_ANGLE);

  delay(1000);

  Serial.println("==============================");
  Serial.println("   SERVO LOOP TEST START");
  Serial.println("==============================");

  setServo(servo1, 1, CLOSED_ANGLE);
}

void testServo(Servo &servo, int number) {

  Serial.print("DOOR ");
  Serial.print(number);
  Serial.println(" -> OPEN");

  servo.write(OPEN_ANGLE);

  delay(1000);

  Serial.print("DOOR ");
  Serial.print(number);
  Serial.println(" -> CLOSED");

  servo.write(CLOSED_ANGLE);

  delay(500);
}

void setServo(Servo &servo, int number, int angle){

  Serial.print("DOOR ");
  Serial.print(number);
  Serial.println(" -> OPEN");

  servo.write(OPEN_ANGLE);

  servo.write(angle);
}

void loop() {


  // Servo 1
 testServo(servo1, 1);
/*
  // Servo 2
  testServo(servo2, 2);

  // Servo 3
  testServo(servo3, 3);

  // Servo 4
  testServo(servo4, 4);

  // Servo 5
  testServo(servo5, 5);
*/
  Serial.println("==============================");
  Serial.println("ALL SERVO TEST COMPLETE");
  Serial.println("==============================");

  delay(1000);
  
}