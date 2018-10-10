// Programmable Air
// Author: tinkrmind
// github.com/tinkrmind/programmable-air
//
// Switch on all valves one by one quickly, indefinitely
//
// PCB v0.3/v0.4
//

#include "programmable_air.h"

#define DEBUG 1

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initiate with all valve and pumps off
  initializePins();
}

void loop() {
  Serial.println(readPressure());
  if (!digitalRead(btn[0])) {
    //switch on pumps
    switchOnPumps();

    suck();
    delay(1000);
    vent();
    delay(1000);
    blow();
    delay(1000);
  }
  else {
    //switch off pumps
    switchOffPumps();

    setAllValves(0);
    delay(100);
  }
}
