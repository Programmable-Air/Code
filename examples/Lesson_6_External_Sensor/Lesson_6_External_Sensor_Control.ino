// Programmable-Air
// Author: angelw
// https://github.com/orgs/Programmable-Air
//
// This example uses an IR sensor to control when to suck, blow and vent using the Programmable Air.
//
// PCB v0.3/v0.4/v0.5

#include "programmable_air.h"
#include <SharpIR.h>

#define DEBUG 1

#define BLOWING_DIST 45
#define SUCKING_DIST 70

int distance;

//Check and edit the sensor model when necessary, models supported by library: GP2Y0A41SK0F, GP2Y0A21YK0F, GP2Y0A02YK0F. https://github.com/qub1750ul/Arduino_SharpIR
SharpIR sensor( SharpIR::GP2Y0A21YK0F, A0); 

void setup() {
  initializePins();
  pinMode(A0, INPUT);
}

void loop() {
  int distance = sensor.getDistance(); 
  Serial.println( distance );

  if (distance > SUCKING_DIST) {
      switchOffPumps();
      switchOnPump(1, 50);
      suck();
      //Serial.println("sucking");
  } else if (distance > BLOWING_DIST) {
      switchOffPumps();
      switchOnPump(2);
      blow(); 
      //Serial.println("blowing");
  } else {
    switchOffPumps();
    vent();
  }
}
