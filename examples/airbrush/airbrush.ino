// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Airbrush
//
// NOTE: both motors used as high pressure pumps

#include "programmable_air.h"

#define DEBUG 1

int state = UN_KNOWN;

void setup() {
  initializePins();
  pinMode(A0, INPUT_PULLUP);
}

void loop() {
  if(!digitalRead(A0) || readBtn(RED)){
    switchOnPumps();
    setValve(2, OPEN);
    setValve(3, OPEN);
  } else{
    switchOffPumps();
    setValve(2, CLOSE);
    setValve(3, CLOSE);
  }
}