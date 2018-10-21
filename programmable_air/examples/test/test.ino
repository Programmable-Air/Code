// Programmable Air
// Author: tinkrmind
// github.com/tinkrmind/programmable-air
//
// Pressing btn1 will switch on pumps and squentially switch on all valves
// Pressing btn2 will vent
//
// PCB v0.3/v0.4
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
  Serial.println(readPressure(0,1));

  if (readBtn(1)) {
    //switch on pumps
    switchOnPumps();

    blow(0);
    delay(250);
    vent(0);
    delay(250);
    suck(0);
    delay(250);
  }
  else if (readBtn(2)) {
    //switch off pumps
    switchOffPumps();

    vent(0);
  }
  else {
    //switch off pumps
    switchOffPumps();

    closeAllValves();
  }

  delay(200);
}
