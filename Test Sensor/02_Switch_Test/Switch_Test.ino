const int SWITCH_PIN = 7;

void setup() {

  Serial.begin(9600);

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  Serial.println("=== SWITCH TEST ===");
  Serial.println("System Ready");
}

void loop() {

  int switchState = digitalRead(SWITCH_PIN);

  if (switchState == LOW) {

    Serial.println("SWITCH PRESSED");

  } else {

    Serial.println("SWITCH RELEASED");
  }

  delay(300);
}
