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

#define DEBUG 1

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initiate with all valve and pumps off
  initializePins();

  Serial.println("This is a test!");

  for (int i = 0; i < 3; i++) {
    neopixel.setPixelColor(i, neopixel.Color(0, 50, 50));
  }
  neopixel.show();
}

void loop() {
  Serial.println(readPressure());

  if (readBtn(RED)) {
    //switch on pumps
    switchOnPumps();

    blow();
    delayWhileReadingPressure(250);
    vent();
    delayWhileReadingPressure(250);
    suck();
    delayWhileReadingPressure(250);
  }
  else if (readBtn(BLUE)) {
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
