//
// Controlled Programmable-Air board
// Pin 7 is used as softwareSerial input to control the board
//

#include "programmable_air.h"
#include <SoftwareSerial.h>

const byte rxPin = 7;
const byte txPin = 8;

// Set up a new SoftwareSerial object
SoftwareSerial mySerial(rxPin, txPin);

// #define DEBUG 1

void setup() {
  initializePins();
  // ---- these pins are declared as OUTPUT in Programmable-Air library. That will trip up software serial. So declare them as inout explicitly.
  pinMode(rxPin, INPUT);
  pinMode(txPin, INPUT);
  //----

  mySerial.begin(9600);
  Serial.begin(115200);

  Serial.println("START2");
}

void loop() {
  if (mySerial.available()) {
    String data = mySerial.readString();
    Serial.println(data);
    if (data.substring(0, 4) == "blow") {
      switchOffPumps();
      switchOnPump(2);
      blow();
    }
    if (data.substring(0, 4) == "suck") {
      switchOffPumps();
      switchOnPump(1);
      suck();
    }
    if (data.substring(0, 4) == "vent") {
      switchOffPumps();
      vent();
    }
    Serial.print(char(mySerial.read()));
  }
  delay(200);
}
