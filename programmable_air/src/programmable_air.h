// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// PCB v0.3/v0.4/v0.5
//

#ifndef programmable_air_h
#define programmable_air_h

#include "Arduino.h"

#include <Adafruit_NeoPixel.h>

const int pump[2] = {10, 11};
const int temp_sense[2] = {A6, A7};

#define OPEN 1
#define CLOSE 0
#define OPENED 1
#define CLOSED 0

#define UN_KNOWN -9
#define INCREASING 1
#define DECREASING -1

#define SUCKING -1
#define BLOWING 1
#define VENTING 0

#define RED 1
#define BLUE 2

// pressure, atmosphere, vaccuum
const int valve[9] = {   4,  5,  6,  \
                         7,  8,  9,  \
                         A4, A1, A0
                     };

const int sense[3] = {A3, A2, A5};

int readPressure(int num, int times);

#define neopixelPin 12
const int btn[2] = { 2, 3 };

Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(3, neopixelPin, NEO_GRB + NEO_KHZ800);

const int load = 13;

void initializePins();

void blow(int i = 0);
void vent(int i = 0);
void ventQuick(int i = 0);
void suck(int i = 0);

int readBtn(int i);

int readPressure(int num = 0, int times = 1);

void setAllValves(int position);
void setValve(int number, int position);
void closeAllValves();

void switchOnPump(int num,  int percentagePower = 100);
void switchOffPump(int num);
void switchOnPumps(int percentagePower = 100);
void switchOffPumps();

void switchOnLoad(int percentagePower = 100);
void switchOffLoad();

#endif
//
// END OF FILE
//
