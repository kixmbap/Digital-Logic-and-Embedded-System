const int LASER_TX_PIN = 9;
const int LASER_RX_PIN = 10;

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

  int receiverValue = digitalRead(LASER_RX_PIN);

  Serial.print("RX VALUE = ");
  Serial.print(receiverValue);

  if (receiverValue == HIGH) {

    Serial.println(" -> LASER DETECTED");

  } else {

    Serial.println(" -> LASER LOST");
  }

  delay(500);
}
