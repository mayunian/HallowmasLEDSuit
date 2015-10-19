
#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            2

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int LEDsPin[] = {13, 12, 11, 10, 9, 8, 7, 6, 5};
int switchPin = 4;
int switchState = 0;
int pervSwitchState = 0;
long interval = 120000;
unsigned long previousTime = 0;
int numOfLED = 9;
int handRingColorR[] = {150, 0, 0, 150};
int handRingColorG[] = {0, 150, 0, 150};
int handRingColorB[] = {0, 0, 150, 150};
int maxColors = 4;
int currentColor = 0;

void setup() {
    int i = 0;
    for(i = 0; i <= 13; i++ ){
        pinMode(LEDsPin[i], OUTPUT);               
    };
    pinMode(switchPin, INPUT);
    previousTime = millis();
    pixels.begin();
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
  if (switchState != pervSwitchState){
      pervSwitchState = switchState;
      // Initalizes hand ring color.
      if (currentColor == maxColors){
          currentColor = 0;
      }
      for(int i = 0; i < NUMPIXELS; i++){
          // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(handRingColorR[currentColor], handRingColorG[currentColor], handRingColorB[currentColor])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(150); // Delay for a period of time (in milliseconds).
      }
      currentColor++;
  } 
  switchState = digitalRead(switchPin);
}

void turnOffLED(){
    int i = 0;
    for(i = 0; i < numOfLED; i++){
        analogWrite(LEDsPin[i], 1023);
    };
}

void turnOnLED(int delayTime){
    int i = 0;
    for(i = 0; i < numOfLED; i++){
        analogWrite(LEDsPin[i], 0);
        if (i == numOfLED - 1){
          delay(500);
        }
        else{        
          delay(delayTime);
        }
    };
}
