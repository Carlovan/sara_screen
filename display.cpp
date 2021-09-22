#include "display.h"
#include "log.h"

const int LINE_SPACE = 10;
const int BRIGHT_PWM_CHANNEL = 0;
const int BRIGHT_PWM_PIN = 13;
const int BRIGHT_PWM_RESOLUTION = 8;
const int BRIGHT_PWM_FREQ = 5000;


Display::Display() {
  init();
  setRotation(3);
  fillScreen(TFT_BLACK);

  ledcSetup(BRIGHT_PWM_CHANNEL, BRIGHT_PWM_FREQ, BRIGHT_PWM_RESOLUTION);
  ledcAttachPin(BRIGHT_PWM_PIN, BRIGHT_PWM_CHANNEL);
  setBrightness(255);
}

void Display::drawWrapCenterString(char* string) {
  char* lines[11][6] = {NULL};// [line][word]
  int lineLen[11] = {0};
  int curLine = 0, curWord = 0;

  while(true) {
    char* next = strtok((curLine == 0 && curWord == 0) ? string : NULL, " ");
    if (next == NULL) break;
    if (lineLen[curLine] + textWidth(next) + textWidth(" ") > width()) {
      curLine++;
      curWord = 0;
    }
    lines[curLine][curWord] = next;
    lineLen[curLine] += textWidth(next) + textWidth(" ");
    curWord++;
  }
  curLine++;

  int totHeight = curLine * (fontHeight() + LINE_SPACE);

  for (int l = 0, y = (height() - totHeight) / 2; l < curLine; l++, y+= fontHeight() + LINE_SPACE) {
    int x = (width() - lineLen[l]) / 2;
    setCursor(x, y);
    for (int w = 0; lines[l][w] != NULL; w++) {
      print(lines[l][w]);
      print(' ');
    }
  }
}

void Display::setBrightness(byte level) {
  ledcWrite(BRIGHT_PWM_CHANNEL, level);
}
