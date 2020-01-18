// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Origami gripper auto trigger
//
// PCB v0.3/v0.4/v0.5

#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>

#define DEBUG 1

int state = UN_KNOWN;

int atmospheric_pressure = 504; // should be around 500
int threshold = 3;

void setup() {
  initializePins();
}

void loop() {
  showPressure();

  if (readPressure() >= (atmospheric_pressure + threshold)) {
    switchOnPump(1, 100);
    switchOffPump(2);
    suck();
    state = SUCKING;
    delayWhileReadingPressure(3500);
  }

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
    switchOnPump(2, 100);
    blow();
    delayWhileReadingPressure(1200);
    switchOffPumps();
    closeAllValves();
    state = VENTING;
  }

  delayWhileReadingPressure(200);
}
