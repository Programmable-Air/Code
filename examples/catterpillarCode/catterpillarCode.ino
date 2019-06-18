// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Crawling catterpillar
// Needs two added valve extension boards
//
// PCB v0.3/v0.4/v0.5

#include "programmable_air.h"

#define DEBUG 1

int state = UN_KNOWN;

int atmospheric_pressure[3] = {520, 520, 512};
int upper_threshold = 35;
int lower_threshold = -10;

void setup() {
  initializePins();

  vent(1);
  vent(2);
  vent(3);
  for (int i = 1; i <= 3; i++) {
    readPressure(i, 20);
  }
  delay(200);
  for (int i = 1; i <= 3; i++) {
    atmospheric_pressure[i - 1] = readPressure(i, 10);
  }
  closeAllValves();
}

void loop() {
  if (readBtn(RED)) {
    switchOnPumps(80);
    for (int j = 0; j <= 10; j++) {
      for (int i = 3; i >= 1; i--) {
        blowSection(i);
      }
      for (int i = 3; i >= 1; i--) {
        ventSection(i);
      }
    }
    switchOffPumps();
  }
  if (readBtn(BLUE)) {
    ventSection(4);
  }
}

void blowSection(int i) {
//  int pressure = readPressure(i);
//  int pressure_diff = pressure - atmospheric_pressure[i - 1];
//  while (pressure_diff < upper_threshold) {
//    pressure = readPressure(i);
//    pressure_diff = pressure - atmospheric_pressure[i - 1];
//    Serial.println(pressure_diff);
//    blow(i);
//    delay(200);
//  }
  blow(i);
  delay(3000);
  closeAllValves();
}

void ventSection(int i) {
  if (i >= 1 && i <= 3) {
    vent(i);
    delay(500);
    closeAllValves();
  }
  if (i == 4) {
    vent(1);
    vent(2);
    vent(3);
    while (!readBtn(BLUE)) {
      delay(10);
    }
    closeAllValves();
  }
}
