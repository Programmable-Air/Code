// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Basic example of using Suck function of the Programmable-Air board.
// The neopixels show pressure. Cyan for low pressure and Purple for high pressure
// Brighter color means more extreme pressure. Bright cyan means lower pressure than dim cyan and brighter purple means higher pressure tham dim purple. At atmospheric presure,lights will be off.
//
// PCB v0.3/v0.4/v0.5

#include "programmable_air.h"
#include <SharpIR.h>

#define MIN_DISTANCE 45
#define MAX_DISTANCE 55
int distance;
SharpIR sensor( SharpIR::GP2Y0A02YK0F, A0);

#define DEBUG 1

void setup() {
  initializePins();
}

void loop() {
  if (readBtn(RED)) {
    switchOnPump(2);
    blow(); // setValve(2, OPEN); setValve(1, CLOSED); setValve(3, CLOSED);
    distance = sensor.getDistance();
    while(distance > MIN_DISTANCE){
        delayWhileReadingPressure(100);
        distance = sensor.getDistance();
    }

    switchOffPumps();
    vent();
    distance = sensor.getDistance();
    while(distance < MAX_DISTANCE){
        delayWhileReadingPressure(100);
        distance = sensor.getDistance();
    }
  }
  else {
    delayWhileReadingPressure(100);
  }
}