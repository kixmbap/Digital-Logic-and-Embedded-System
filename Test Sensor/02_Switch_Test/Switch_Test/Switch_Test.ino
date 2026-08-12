
//ขา
const int switchpin = 2;

bool switch1 = false;
bool door1 = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchpin, INPUT_PULLUP);
  Serial.println("Start!");
}

void loop() {
  // put your main code here, to run repeatedly:
  testSwitch(switchpin, switch1);
}

void testSwitch(int pin, bool &doorstate){
  //true state, switch is pressed 
  if(digitalRead(pin) == 0 & !doorstate){
    //sevo open
    doorstate = true;
    Serial.println("true");
    while (digitalRead(pin) == 0){
      delay(100);
    }
    doorstate = false;
  }
}