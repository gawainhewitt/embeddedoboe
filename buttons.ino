//this function manages 4-state buttons (pressed, held, released, off)
unsigned int scrollTime = 250;
long unsigned int heldTimer = 0;
long unsigned int menuTimer = 0;


const byte buttonPins[] = {0, 1, 2, 3, 4}; //UP, LEFT, CENTRE, RIGHT, DOWN
byte buttonStates[NUM_BUTTONS];

void buttonUpdate() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    boolean buttonState = digitalRead(buttonPins[i]);
    if (buttonStates[i] == 3) {
      buttonStates[i] = 2;
    }
    if ((buttonState == LOW) && (buttonStates[i] == 0)) {
      buttonStates[i] = 3;
      heldTimer = millis();
      menuTimer = millis();
      bigMenu = false;
    }
    if (buttonStates[i] == 1) {
      buttonStates[i] = 0;
    }
    if ((buttonState == HIGH) && (buttonStates[i] == 2)) {
      buttonStates[i] = 1;
    }
  }
  //0-off
  //3-momentary on
  //2-on
  //1-momentary off
}

void volumeUpdate(int knob) {
  // Serial.println((float)knob / 1023.0);
  float knobVolume = (float)knob / 1023.0;
  
  if ( knobChange(knobVolume, gain)){
    gain = knobVolume;
    amp1.gain(gain);
    updateDisplayFlag = true;
    bigMenu = false;
    heldTimer = millis();
    menuTimer = millis();
    bigMenu = false;
  }
}

bool knobChange(float knobVol, float gainTest){
  float sensitivity = 0.01;
  // Serial.print("knob volume ");
  // Serial.println(knobVol);
  // Serial.print("gain ");
  // Serial.println(gainTest);
  // Serial.print("gain + sensitivity ");
  // Serial.println(gainTest + sensitivity);
  if (knobVol > gainTest + sensitivity){
    Serial.println("greater");
    return true;
  } else if (knobVol < gainTest - sensitivity){
    Serial.println("lesser");
    return true;
  } else {
    return false;
  }
}

//this function acts upon button presses
void buttonActions() {
  if (buttonStates[UP] == 3) {
    Serial.print("up menu: ");
    Serial.println(activeMenuInput);
    Serial.print("buttonState ");
    Serial.println(buttonStates[0]);
    activeMenuInput--;
  }

  if (buttonStates[DOWN] == 3) {
    Serial.print("down menu: ");
    Serial.println(activeMenuInput);
    activeMenuInput++;
  }

  if (buttonStates[LEFT] == 3) {
    switch (activeMenuInput) {
      case 0:
        keyPosition = keyPosition - 1;
        if (keyPosition < 0) {
          keyPosition = 11;
        }
        keyName = noteNames[keyPosition];
        break;
      case 1:
      currentScale = currentScale - 1;
        if (currentScale < 0) {
          currentScale = numScales - 1;
        }
        changeScale(currentScale);
        // drawMenu();
        break;
      case 2:
      currentSound = currentSound - 1;
        if (currentSound < 0) {
          currentSound = numSounds - 1;
        }
        changeSound(currentSound);
        break;
      
    }
  }

  if (buttonStates[CENTRE] == 3) {
    switch (activeMenuInput) {
      case 0:
        Serial.print("centre menu: ");
        Serial.println(activeMenuInput);
        break;
      case 4:
        Serial.print("centre menu: ");
        Serial.println(activeMenuInput);
        break;
    }
  }

  if (buttonStates[RIGHT] == 3) {
    switch (activeMenuInput) {
      case 0:
      keyPosition = keyPosition + 1;
        if (keyPosition > 11) {
          keyPosition = 0;
        }
        keyName = noteNames[keyPosition];
        keyName = noteNames[keyPosition];
        break;
      case 1:
        currentScale = currentScale + 1;
        if (currentScale > numScales - 1) {
          currentScale = 0;
        }
        changeScale(currentScale);
        break;
      case 2:
      currentSound = currentSound + 1;
        if (currentSound > numSounds - 1) {
          currentSound = 0;
        }
        changeSound(currentSound);
        break;
    }
  }

  if (activeMenuInput < 0) {
    activeMenuInput = menuItems - 1; //menu looping
  } else if (activeMenuInput > (menuItems - 1)) {
    activeMenuInput = 0;
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
    if ((buttonStates[i] == 2) && ((millis() - heldTimer) > scrollTime)) { //if a button has been held for enough time
      buttonStates[i] = 0;
      updateDisplayFlag = true;
      //saveState();
      return;
    } else if (buttonStates[i] == 1) { //if a button has been released
      updateDisplayFlag = true;
      return;
    }
  }

  if ((millis() - menuTimer) > 10000 && bigMenu == false) {
    bigMenu = true;
    updateDisplayFlag = true;
  }
}
