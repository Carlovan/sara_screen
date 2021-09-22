#ifndef _SARA_DISPLAY
#define _SARA_DISPLAY

#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

class Display : public TFT_eSPI {
  private:
    TFT_eSPI tft;
  public:
    Display();

    void drawWrapCenterString(char* string);
    void setBrightness(byte level);
};

#endif
