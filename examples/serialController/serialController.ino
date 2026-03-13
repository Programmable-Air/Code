// 
// Controller Board Code
// Can be any microcontroller, connect via 220 Ohm resistor to Programmable-Air board if using a 3.3V microcontroller.
//

#include "programmable_air.h"
#include <SoftwareSerial.h>

const byte rxPin = 7;
const byte txPin = 8;

// Set up a new SoftwareSerial object
SoftwareSerial mySerial(rxPin, txPin);
// #define DEBUG 1

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
}

void loop() {
  // mySerial.println("A");
  // delay(100);
  while (Serial.available()) {
    String data = Serial.readString();
    mySerial.print(data);
    delay(10);
  }
  while (mySerial.available()) {
    String data = mySerial.readString();
    Serial.print(data);
    delay(10);
  }
}
