#ifndef _SARA_DISPLAY
#define _SARA_DISPLAY

#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

void initDisplay();
TFT_eSPI& getDisplay();

void drawWrapCenterString(char* string);
void setBrightness(byte level);

#endif
