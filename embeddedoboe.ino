/* A physical, touch sensitive oboe instrument. 

gawainhewitt.co.uk
https://github.com/gawainhewitt
*/

#include "constants.h"
#include "touch.h"
#include "reboot.h"
#include <bus1_U8g2lib.h>        // my bus1 adaptation of https://github.com/olikraus/u8g2/blob/master/cppsrc/U8g2lib.h - manages I2C display
#include "wavetable.h"

boolean updateDisplayFlag = true;

int activeMenuInput = 0;
byte menuItems = 3;
boolean bigMenu = false;
float gain = 0;

#define UP 0
#define LEFT 1
#define CENTRE 2
#define RIGHT 3
#define DOWN 4
#define NUM_BUTTONS 5

// Sound management variables
unsigned long soundStopDelay = 50; // milliseconds - you can change this value
unsigned long lastTouchTime = 0;
unsigned long lastReleaseTime = 0;
bool touchedState[12]; // track current state of each electrode
bool pendingStopAll = false;

U8G2_SSD1306_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   //page buffer = 128bytes (_1_ = 128, _2_ = 256, _F_ = 1024)


void setup() {
    Serial.begin(9600);
    init_mpr121();
    setupPins();
    u8g2.begin();
    drawMenu();
    pinMode(rebootButton, INPUT_PULLUP);
    pinMode(volumePin, INPUT);

    setupAudio();
    
    // Initialize touch state array
    for (int i = 0; i < 12; i++) {
        touchedState[i] = false;
    }
}

void loop() {

  buttonUpdate();  //updates buttons states
  buttonActions(); //carries out actions from button states
  
  int knob = analogRead(volumePin); // knob = 0 to 1023
  volumeUpdate(knob); 

  if(digitalRead(rebootButton) == LOW){
      Serial.print("reboot");
      doReboot();
  }

  MPR121.updateAll();
  
  // Track current touch state
  bool currentlyTouched = false;

  for (int i = 0; i < 12; i++) {
    if (MPR121.isNewTouch(i)) {
      Serial.print("electrode ");
      Serial.print(i, DEC);
      Serial.println(" was just touched");
      playSound(octave, i);
      
      touchedState[i] = true;
      currentlyTouched = true;
      lastTouchTime = millis();
      pendingStopAll = false; // Cancel any pending stop

    } else if (MPR121.isNewRelease(i)) {
      Serial.print("electrode ");
      Serial.print(i, DEC);
      Serial.println(" was just released");
      
      touchedState[i] = false;
    }
    
    // Check if any electrode is still touched
    if (touchedState[i]) {
      currentlyTouched = true;
    }
  }
  
  // If no electrodes are touched and we haven't already scheduled a stop
  if (!currentlyTouched && !pendingStopAll) {
    lastReleaseTime = millis();
    pendingStopAll = true;
  }
  
  // Check if we should stop all sounds after delay
  if (pendingStopAll && !currentlyTouched && (millis() - lastReleaseTime >= soundStopDelay)) {
    // Stop all sounds
    for (int i = 0; i < 12; i++) {
      stopSound(octave, i);
    }
    pendingStopAll = false;
    Serial.println("All sounds stopped after delay");
  }

  if (updateDisplayFlag == true) {
      drawMenu();            //update the menu
      updateDisplayFlag = false;
  }

  return;

  //   // debugging info, what
  // Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(mprBoard_D.touched(), HEX);
  // Serial.print("Filt: ");
  // for (uint8_t i=0; i<12; i++) {
  //   Serial.print(mprBoard_D.filteredData(i)); Serial.print("\t");
  // }
  // Serial.println();
  // Serial.print("Base: ");
  // for (uint8_t i=0; i<12; i++) {
  //   Serial.print(mprBoard_D.baselineData(i)); Serial.print("\t");
  // }
  // Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}


