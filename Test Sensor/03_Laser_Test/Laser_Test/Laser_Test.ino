const int LASER_TX_PIN = 10;
const int LASER_RX_PIN = 12;

void setup() {

  Serial.begin(9600);

  pinMode(LASER_TX_PIN, OUTPUT);
  pinMode(LASER_RX_PIN, INPUT);

  // เปิด Laser
  digitalWrite(LASER_TX_PIN, HIGH);

  Serial.println("=== LASER TEST ===");
  Serial.println("Laser TX : D9");
  Serial.println("Laser RX : D10");
  Serial.println("System Ready");
}

void loop() {
  testLaser(LASER_RX_PIN);
}

void testLaser(int pin){
  int receiverValue = digitalRead(pin);
  Serial.print("RX PIN ");
  Serial.print(pin);
  Serial.print(receiverValue);

  if (receiverValue == LOW) {

    Serial.println(" -> LASER DETECTED");

  } else {

    Serial.println(" -> LASER LOST");
  }

  delay(500);
}
