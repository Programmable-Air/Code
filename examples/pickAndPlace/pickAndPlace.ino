// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Also works as an SMD pick and place!
// Demo video: https://vimeo.com/268358924
//
// PCB v0.3/v0.4/v0.5

#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, neopixelPin, NEO_GRB + NEO_KHZ800);

#define DEBUG 1

int state = UN_KNOWN;

int atmospheric_pressure = 508; // should be around 508
int threshold = 8;

int switch_ = 9;

void setup() {
  initializePins();
  pixels.begin();
  pixels.show();
  pinMode(switch_, INPUT_PULLUP);
}

void loop() {
  showPressure();

  // If blue button is pressed start sucking
  if ((readBtn(BLUE)||!digitalRead(switch_)) && state != SUCKING) {
    // switch on pumps to 50% power
    switchOnPump(1, 100);
    switchOffPump(2);
    suck();
    state = SUCKING;
  }
  // if red button is pressed, start blowing
  else if (readBtn(RED) && state != BLOWING) {
    // switch on pumps to 50% power
    switchOnPump(2, 100);
    switchOffPump(1);
    blow();
    state = BLOWING;
  }

  // if nither button is pressed, vent (but blow for a bit to let go of the object)
  else if (!readBtn(BLUE) && !readBtn(RED) && digitalRead(switch_) && state != VENTING) {
    switchOnPump(1, 100);
    blow();
    delayWhileReadingPressure(250);
    switchOffPumps();
    vent();
    state = VENTING;
  }

  delayWhileReadingPressure(200);
}

int showPressure(){
  int pressure = readPressure();
  Serial.println(pressure);

  int pressure_diff = pressure - atmospheric_pressure;

  if (pressure_diff > threshold) {
    setAllNeopixels(pixels.Color(pressure_diff/3, 0, pressure_diff/3));
  }
  if (pressure_diff < -threshold) {
    setAllNeopixels(pixels.Color(0, -pressure_diff/3, -pressure_diff/3));
  }
  if (abs(pressure_diff) < threshold) {
    setAllNeopixels(pixels.Color(0, 0, 0));
  }

  return pressure;
}

void delayWhileReadingPressure(unsigned long del){
  unsigned long startTime = millis();
  while(millis() - startTime < del){
    showPressure();
    delay(20);
  }
}

void setAllNeopixels(uint32_t c){
    for (int i = 0; i < 3; i++) {
      pixels.setPixelColor(i, c);
    }
    pixels.show();
}
