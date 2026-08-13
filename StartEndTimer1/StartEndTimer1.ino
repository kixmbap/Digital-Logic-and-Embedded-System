
const int swpin = 2;
const int IRpin = 3;

bool startround = false;
int lastIR = 0;
bool endround = false;

unsigned long runtimer = 0;
unsigned long interval = 1000;
unsigned long totalTime = 60;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  timerPinSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  timerCount(runtimer, interval, totalTime, startround, endround);
  checkIRstart(IRpin, lastIR, runtimer, startround);
  checkSWEND(swpin, runtimer, startround, endround);
}


void timerPinSetup(){
  pinMode(swpin, INPUT_PULLUP);
  pinMode(IRpin, INPUT);
}

void timerCount(unsigned long &timer, unsigned long interval, unsigned long &totalTime, bool startround, bool endround){
  if(millis() - timer >= interval && startround && !endround){
    timer = millis();
    totalTime += interval/1000;
    unsigned long mins, secs = convertTime(totalTime);
    Serial.print(totalTime);
    Serial.print(" ");
    Serial.print(mins);
    Serial.print(" ");
    Serial.print(secs);
    Serial.print(" Time : ");
    printTime(mins, secs);
    Serial.println(" Sec.");
  }
}

unsigned long convertTime(unsigned long totalTime){
  unsigned long mins = (totalTime) / 60;
  unsigned long secs = (totalTime) % 60;
  Serial.println(mins);
  if(mins < 1){
    mins = 0;
    secs = totalTime;
  }
  return mins, secs;
}

void printTime(unsigned long mins, unsigned long secs){
  if(mins >= 1){
    Serial.print(mins);
    Serial.print(":");
    Serial.println(secs);
  } else {
    Serial.print(secs);
  }
}

void checkIRstart(const int IRpin, int &lastIR, unsigned long &timer, bool &startround){
  int nowIR = digitalRead(IRpin);
  if(nowIR == 1){
    if(lastIR == 0 && !startround){
      timer = millis();
      Serial.print("Time start now. (");
      Serial.print(timer);
      Serial.println(")");
      startround = true;
    }
  } else {
    lastIR = nowIR;
  }
}

void checkSWEND(const int swPin, unsigned long totaltime, bool &startround, bool &endround){
  if(startround && digitalRead(swPin) == 0 && !endround){
    endround = true;
        Serial.print("Time end. using ");
        unsigned long mins, secs = convertTime(totaltime);
        printTime(mins, secs);
        Serial.print(" seconds (");
        Serial.print(millis());
        Serial.println(")");  
  }
}

void checkLaserEND(const int laserRVpin, int &lastLaser, unsigned long timer, bool &startround, bool &endround){
  int nowLaser = digitalRead(laserRVpin);
  static unsigned long lowStart = 0;
  if(startround && !endround){
    Serial.println(nowLaser);
  }
  //Serial.println(nowLaser);
  if(nowLaser == LOW && startround && !endround){
        lowStart = millis();
        endround = true;
        int time = millis() - timer;
        Serial.print("Time end. using ");
        Serial.print(time);
        Serial.print(" seconds (");
        Serial.print(timer);
        Serial.println(")");  
  } else {
      lastLaser = nowLaser;
    }
}

void checkLaserEND2(const int pin, int &lastLaser,
                   unsigned long timer, bool &startround,
                   bool &endround) {
    static unsigned long lowStart = 0;
    int nowLaser = digitalRead(pin);
    //Serial.println(nowLaser);
    if (startround && !endround) {
        Serial.println(nowLaser);
        if (nowLaser == LOW) {
            // Start timing how long it has been LOW
            if (lastLaser == HIGH) {
                lowStart = millis();
            }
            // Only accept it as a hit if LOW is stable
            if (millis() - lowStart >= 100) {
                endround = true;
                unsigned long elapsed = millis() - timer;
                Serial.print("Time end. Using ");
                Serial.print(elapsed);
                Serial.println(" ms");
            } else {
              lowStart = 0;
            }
        }
    }

    lastLaser = nowLaser;
}
