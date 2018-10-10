// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// PCB v0.3/v0.4

#include "programmable_air.h"

#define DEBUG 1

int state = UN_KNOWN;

void setup() {
  initializePins();
  switchOnPump(1, 75);
  switchOnPump(2, 50);
}

void loop() {
  if (!digitalRead(btn2) && state != SUCKING) {
    suck();
    state = SUCKING;
  }
  else if (!digitalRead(btn1) && state != BLOWING) {
    blow();
    state = BLOWING;
  }
  else if(digitalRead(btn2) && state != VENTING){
    blow();
    delay(250);
    vent();
    state = VENTING;
  }
  Serial.println(readPressure());
  delay(100);
}
