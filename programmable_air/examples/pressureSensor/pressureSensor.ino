// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Reads pressure
// Demo video: https://vimeo.com/268358944
//
// PCB v0.3/v0.4

#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, neopixelPin, NEO_GRB + NEO_KHZ800);

#define DEBUG 1

int atmospheric_pressure = 508; // should be around 508
int threshold = 4;

void setup() {
  initializePins();

  pixels.begin();
  pixels.show();

  // Uncomment code below to read atmospheric_pressure instead of using default value
  // vent();
  // delay(2500);
  // atmospheric_pressure = readPressure(0, 10);
  // println("Atmospheric pressure: %d", atmospheric_pressure)
}

void loop() {
  int pressure = readPressure();
  Serial.println(pressure);

  int pressure_diff = pressure - atmospheric_pressure;

  if (pressure_diff > threshold) {
    setAllNeopixels(pixels.Color(pressure_diff, 0, pressure_diff));
  }
  else {
    setAllNeopixels(pixels.Color(0, 0, 0));
  }

  delay(50);
}

void setAllNeopixels(uint32_t c){
    for (int i = 0; i < 3; i++) {
      pixels.setPixelColor(i, c);
    }
    pixels.show();
}
