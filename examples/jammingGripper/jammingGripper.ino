// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Jamming gripper
// Demo video: https://vimeo.com/268358891
// Also works as an SMD pick and place!
// Demo video: https://vimeo.com/268358924
//
// PCB v0.3/v0.4/v0.5

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

  // If blue button is pressed start sucking
  if (readBtn(BLUE) && state != SUCKING) {
    suck();
    state = SUCKING;
  }
  // if red button is pressed, start blowing
  else if (readBtn(RED) && state != BLOWING) {
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
