// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// PCB v0.3/v0.4/v0.5
//

#ifndef programmable_air_h
#define programmable_air_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

const int pump[2] = {10, 11};

#define OPEN 1
#define CLOSE 0
#define OPENED 1
#define CLOSED 0
#define ENGAGE 1
#define DISENGAGE 0
#define ENGAGED 1
#define DISENGAGED 0

#define UN_KNOWN -9
#define INCREASING 1
#define DECREASING -1

#define SUCKING -1
#define BLOWING 1
#define VENTING 0

#define RED 1
#define BLUE 2

extern Adafruit_NeoPixel pixels;

#ifndef BOARD_VER
// pressure, atmosphere, vaccuum
const int valve[9] = {   5,  4,  6,   \
                         8,  7,  9,   \
                         A1, A4, A0
                     };
#else
#if BOARD_VER == 6
//  atmosphere, pressure, vaccuum
const int valve[9] = {   6,  5,  4,   \
                         9,  8,  7,   \
                         A0, A1, A4
                     };
#else
  // pressure, atmosphere, vaccuum
  const int valve[9] = {   5,  4,  6,   \
                           8,  7,  9,   \
                           A1, A4, A0
                       };
#endif
#endif
const int sense[3] = {A3, A2, A5};

int readPressure(int num, int times);

#define neopixelPin 12
const int btn[2] = { 3, 2 };

const int load = 13;

void initializePins();

void blow(int i = 1);
void vent(int i = 1);
void ventQuick(int i = 1);
void suck(int i = 1);

int readBtn(int i);

int readPressure(int num = 1, int times = 1);

void setAllValves(int position);
void setValve(int number, int position);
void closeAllValves();

void switchOnPump(int num,  int percentagePower = 100);
void switchOffPump(int num);
void switchOnPumps(int percentagePower = 100);
void switchOffPumps();

void switchOnLoad(int percentagePower = 100);
void switchOffLoad();

// void delayWhilePrintingPressure(unsigned long del, int threshold = 8);

int showPressure(int atmospheric_pressure = 500, int threshold = 8);
void delayWhileReadingPressure(unsigned long del);
void setAllNeopixels(uint32_t c);
#endif
//
// END OF FILE
//
