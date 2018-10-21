// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Reads pressure
//
// PCB v0.3/v0.4

#include "programmable_air.h"

#define DEBUG 1

int atmospheric_pressure = 508; // should be around 508
int threshold = 4;

void setup() {
  initializePins();

  // Uncomment code below to read atmospheric_pressure instead of using default value
  // vent();
  // delay(2500);
  // atmospheric_pressure = readPressure(0, 10);
  // println("Atmospheric pressure: %d", atmospheric_pressure)
}

void loop() {
  int pressure = readPressure(0, 1);
  Serial.print(pressure);

  int pressure_diff = pressure - atmospheric_pressure;

  if (pressure_diff > threshold) {
    for (int i = 0; i < 3; i++) {
      neopixel.setPixelColor(i, neopixel.Color(pressure_diff, 0, pressure_diff));
    }
    neopixel.show();
  }
  else {
    for (int i = 0; i < 3; i++) {
      neopixel.setPixelColor(i, neopixel.Color(0, 0, 0));
    }
    neopixel.show();
  }

  delay(200);
}
