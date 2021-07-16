#include "Arduino.h"
#include "log.h"

bool enabled = false;

bool logIsEnabled() {
  return enabled;
}

void enableLog() {
  Serial.begin(115200);
  getDisplay().setCursor(0, 0, 2);
  getDisplay().setTextColor(TFT_WHITE, TFT_BLACK);
  enabled = true;
}

void disableLog() {
  Serial.end();
  enabled = false;
}
