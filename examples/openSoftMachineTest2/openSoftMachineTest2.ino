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

int atmospheric_pressure = 512;
int upper_threshold = 50;
int lower_threshold = -10;

void setup() {
  initializePins();

  // Uncomment code below to read atmospheric_pressure instead of using default value
  // vent();
  // delay(2500);
  // atmospheric_pressure = readPressure(0, 10);
  // println("Atmospheric pressure: %d", atmospheric_pressure)
}

void loop() {
  if (readBtn(RED)) {
    contract();
  }
  else if (readBtn(BLUE)) {
    expand();
  }
  else {
    closeAllValves();
    switchOffPumps();
  }
  delayWhileReadingPressure(50);
}

void contract() {
  int pressure_diff = readPressure() - atmospheric_pressure;
  if(pressure_diff < upper_threshold) {
    switchOnPump(2);
    blow();
    delayWhileReadingPressure(250);
  }  
  else{
    closeAllValves();
    switchOffPumps();
  }
}

void expand() {
  switchOnPump(1);
  suck();
}