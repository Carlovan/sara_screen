#include "Arduino.h"
#include "log.h"

bool enabled = false;
Display *display;

bool logIsEnabled() {
  return enabled;
}

void enableLog(Display *disp) {
  Serial.begin(115200);
  display = disp;
  display->setCursor(0, 0, 2);
  display->setTextColor(TFT_WHITE, TFT_BLACK);
  enabled = true;
}

void disableLog() {
  Serial.end();
  enabled = false;
}
