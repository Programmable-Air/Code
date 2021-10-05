/*
   Programmable-Air
   Author: tinkrmind
   https://github.com/orgs/Programmable-Air

   Telepresence balloon control. Connections below:

   Board 1    Board 2
   A0         A1
   A1         A0
   GND        GND

   PCB v1.1
*/

#define inputPin A0
#define outputPin A1

#include "programmable_air.h"

#include <Adafruit_NeoPixel.h>

#define STEADY_STATE 0
#define INFLATING_REMOTE 1
#define INFLATING_SELF 2

#define DEBUG 1

int pressureUpperThreshold = 550; // steady state pressure + margin of error
int pressureUpperMargin = 20;
int pressureLowerThreshold = 500;

int state = STEADY_STATE;

void setup() {
  initializePins();

  pinMode(inputPin, INPUT_PULLUP);
  pinMode(outputPin, OUTPUT);

  steadyStateSelf();
}

void loop() {
  int prevState = state;
  int pressure = showPressure();

  if (state == INFLATING_SELF) {
    // Stop inflating if remote signal disabled
    if (digitalRead(inputPin) == 1) {
      steadyStateSelf();
      state = STEADY_STATE;
    }
  }

  if (state == STEADY_STATE) {
    // inflate if triggered by remote or self button press
    if (digitalRead(inputPin) == 0 || readBtn(1) == 1) {
      state = INFLATING_SELF;
      inflateSelf();
    }

    if (state == STEADY_STATE && prevState == INFLATING_SELF) {
      // suck all air out of the balloon quickly then go to steady state
      while (pressure > pressureLowerThreshold) {
        pressure = showPressure();
        switchOnPump(1, 100);
        ventQuick();
      }
      switchOffPump(1);
      steadyStateSelf();
    }

    // if pressed, inflate remote
    if (pressure > pressureUpperThreshold) {
      inflateRemote();
    } else {
      steadyStateRemote();
    }
  }

  if (state == INFLATING_REMOTE) {
    // if pressure released, go back to steady state
    if (pressure < (pressureUpperThreshold - pressureUpperMargin)) {
      steadyStateSelf();
      state = STEADY_STATE;
    }
  }

  delay(50);
}

int steadyStateRemote() {
  digitalWrite(outputPin, HIGH);
}

int inflateRemote() {
  digitalWrite(outputPin, LOW);
  state = INFLATING_REMOTE;
  // close the valves so that no air is added or escapes
  closeAllValves();
  switchOffPumps();
}

int steadyStateSelf() {
  // pump blowing air at low rate, vent open to let excess air out.
  // better than just adding some air in the beginning and then closing all valves because the system might have leaks.
  // TODO: Do this on a duty cycle instead.
  switchOnPump(2, 35);
  blow();
  setValve(1, 1); // vent
}

int inflateSelf() {
  // Add air into the balloon quickly
  switchOnPump(2, 100);
  blow();
  //  setValve(1, 1); // vent as well? To make sure the balloon doesn't explode?
}
