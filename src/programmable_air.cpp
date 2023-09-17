// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// PCB v0.3/v0.4/v0.5
//
#define BOARD_VER 6
#include "programmable_air.h"
#include "Adafruit_NeoPixel.h"
#include <EEPROM.h>

Adafruit_NeoPixel pixels(3, neopixelPin, NEO_GRB + NEO_KHZ800);

void initializePins() {
  Serial.begin(115200);
  while (!Serial);
  analogReference(EXTERNAL);

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

  pixels.begin();
  pixels.show();

  #ifdef DEBUG
    Serial.println("Pins initialized.");
  #endif
}

//1-vent, 2-blow, 3-suck

void blow(int i) {
  #ifdef DEBUG
    Serial.println("blow from daughter board # %d", i);
  #endif
  if (i >= 1 && i <= 3) {
    setValve((i-1) * 3 + 1, CLOSE);
    setValve((i-1) * 3 + 2, OPEN);
    setValve((i-1) * 3 + 3, CLOSE);
  }
}

void vent(int i) {
  #ifdef DEBUG
    Serial.println("vent from daughter board # %d", i);
  #endif
  if (i >= 1 && i <= 3) {
    setValve((i-1) * 3 + 1, OPEN);
    setValve((i-1) * 3 + 2, CLOSE);
    setValve((i-1) * 3 + 3, CLOSE);
  }
}

void ventQuick(int i) {
  #ifdef DEBUG
    Serial.println("ventQuick from daughter board # %d", i);
  #endif
  if (i >= 1 && i <= 3) {
    setValve((i-1) * 3 + 1, OPEN);
    setValve((i-1) * 3 + 2, OPEN);
    setValve((i-1) * 3 + 3, CLOSE);
  }
}

void suck(int i) {
  #ifdef DEBUG
    Serial.println("suck from daughter board # %d", i);
  #endif
  if (i >= 1 && i <= 3) {
    setValve((i-1) * 3 + 1, CLOSE);
    setValve((i-1) * 3 + 2, CLOSE);
    setValve((i-1) * 3 + 3, OPEN);
  }
}

int readBtn(int i){
  int button_status = !digitalRead(btn[i-1]);

  #ifdef DEBUG
    Serial.print("Button ");
    Serial.print(i);
    Serial.print(" status: ");
    Serial.println(button_status);
  #endif

  return button_status;
}

// Read pressure
int readPressure(int num, int times) {
  #ifdef DEBUG
    Serial.print("reading pressure sensor ");
    Serial.print(num);
    Serial.print(" Averaging ");
    Serial.print(times);
    Serial.println(" times.");
  #endif

  long pressure = 0;

  for (int i = 0; i < times; i++) {
    pressure += analogRead(sense[num-1]);
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
    Serial.print("Setting all valves to ");
    if(position == OPEN){
      Serial.println("open");
    } else{
      Serial.println("closed");
    }
  #endif
  if (position == OPEN) {
    for (int i = 0; i < 9; i++) {
      digitalWrite(valve[i], HIGH);
    }
  }

  if (position == CLOSE) {
    for (int i = 0; i < 9; i++) {
      digitalWrite(valve[i], LOW);
    }
  }
}

void setValve(int number, int position) {
  #ifdef DEBUG
    Serial.print("Setting valve #");
    Serial.print(number);
    Serial.print(" to ");
    if(position == OPEN){
      Serial.println("open");
    } else{
      Serial.println("closed");
    }
  #endif
  if (position == OPEN) {
    digitalWrite(valve[number - 1], HIGH);
  }

  if (position == CLOSE) {
    digitalWrite(valve[number - 1], LOW);
  }
}

void closeAllValves(){
  for (int i = 0; i < 9; i++) {
    digitalWrite(valve[i], LOW);
  }
}

void switchOnPump(int num,  int percentagePower) {
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

void switchOnPumps(int percentagePower) {
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

void switchOnLoad(int percentagePower){
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

// void delayWhilePrintingPressure(unsigned long del, int n){
//   unsigned long startTime = millis();
//   while(millis() - startTime < del){
//     int pressure = readPressure(n);
//     Serial.println(pressure);
//     delay(20);
//   }
// }

int showPressure(int atmospheric_pressure, int threshold){
  int calibratedPressure = 0;
  calibratedPressure += EEPROM.read(3)<<24;
  calibratedPressure += EEPROM.read(2)<<16;
  calibratedPressure += EEPROM.read(1)<<8;
  calibratedPressure += EEPROM.read(0);
  if(calibratedPressure > 450 && calibratedPressure < 550){
    atmospheric_pressure = calibratedPressure;
  }
  int pressure = readPressure();
  Serial.println(pressure);

  int pressure_diff = pressure - atmospheric_pressure;

  if (pressure_diff > threshold) {
    setAllNeopixels(pixels.Color(pressure_diff/3, 0, pressure_diff/3));
  }
  if (pressure_diff < -threshold) {
    setAllNeopixels(pixels.Color(0, -pressure_diff/3, -pressure_diff/3));
  }
  if (abs(pressure_diff) < threshold) {
    setAllNeopixels(pixels.Color(0, 0, 0));
  }

  return pressure;
}

void delayWhileReadingPressure(unsigned long del){
  unsigned long startTime = millis();
  while(millis() - startTime < del){
    showPressure();
    delay(20);
  }
}

void setAllNeopixels(uint32_t c){
    for (int i = 0; i < 3; i++) {
      pixels.setPixelColor(i, c);
    }
    pixels.show();
}


//
// END OF FILE
//
