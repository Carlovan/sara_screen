#ifndef _SARA_LOG
#define _SARA_LOG

#include "display.h"

bool logIsEnabled();
void enableLog();
void disableLog();

template<typename ...T>
void log(T ... args) {
  if(logIsEnabled()) {
    Serial.println(args...);
    getDisplay().println(args...);
  }
}

#endif
