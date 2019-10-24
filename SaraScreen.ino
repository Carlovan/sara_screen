#include "wifi.h"
#include "log.h"
#include "mqtt.h"

const int BOOTMAGIC_PIN = 23;

void onMQTTReceive(const char* topic, byte* payload, unsigned int length) {
  char msg[length+1];
  strncpy(msg, (char*)payload, length);
  msg[length] = 0;

  auto& disp = getDisplay();
  disp.fillScreen(TFT_BLACK);
  disp.setTextFont(4);
  disp.setTextSize(2);
  disp.setTextColor(TFT_WHITE);
//  disp.setTextWrap(true);
//  disp.drawString(msg, disp.width() / 2, disp.height() / 2, 4);

  drawWrapCenterString(msg);
}

MQTTClient client("cauldron.liquoricemage.it", "sara_screen", "sara_screen/publish", onMQTTReceive);

void setup() {
  initDisplay();
  enableLog();

  pinMode(BOOTMAGIC_PIN, OUTPUT);
  digitalWrite(BOOTMAGIC_PIN, LOW);
  
  connect(BOOTMAGIC_PIN);
  delay(1000);
  client.begin();
}

void loop() {
  client.loop();
  delay(1000);
}
