#include "display.h"
#include "log.h"

const int LINE_SPACE = 10;
const int BRIGHT_PWM_CHANNEL = 0;
const int BRIGHT_PWM_PIN = 13;
const int BRIGHT_PWM_RESOLUTION = 8;
const int BRIGHT_PWM_FREQ = 5000;

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

void initDisplay() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  ledcSetup(BRIGHT_PWM_CHANNEL, BRIGHT_PWM_FREQ, BRIGHT_PWM_RESOLUTION);
  ledcAttachPin(BRIGHT_PWM_PIN, BRIGHT_PWM_CHANNEL);
  setBrightness(255);
}

TFT_eSPI& getDisplay() {
  return tft;
}

void drawWrapCenterString(char* string) {
  auto& disp = getDisplay();
  
  char* lines[11][6] = {NULL};// [line][word]
  int lineLen[11] = {0};
  int curLine = 0, curWord = 0;

  while(true) {
    char* next = strtok((curLine == 0 && curWord == 0) ? string : NULL, " ");
    if (next == NULL) break;
    if (lineLen[curLine] + disp.textWidth(next) + disp.textWidth(" ") > disp.width()) {
      curLine++;
      curWord = 0;
    }
    lines[curLine][curWord] = next;
    lineLen[curLine] += disp.textWidth(next) + disp.textWidth(" ");
    curWord++;
  }
  curLine++;

  int totHeight = curLine * (disp.fontHeight() + LINE_SPACE);

  for (int l = 0, y = (disp.height() - totHeight) / 2; l < curLine; l++, y+= disp.fontHeight() + LINE_SPACE) {
    int x = (disp.width() - lineLen[l]) / 2;
    disp.setCursor(x, y);
    for (int w = 0; lines[l][w] != NULL; w++) {
      disp.print(lines[l][w]);
      disp.print(' ');
    }
  }
}

void setBrightness(byte level) {
  ledcWrite(BRIGHT_PWM_CHANNEL, level);
}
