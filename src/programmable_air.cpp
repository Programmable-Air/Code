// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// PCB v0.3/v0.4/v0.5
//

#include "programmable_air.h"

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

void closeAllValves(){
  for (int i = 0; i < 12; i++) {
    digitalWrite(valve[i], LOW);
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

//
// END OF FILE
//
