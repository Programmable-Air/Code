// Programmable-Air
// Author: tinkrmind
// https://github.com/orgs/Programmable-Air
//
// Factory Image
//
// PCB v1.0
#define BOARD_VER 6
#include "programmable_air.h"
#include <Adafruit_NeoPixel.h>
#include "EEPROMAnything.h"
Adafruit_NeoPixel paPixels(3, 12, NEO_GRB + NEO_KHZ800);

#define DEBUG 1

int state = UN_KNOWN;

#define MOTORS_ON 6
#define MOTORS_OFF 7

int calibratedPressure = 0;

const char helpText[] PROGMEM =
  "\t\t\tWelcome to the Programmable - Air kit! \n\n"
  "   _______________________________________|--|________________________________\n"
  "  /__      RED BTN BLUE BTN  POWER   |    |__|     |    NEOPIXELS (PIN 12)   __\\ \n"
  " |   |     (PIN3)  (PIN2)   + 12V    |             |                        |   | \n"
  " |   |           __                  |             |          __            |   | \n"
  " |   |                               |     N       |                        |   | \n"
  " |   |    /               \\          |     A       |   /              \\     |   | \n"
  " |   |         PUMP 1                |     N       |        PUMP 2          |   | \n"
  " |___|  |     (PIN 10)      |        |     O       | |     (PIN 11)     |   |___| \n"
  " |              SUCK                 |             |         BLOW               | \n"
  " |        \\               /          |             |   \\              /         | \n"
  " |               __                  |             |          __                | \n"
  " |                                    _____________                             | \n"
  "  \\                                                                            / \n"
  "   ---------------------------------------------------------------------------- \n"
  "  /                                                                            \\ \n"
  " |                               PRESSURE SENSOR(A3)                            | \n"
  " |          ___                        ___                        ___           | \n"
  " |                                                                              | \n"
  " |    /             \\            /              \\           /             \\     | \n"
  " |   |    VALVE 1    |          |    VALVE 2     |         |    VALVE 3    |    | \n"
  " |   |    (PIN 6)    |          |    (PIN 5)     |         |    (PIN 4)    |    | \n"
  " |    \\    VENT     /            \\    BLOW      /           \\    SUCK     /     | \n"
  " |          ___                        ___                        ___           | \n"
  " |       YELLOW BTN                 GREEN BTN                 WHITE BTN         | \n"
  "  \\  ________________________________________________________________________  / \n\n"

  "\tI hope you're ready to experiment with air, because Programmable-Air is! \n\n"
  "Here's how to get started:  \n"
  "\t * Right now, the vent valve(next to YELLOW button) is switched on,  \n"
  "\t   and the output tube can freely exchange air with the atmosphere. \n"
  "\t * Press the RED button to blow air out of the output tube. \n"
  "\t * Press the BLUE button to suck air into the output tube. \n"
  "\t * Press both RED and BLUE buttons together to switch the motors on or off. \n"
  "\t * When the motors are ON, all the valves will switch off by default. \n"
  "\t   You can now press the WHITE, GREEN, and YELLOW buttons \n"
  "\t   to suck air in, blow air out, and vent air to the atmosphere respectively. \n"
  "\t * All this while, the pressure is being reported on the neopixel; \n"
  "\t   bright cyan is low pressure and bright purple is high pressure. \n"
  "\t * If the neopixels are dim or off, pressure is close to the atmospheric pressure. \n"
  "\t   (Atleast in Manhattan on Friday Oct 18th around 6pm, when I calibrated this board!) \n"
  "\t * The pressure is also being reported in the Serial port as numbers \n"
  "\t   (which is why you had to scroll so much to see this message :P ) \n"
  "\t * Whatever you do, don't block the output tube and send 'test' over serial. \n"
  "\t   Sending 'music' or 'help' over serial is not a good idea either.\n\n"
  "\t\t\t\tHappy hacking!\n"
  "\t\t\t\t\t\t\t\t\t-tinkrmind \n"
  "------------------------------------------------------------------------------------ \n";

void setup() {

  initializePins();
  pixels.begin();
  pixels.show();
  paPixels.begin();
  paPixels.show();

  if (readBtn(BLUE) && readBtn(RED)) {
    testMode();

  }
  printHelpText();
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readString();
    if (data == "test" || data == "test\n" || data == "test\r\n" || data == "test\r") {
      testMode();
    }
    if (data == "help" || data == "help\n" || data == "help\r\n" || data == "help\r") {
      printHelpText();
    }
    if (data == "music" || data == "music\n" || data == "music\r\n" || data == "music\r") {
      playMusic();
    }
  }

  showPressure();

  if (readBtn(BLUE) && readBtn(RED)) {
    if (state == MOTORS_ON) {
      switchOffPumps();
      closeAllValves();
      state = MOTORS_OFF;
    }
    else {
      switchOnPumps(100);
      closeAllValves();
      state = MOTORS_ON;
    }
    while (readBtn(BLUE) && readBtn(RED));
    delay(50);
  }

  // If blue button is pressed start sucking
  if (readBtn(BLUE) && state != SUCKING) {
    // switch on pumps to 50% power
    switchOnPump(1, 100);
    switchOffPump(2);
    suck();
    state = SUCKING;
  }
  // if red button is pressed, start blowing
  else if (readBtn(RED) && state != BLOWING) {
    // switch on pumps to 50% power
    switchOnPump(2, 100);
    switchOffPump(1);
    blow();
    state = BLOWING;
  }

  // if nither button is pressed, vent (but blow for a bit to let go of the object)
  else if (!readBtn(BLUE) && !readBtn(RED) && state != VENTING && state != MOTORS_ON) {
    //    switchOnPump(1, 100);
    //    blow();
    //    delayWhileReadingPressure(250);
    switchOffPumps();
    vent();
    state = VENTING;
  }

  delayWhileReadingPressure(200);
}

void testMode() {

}

void error() {
  Serial.println("ERROR");
  switchOffPumps();
  closeAllValves();
  for (int i = 0; i < 3; i++) {
    paPixels.setPixelColor(i, paPixels.Color(100, 0, 0));
  }
  paPixels.show();
  while (1);
}

void printHelpText() {
  char myChar;
  for (int k = 0; k < strlen_P(helpText); k++) {
    myChar = pgm_read_byte_near(helpText + k);
    Serial.print(myChar);
  }
}

void playMusic() {
  int notes[] = {100, 100, 100, 80, 100, 100, 90, 90, 75, 60, 100, 60, 100, 65, 60, 55, 45, 100, 90, 85, 85, 100, 85, 100, 100, 60};
  int delays[] = {100, 100, 300, 200, 300, 200, 100, 200, 200, 100, 200, 100, 200, 100, 200, 100, 200, 100, 100, 100, 200, 100, 200, 400, 100, 1000};
  Serial.println("Music sequence playing");
  for (int i = 0; i <= sizeof(notes); i++) {
    //cycle through the notes[] array
    switchOnPump(1, notes[i]);
    suck();
    //cycle through the delays[] array
    delay(delays[i]);
    closeAllValves();
    switchOffPumps();
    vent();
    delay(delays[i+1]);
    switchOnPump(1, notes[i]);
    blow();
    delay(delays[i+2]);
  }
  closeAllValves();
  switchOffPumps();
  vent();
  delay(200);
}
