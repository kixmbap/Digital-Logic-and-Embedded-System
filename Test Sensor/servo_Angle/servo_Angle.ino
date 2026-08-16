#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

const int SERVO1_PIN = 2;
const int SERVO2_PIN = 3;
const int SERVO3_PIN = 4;
const int SERVO4_PIN = 5;
const int SERVO5_PIN = 6;

int state = 0;
int angle = 0;
int pinnum = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);
  servo5.attach(SERVO5_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Input Servo pin : ");
  while(Serial.available() == 0){
  }
  pinnum = Serial.parseInt();
  Serial.print("Servo number : ");
  Serial.println(pinnum);

  while(Serial.available() == 0){
  }
  angle = Serial.parseInt();
  Serial.print("ANGLE : ");
  Serial.println(angle);
  switch(pinnum){
    case 1:
    setServo(servo1, angle);
    break;
    case 2:
    setServo(servo2, angle);
    break;
    case 3:
    setServo(servo3, angle);
    break;
    case 4:
    setServo(servo4, angle);
    break;
    case 5:
    setServo(servo5, angle);
    break;
  }
}

void setServo(Servo &servo, int angle){
  servo.write(angle);
  state = 0;
}
