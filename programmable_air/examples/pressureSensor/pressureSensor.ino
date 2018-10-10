// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// PCB v0.3/v0.4

#include "programmable_air.h"

#define DEBUG 1

int atmospheric_pressure = 508;
int threshold = 4;

void setup() {
  initializePins();
  vent();
}

void loop() {
  int pressure = readPressure();
  Serial.print(pressure);

  int pressure_diff = pressure - atmospheric_pressure;

  if (pressure_diff > threshold) {
    for (int i = 0; i < 3; i++) {
      neopixel.setPixelColor(i, neopixel.Color(pressure_diff * 3, 0, pressure_diff * 3));
    }
    neopixel.show();
  }
  else {
    for (int i = 0; i < 3; i++) {
      neopixel.setPixelColor(i, neopixel.Color(0, 0, 0));
    }
    neopixel.show();
  }

  delay(50);
}
