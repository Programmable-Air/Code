// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
// http://opensoftmachines.com/
//
// Cycles through pressure
// Demo video: https://vimeo.com/291361549
//
// PCB v0.3/v0.4/v0.5

#include "programmable_air.h"

#define DEBUG 1

int state = UN_KNOWN;

int atmospheric_pressure = 508;
int upper_threshold = 10;
int lower_threshold = -10;

void setup() {
  initializePins();

  // Uncomment code below to read atmospheric_pressure instead of using default value
  // vent();
  // delay(2500);
  // atmospheric_pressure = readPressure(0, 10);
  // println("Atmospheric pressure: %d", atmospheric_pressure)

  // switch on pumps to 50% power
  switchOnPumps(50);
}

void loop() {
  int pressure = readPressure();
  int pressure_diff = pressure - atmospheric_pressure;
  Serial.println(pressure_diff);

  if (readBtn(RED)) {
    blow();
  }
  else if (readBtn(BLUE)) {
    suck();
  }
  else {
    switch (state) {
      // if we don't know the state blow until the pressure reaches atmospheric_pressure
      case UN_KNOWN:
        if (pressure_diff > 0) {
          suck();
          state = DECREASING;
        }
        else {
          blow();
          state = INCREASING;
        }
        break;

      // we are blowing up the robot. Start sucking after pressure reaches upper_threshold
      case INCREASING:
        if (pressure_diff > upper_threshold) {
          suck();
          state = DECREASING;
        } else {
          blow();
        }
        break;

      // we are deflating the robot. Start blowing after pressure reaches lower_threshold
      case DECREASING:
        if (pressure_diff < lower_threshold) {
          blow();
          state = INCREASING;
        } else {
          suck();
        }
        break;
    }
  }

  delay(200);
}
