// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Jamming gripper
// Demo video: https://vimeo.com/268358891
// Also works as an SMD pick and place!
// Demo video: https://vimeo.com/268358924
//
// PCB v1.0

#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>

#define DEBUG 1

int state = UN_KNOWN;

int atmospheric_pressure = 508; // should be around 508
int threshold = 8;

void setup() {
  initializePins();
}

void loop() {
  showPressure();

  // If blue button is pressed start sucking
  if (readBtn(BLUE) && state != SUCKING) {
    // switch on pumps to 50% power
    switchOnPump(1, 100);
    switchOffPump(2);
    suck();
    state = SUCKING;
  }
  // if red button is pressed, start blowing
  else if (readBtn(RED) && state != BLOWING) {
    // switch on pumps to 50% power
    switchOnPump(2, 100);
    switchOffPump(1);
    blow();
    state = BLOWING;
  }

  // if nither button is pressed, vent (but blow for a bit to let go of the object)
  else if (!readBtn(BLUE) && !readBtn(RED) && state != VENTING) {
    switchOnPump(1, 100);
    blow();
    delayWhileReadingPressure(250);
    switchOffPumps();
    vent();
    state = VENTING;
  }

  delayWhileReadingPressure(200);
}