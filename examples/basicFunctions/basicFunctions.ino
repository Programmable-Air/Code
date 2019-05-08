// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// PCB v0.3/v0.4/v0.5

#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, neopixelPin, NEO_GRB + NEO_KHZ800);

#define DEBUG 1

void setup() {
  initializePins();

  //neopixels
  pixels.begin();
  for (int i = 0; i < 3; i++) {
    // pixels.Color(red, green, blue)
    pixels.setPixelColor(i, pixels.Color(0, 100, 100));
  }
  pixels.show();

  // Pumps
  switchOnPump(1, 100);
  delay(500);
  switchOffPump(1);
  delay(500);
  switchOnPumps(50);
  delay(500);
  switchOffPumps();
  delay(500);

  // Valves
  blow();
  delay(500);
  suck();
  delay(500);
  vent();
  delay(500);
  ventQuick();
  delay(500);

  setValve(1, OPEN);
  delay(500);
  setValve(1, CLOSE);
  delay(500);

  setAllValves(OPEN);
  delay(500);
  closeAllValves();
  delay(500);
}

void loop() {
  int pressure = readPressure();
  Serial.println(pressure);
  
  delayWhilePrintingPressure(200);
}
