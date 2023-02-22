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

void loop() {
  if (Serial.available()) {
    String data = Serial.readString();
    if (data.substring(0,4) == "blow") {
      switchOffPumps();
      switchOnPump(2);
      blow();
    }
    if (data.substring(0,4) == "suck") {
      switchOffPumps();
      switchOnPump(1);
      suck();
    }
    if (data.substring(0,4) == "vent") {
      switchOffPumps();
      vent();
    }
  }
  delayWhileReadingPressure(200);
}
