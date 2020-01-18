// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Reads pressure
// Demo video: https://vimeo.com/268358944
//
// PCB v1.0

#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>

#define DEBUG 1

void setup() {
  initializePins();
}

void loop() {
  showPressure();

  delay(50);
}
