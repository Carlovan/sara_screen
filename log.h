#ifndef _SARA_LOG
#define _SARA_LOG

#include "display.h"

extern Display* display;

bool logIsEnabled();
void enableLog(Display *disp);
void disableLog();

template<typename ...T>
void log(T ... args) {
  if(logIsEnabled()) {
    Serial.println(args...);
    display->println(args...);
  }
}

#endif
