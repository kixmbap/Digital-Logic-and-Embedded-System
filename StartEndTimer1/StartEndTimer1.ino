const int swpin = 2;
const int IRpin = 3;
const int laserPin = 4;


// =========================
// Round Status
// =========================
bool startround = false;
bool endround = false;


// =========================
// Sensor Previous State
// =========================
int lastIR = LOW;
int lastLaser = HIGH;


// =========================
// Timer
// =========================
unsigned long startTime = 0;
unsigned long lastDisplayTime = 0;

const unsigned long displayInterval = 1000;


// =========================
// Setup
// =========================
void setup() {

  Serial.begin(9600);

  timerPinSetup();

  Serial.println("================================");
  Serial.println("      ROBOT TIMER READY");
  Serial.println("================================");
  Serial.println("IR    = START");
  Serial.println("SW    = END");
  Serial.println("Laser = END");
  Serial.println("================================");
}


// =========================
// Main Loop
// =========================
void loop() {

  // -------------------------
  // IR START
  // -------------------------
  checkIRstart(
    IRpin,
    lastIR,
    startTime,
    startround
  );


  // -------------------------
  // TIMER
  // -------------------------
  timerCount(
    startTime,
    lastDisplayTime,
    startround,
    endround
  );


  // -------------------------
  // SWITCH END
  // -------------------------
  checkSWEND(
    swpin,
    startTime,
    startround,
    endround
  );


  // -------------------------
  // LASER END
  // -------------------------
  checkLaserEND2(
    laserPin,
    lastLaser,
    startTime,
    startround,
    endround
  );
}


// =========================
// Pin Setup
// =========================
void timerPinSetup() {

  pinMode(swpin, INPUT_PULLUP);

  pinMode(IRpin, INPUT);

  pinMode(laserPin, INPUT);
}


// =========================
// Timer Count
// =========================
void timerCount(
  unsigned long &startTime,
  unsigned long &lastDisplayTime,
  bool &startround,
  bool &endround
) {

  if (startround && !endround) {

    unsigned long currentTime = millis();

    if (currentTime - lastDisplayTime >= displayInterval) {

      lastDisplayTime = currentTime;

      unsigned long elapsed =
        currentTime - startTime;

      printElapsedTime(elapsed);
    }
  }
}


// =========================
// Print Time
// =========================
void printElapsedTime(unsigned long elapsed) {

  unsigned long totalSeconds =
    elapsed / 1000;

  unsigned long mins =
    totalSeconds / 60;

  unsigned long secs =
    totalSeconds % 60;


  Serial.print("Time : ");


  // -------------------------
  // Less than 1 minute
  // 1
  // 2
  // 3
  // ...
  // 59
  // -------------------------
  if (mins == 0) {

    Serial.println(totalSeconds);

  }


  // -------------------------
  // 1 minute or more
  // 1:00
  // 1:01
  // 1:02
  // -------------------------
  else {

    Serial.print(mins);

    Serial.print(":");

    if (secs < 10) {
      Serial.print("0");
    }

    Serial.println(secs);
  }
}


// =========================
// IR START
// =========================
void checkIRstart(
  const int IRpin,
  int &lastIR,
  unsigned long &startTime,
  bool &startround
) {

  int nowIR = digitalRead(IRpin);


  // Detect LOW -> HIGH
  if (
    nowIR == HIGH &&
    lastIR == LOW &&
    !startround
  ) {

    startTime = millis();

    startround = true;

    lastDisplayTime = startTime;


    Serial.println();
    Serial.println("========== START ==========");

    Serial.print("Time start now. (");
    Serial.print(startTime);
    Serial.println(" ms)");

    Serial.println("============================");
  }


  lastIR = nowIR;
}


// =========================
// SWITCH END
// =========================
void checkSWEND(
  const int swPin,
  unsigned long startTime,
  bool &startround,
  bool &endround
) {

  if (
    startround &&
    !endround &&
    digitalRead(swPin) == LOW
  ) {

    endround = true;


    unsigned long elapsed =
      millis() - startTime;


    Serial.println();
    Serial.println("=========== END ===========");

    Serial.println("End by SWITCH");

    Serial.print("Time end. Using ");

    printElapsedTime(elapsed);


    Serial.print("Total milliseconds: ");
    Serial.println(elapsed);

    Serial.println("============================");
  }
}


// =========================
// LASER END
// LOW must stay 100 ms
// =========================
void checkLaserEND2(
  const int pin,
  int &lastLaser,
  unsigned long startTime,
  bool &startround,
  bool &endround
) {

  static unsigned long lowStart = 0;

  int nowLaser =
    digitalRead(pin);


  if (
    startround &&
    !endround
  ) {


    // -------------------------
    // Laser LOW
    // -------------------------
    if (nowLaser == LOW) {


      // First moment LOW
      if (lastLaser == HIGH) {

        lowStart = millis();

        Serial.println("Laser LOW detected");
      }


      // LOW continuously for 100 ms
      if (
        millis() - lowStart >= 100
      ) {

        endround = true;


        unsigned long elapsed =
          millis() - startTime;


        Serial.println();
        Serial.println("=========== END ===========");

        Serial.println("End by LASER");

        Serial.print("Time end. Using ");

        printElapsedTime(elapsed);


        Serial.print("Total milliseconds: ");
        Serial.println(elapsed);

        Serial.println("============================");
      }
    }


    // -------------------------
    // Laser HIGH
    // Reset LOW timer
    // -------------------------
    else {

      lowStart = 0;
    }
  }


  lastLaser = nowLaser;
}