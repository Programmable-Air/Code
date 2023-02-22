// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
// 
// Basic example of using Blow function of the Programmable-Air board using an External Pump.
// Electrically connect external Pumnp between Vin(+12V) and Load Pins on either side of the Programmable-Air board.
// Then connect the input tube of Valve 2(green button) to the high pressure output of the external pump.
// The neopixels show pressure. Cyan for low pressure and Purple for high pressure
// Brighter color means more extreme pressure. Bright cyan means lower pressure than dim cyan and brighter purple means higher pressure tham dim purple. At atmospheric presure,lights will be off.
//
// PCB v0.3/v0.4/v0.5

#include "programmable_air.h"

#define DEBUG 0

void setup() {
  initializePins();
}

void loop() {
  delayWhileReadingPressure(200);

  // if the RED button is pressed blow air into the output, else, vent to atmosphere
  if(readBtn(RED)){
    // switch on Load to 50% duty cycle
    switchOnLoad(50);
    blow();
  } else{
    switchOffLoad();
    vent();
  }
}