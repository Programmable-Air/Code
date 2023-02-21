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

#define DEBUG 1

void setup() {
  initializePins();
}

void loop() {
  delayWhileReadingPressure(200);

  // if the BLUE button is pressed suck air out of the output, else, vent to atmosphere
  if(readBtn(BLUE)){
    // switch on Pump 1 (suck) to 50% duty cycle
    switchOnPump(1, 50);
    suck();
  } else{
    vent();
  }
}
