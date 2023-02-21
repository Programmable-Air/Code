// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
// 
// Basic example of using Vent function of the Programmable-Air board. 
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
  // STEP 1 : Read pressure only. Valves and Pumps are all off. 
  // You can turn the vent valve on and off manually using the yellow button.
  // Using a syringe or your mouth try blowing or sucking on the output tube and see how the pressure and thus neopixels are affected.
  // delayWhileReadingPressure(200);

  // STEP 2: Vent the output tube. See if you can affect the neopixels with the following line uncommented.
  vent();
}
