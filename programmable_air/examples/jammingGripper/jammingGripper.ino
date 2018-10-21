// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Jamming gripper
//
// PCB v0.3/v0.4

#include "programmable_air.h"

#define DEBUG 1

int state = UN_KNOWN;

void setup() {
  initializePins();

  // switch on pumps to 50% power
  switchOnPumps(50);
}

void loop() {
  Serial.println(readPressure());

  // If btn2 is pressed start sucking
  if (readBtn(2) && state != SUCKING) {
    suck();
    state = SUCKING;
  }
  // if btn1 is pressed, start blowing
  else if (readBtn(1) && state != BLOWING) {
    blow();
    state = BLOWING;
  }
  // if nither button is pressed, vent (but blow for a bit to let go of the object)
  else if(state != VENTING){
    blow();
    delay(250);
    vent();
    state = VENTING;
  }

  delay(200);
}
