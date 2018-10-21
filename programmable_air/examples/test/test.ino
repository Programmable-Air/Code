// Programmable Air
// Author: tinkrmind
// github.com/tinkrmind/programmable-air
//
// Pressing btn1 will switch on pumps and squentially switch on all valves
// Pressing btn2 will vent
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

  if (readBtn(1)) {
    //switch on pumps
    switchOnPumps();

    blow();
    delay(500);
    vent();
    delay(500);
    suck();
    delay(500);
  }
  else if (readBtn(2)) {
    //switch off pumps
    switchOffPumps();

    vent();
  }
  else {
    //switch off pumps
    switchOffPumps();

    setAllValves(CLOSED);
  }

  delay(200);
}
