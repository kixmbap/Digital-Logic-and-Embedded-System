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
int pinnum = 0;

const int servo1close = 90;
const int servo1open = 160;

const int servo2close = 17;
const int servo2open = 100;

const int servo3close = 90;
const int servo3open = 170;

const int servo4close = 105;
const int servo4open = 20;

const int servo5close = 90;
const int servo5open = 0;

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
  while(Serial.available() == 0){
  }
  pinnum = Serial.parseInt();

  switch(pinnum){
    case 1:
    setServo(servo1, servo1open);
    setServo(servo2, servo2open);
    setServo(servo3, servo3open);
    setServo(servo4, servo4open);
    setServo(servo5, servo5open);
    break;
    case 2:
    setServo(servo1, servo1close);
    setServo(servo2, servo2close);
    setServo(servo3, servo3close);
    setServo(servo4, servo4close);
    setServo(servo5, servo5close);
    break;
  }
}

void setServo(Servo &servo, int angle){
  servo.write(angle);
  state = 0;
}
