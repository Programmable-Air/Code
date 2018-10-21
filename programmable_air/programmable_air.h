// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// PCB v0.3/v0.4

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
// vacuum, atmosphere, pressure
const int valve[9] = {   5,  4,  6,  \
                         8,  7,  9,  \
                         A1, A4, A0
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

void switchOnPump(int num,  int percentagePower = 100);
void switchOffPump(int num);
void switchOnPumps(int percentagePower = 100);
void switchOffPumps();

void switchOnLoad(int percentagePower = 100);
void switchOffLoad();

void initializePins() {
  Serial.begin(115200);
  while (!Serial);

  for (int i = 0; i < 9; i++) {
    pinMode(valve[i], OUTPUT);
    digitalWrite(valve[i], LOW);
  }

  pinMode(13, OUTPUT);

  pinMode(btn[0], INPUT_PULLUP);
  pinMode(btn[1], INPUT_PULLUP);

  for (int i = 0; i < 2; i++) {
    pinMode(pump[i], OUTPUT);
    digitalWrite(pump[i], LOW);
  }

  neopixel.begin();
  for (int i = 0; i < 3; i++) {
    neopixel.setPixelColor(i, neopixel.Color(0, 10, 10));
  }
  neopixel.show();
  #ifdef DEBUG
    Serial.println("Pins initialised. Not 'initialized'. 'initialised'.");
  #endif
}

//0-blow, 1-vent, 2-suck

void blow(int i=0) {
  #ifdef DEBUG
    Serial.println("blow from daughter board # %d", i);
  #endif
  if (i >= 0 && i <= 2) {
    setValve(i * 3 + 0, OPEN);
    setValve(i * 3 + 1, CLOSE);
    setValve(i * 3 + 2, CLOSE);
  }
}

void vent(int i=0) {
  #ifdef DEBUG
    Serial.println("vent from daughter board # %d", i);
  #endif
  if (i >= 0 && i <= 2) {
    setValve(i * 3 + 0, CLOSE);
    setValve(i * 3 + 1, OPEN);
    setValve(i * 3 + 2, CLOSE);
  }
}

void ventQuick(int i=0) {
  #ifdef DEBUG
    Serial.println("ventQuick from daughter board # %d", i);
  #endif
  if (i >= 0 && i <= 2) {
    setValve(i * 3 + 0, CLOSE);
    setValve(i * 3 + 1, OPEN);
    setValve(i * 3 + 2, OPEN);
  }
}

void suck(int i=0) {
  #ifdef DEBUG
    Serial.println("suck from daughter board # %d", i);
  #endif
  if (i >= 0 && i <= 2) {
    setValve(i * 3 + 0, CLOSE);
    setValve(i * 3 + 1, CLOSE);
    setValve(i * 3 + 2, OPEN);
  }
}

int readBtn(int i){
  return !digitalRead(btn[i-1]);
}

// Read pressure
int readPressure(int num = 0, int times = 1) {
  #ifdef DEBUG
    Serial.print("reading pressure sensor ");
    Serial.print(num);
    Serial.print(" Averaging ");
    Serial.print(times);
    Serial.println(" times.");
  #endif
  long pressure = 0;

  for (int i = 0; i < times; i++) {
    pressure += analogRead(sense[num]);
  }
  pressure /= times;

  #ifdef DEBUG
    Serial.print("Pressure: ");
    Serial.println(pressure);
  #endif

  return int(pressure);
}

void setAllValves(int position) {
  #ifdef DEBUG
    Serial.print("Setting all valves to ")
    if(position == OPEN){
      Serial.println("open");
    } else{
      Serial.println("closed");
    }
  #endif
  if (position == OPEN) {
    for (int i = 0; i < 12; i++) {
      digitalWrite(valve[i], HIGH);
    }
  }

  if (position == CLOSE) {
    for (int i = 0; i < 12; i++) {
      digitalWrite(valve[i], LOW);
    }
  }
}

void setValve(int number, int position) {
  #ifdef DEBUG
    Serial.print("Setting valve # %d to ", number)
    if(position == OPEN){
      Serial.println("open");
    } else{
      Serial.println("closed");
    }
  #endif
  if (position == OPEN) {
    digitalWrite(valve[number], HIGH);
  }

  if (position == CLOSE) {
    digitalWrite(valve[number], LOW);
  }
}

void switchOnPump(int num,  int percentagePower = 100) {
  #ifdef DEBUG
    Serial.println("Setting pump # %d to %d percent power", number, percentagePower);
  #endif
  if (num == 1 || num == 2) {
    analogWrite(pump[num - 1], percentagePower * 255 / 100);
  }
}

void switchOffPump(int num) {
  #ifdef DEBUG
    Serial.println("Switch off pump # %d", number);
  #endif
  if (num == 1 || num == 2) {
    digitalWrite(pump[num - 1], LOW);
  }
}

void switchOnPumps(int percentagePower = 100) {
  #ifdef DEBUG
    Serial.println("Setting both pumps to %d percent power", percentagePower);
  #endif
  analogWrite(pump[0], percentagePower * 255 / 100);
  analogWrite(pump[1], percentagePower * 255 / 100);
}

void switchOffPumps() {
  #ifdef DEBUG
    Serial.println("Switching off both pumps");
  #endif
  digitalWrite(pump[0], LOW);
  digitalWrite(pump[1], LOW);
}

void switchOnLoad(int percentagePower = 100){
  #ifdef DEBUG
    Serial.println("Setting load to %d percent power", percentagePower);
  #endif
  analogWrite(load, percentagePower * 255 / 100);
}

void switchOffLoad(){
  #ifdef DEBUG
    Serial.println("Switching off power to load");
  #endif
  digitalWrite(load, LOW);
}

#endif
//
// END OF FILE
//
