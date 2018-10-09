#include "programmable_air.h"

int state = UN_KNOWN;

void setup() {
  Serial.begin(115200);

  initializePins();
  pinMode(A5, INPUT_PULLUP);
  switchOnPump(1, 75);
  switchOnPump(2, 50);

  //  blow(0);
  //  while(1);
}

void loop() {
  if ((!digitalRead(btn2) || !digitalRead(A5)) && state != SUCKING) {
    suck(0);    
    state = SUCKING;
  }
  else if ((!digitalRead(btn1)) && state != BLOWING) {    
    blow(0);
    state = BLOWING;
  }
  else if((digitalRead(btn2) && digitalRead(A5)) && state != VENTING){
    state = VENTING;
    blow(0);
    delay(250);
    vent(0);
  }
  Serial.println(readPressure());
  delay(100);
}
