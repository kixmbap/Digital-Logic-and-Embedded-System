const int LASER_TX_1 = 9;
const int LASER_RX_1 = 10;

const int LASER_TX_2 = 11;
const int LASER_RX_2 = 12;

void setup() {

  Serial.begin(9600);

  // Laser 1
  pinMode(LASER_TX_1, OUTPUT);
  pinMode(LASER_RX_1, INPUT);

  // Laser 2
  pinMode(LASER_TX_2, OUTPUT);
  pinMode(LASER_RX_2, INPUT);

  // เปิด Laser ทั้งสองตัว
  digitalWrite(LASER_TX_1, HIGH);
  digitalWrite(LASER_TX_2, HIGH);

  Serial.println("=== DUAL LASER TEST ===");
  Serial.println("Laser 1 : TX D9 / RX D10");
  Serial.println("Laser 2 : TX D11 / RX D12");
  Serial.println("System Ready");
}

void loop() {

  int laser1 = digitalRead(LASER_RX_1);
  int laser2 = digitalRead(LASER_RX_2);

  // Laser 1
  Serial.print("Laser 1 = ");
  Serial.print(laser1);

  if (laser1 == HIGH) {
    Serial.print(" DETECTED");
  } else {
    Serial.print(" LOST");
  }

  // Laser 2
  Serial.print("    |    Laser 2 = ");
  Serial.print(laser2);

  if (laser2 == HIGH) {
    Serial.println(" DETECTED");
  } else {
    Serial.println(" LOST");
  }

  delay(500);
}
