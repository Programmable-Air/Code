// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
// http://opensoftmachines.com/
//
// PCB v0.3/v0.4

#include "programmable_air.h"

#define DEBUG 1

int state = UN_KNOWN;

void setup() {
  initializePins();

  switchOnPump(1, 50);
  switchOnPump(2, 50);
}

void loop() {
  int pressure = readPressure();
  Serial.println(pressure);

  if (!digitalRead(btn1)) {
    blow(0);
  }
  else {
    if (!digitalRead(btn2)) {
      suck(0);
    }
    else {
      switch (state) {
        case UN_KNOWN:
          if (pressure > 514) {
            suck();
            state = DECREASING;
          }
          else {
            blow();
            state = INCREASING;
          }
          break;

        case INCREASING:
          if (pressure > 550) {
            suck();
            state = DECREASING;
          } else {
            blow();
            for (int i = 0; i < 10; i++) {
              pressure = readPressure();
              Serial.println(pressure);
              delay(200);
            }
          }
          break;

        case DECREASING:
          if (pressure < 450) {
            blow();
            state = INCREASING;
          } else {
            suck();
          }
          break;
      }
    }
  }
  for (int i = 0; i < 10; i++) {
    pressure = readPressure();
    Serial.println(pressure);
    delay(200);
  }
}
