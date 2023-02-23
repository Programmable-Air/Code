// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Programmable-Air Serial Input
//
// PCB v0.3/v0.4/v0.5

#include "programmable_air.h"

#define DEBUG 1

void setup() {
  initializePins();
}

int timing;

void loop() {
  if (Serial.available()) {
    timing = Serial.parseInt(); // parseInt()

    switchOnPump(2);
//    switchOnLoad();
    blow();
    
    delay(timing);

    switchOffPumps();
//    switchOffLoad();
    vent();
  }
  delayWhileReadingPressure(200);
}
