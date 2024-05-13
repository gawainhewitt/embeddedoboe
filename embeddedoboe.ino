
/* A physical, touch sensitive oboe instrument. 

gawainhewitt.co.uk
https://github.com/gawainhewitt
*/

#include "constants.h"
#include "mpr121.h"
#include "reboot.h"
#include <bus1_U8g2lib.h>        // my bus1 adaptation of https://github.com/olikraus/u8g2/blob/master/cppsrc/U8g2lib.h - manages I2C display
#include "wavetable.h"

boolean updateDisplayFlag = true;

int activeMenuInput = 0;
byte menuItems = 2;
boolean bigMenu = false;
float gain = 0;

#define UP 0
#define LEFT 1
#define CENTRE 2
#define RIGHT 3
#define DOWN 4
#define NUM_BUTTONS 5


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
}

void loop() {

  buttonUpdate();  //updates buttons states
  buttonActions(); //carries out actions from button states
  
  int knob = analogRead(volumePin); // knob = 0 to 1023
  volumeUpdate(knob); 
  
  currtouched1 = mprBoard_A.touched();

  if(digitalRead(rebootButton) == LOW){
      Serial.print("reboot");
      doReboot();
  }

  for (uint8_t i=0; i < numberOfSensors; i++) {
      if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched of A");
      playSound(octave, i);
      }

      if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" released of A");
      stopSound(octave, i);
    }
  }

  lasttouched1 = currtouched1;

  if (updateDisplayFlag == true) {
      drawMenu();            //update the menu
      updateDisplayFlag = false;
  }

  return;

    // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(mprBoard_A.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(mprBoard_A.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(mprBoard_A.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}