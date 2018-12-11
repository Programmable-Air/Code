// Programmable Air
// Author: tinkrmind
// github.com/tinkrmind/programmable-air
//
// Pressing red button will switch on pumps and squentially switch on all valves
// Pressing blue button will vent
//
// PCB v0.3/v0.4/v0.5
//

#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, neopixelPin, NEO_GRB + NEO_KHZ800);

#define DEBUG 1

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initiate with all valve and pumps off
  initializePins();

  Serial.println("This is a test!");

  pixels.begin();  
  pixels.show();

  for (int i = 0; i < 3; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 50, 50));
  }
  pixels.show();
}

void loop() {
  Serial.println(readPressure());

  if (readBtn(BLUE)) {
    //switch on pumps
    switchOnPumps();

    blow();
    delayWhileReadingPressure(250);
    vent();
    delayWhileReadingPressure(250);
    suck();
    delayWhileReadingPressure(250);
  }
  else if (readBtn(RED)) {
    //switch off pumps
    switchOffPumps();

    vent();
  }
  else {
    //switch off pumps
    switchOffPumps();

    closeAllValves();
  }

  delay(20);
}

void delayWhileReadingPressure(unsigned long del){
  unsigned long startTime = millis();
  while(millis() - startTime < del){
    Serial.println(readPressure());
    delay(20);
  }
}
