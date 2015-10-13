int LEDsPin[] = {13, 12, 11, 10, 9, 8, 7, 6, 5};
int switchPin = 4;
int switchState = 0;
int pervSwitchState = 0;
long interval = 120000;
unsigned long previousTime = 0;

void setup() {
    int i = 0;
    for(i = 0; i <= 13; i++ ){
        pinMode(LEDsPin[i], OUTPUT);               
    };
    pinMode(switchPin, INPUT);
    previousTime = millis();
}

// the loop function runs over and over again forever
void loop() {
  unsigned long currentTime = millis();
  if (switchState != pervSwitchState || currentTime - previousTime > interval){
        pervSwitchState = switchState;
        previousTime = currentTime;
        turnOffLED();
        turnOnLED(400);
        turnOffLED();
        turnOnLED(300);
        turnOffLED();
        turnOnLED(150);
        turnOffLED();
        turnOnLED(50);
    }
    switchState = digitalRead(switchPin);
}

void turnOffLED(){
    int i = 0;
    for(i = 0; i <= 13; i++){
        analogWrite(LEDsPin[i], 1023);
    };
}

void turnOnLED(int delayTime){
    int i = 0;
    for(i = 0; i <= 13; i++){
        analogWrite(LEDsPin[i], 0);
        if (i == 13){
          delay(500);
        }
        else{        
          delay(delayTime);
        }
    };
}
