#include "programmable_air.h"

float old_pressure;
float clean_pressure;
float temp_pressure;
float alpha = 0.7;

void setup() {
  Serial.begin(115200);

  initializePins();

  switchOnPump(1, 0);
  switchOnPump(2, 0);

  vent();

  clean_pressure = readPressure();
  old_pressure = readPressure();
}
void loop() {
  temp_pressure = readPressure();
  clean_pressure = old_pressure * (1 - alpha) + temp_pressure * alpha;

  Serial.print(temp_pressure);
  if (temp_pressure > 512) {
    for (int i = 0; i < 3; i++) {
      neopixel.setPixelColor(i, neopixel.Color((temp_pressure-508) * 3, 0, (temp_pressure-508) * 3));
    }
    neopixel.show();
  }
  else {
    for (int i = 0; i < 3; i++) {
      neopixel.setPixelColor(i, neopixel.Color(0, 0, 0));
    }
    neopixel.show();
  }

  old_pressure = clean_pressure;



  Serial.println();
  delay(50);
}
