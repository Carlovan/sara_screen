#include "wifi.h"
#include "log.h"
#include "mqtt.h"

const int BOOTMAGIC_PIN = 14;
const char* MQTT_HOSTNAME = "cauldron.liquoricemage.it";
const char* MQTT_CLIENT_ID = "sara_screen";
const char* MQTT_TOPIC = "sara_screen/publish";

void onMQTTReceive(const char* topic, byte* payload, unsigned int length) {
  char msg[length + 1];
  strncpy(msg, (char*)payload, length);
  msg[length] = 0;

  auto& disp = getDisplay();
  disp.fillScreen(TFT_BLACK);
  disp.setTextFont(4);
  disp.setTextSize(2);
  disp.setTextColor(TFT_WHITE);

  drawWrapCenterString(msg);
}

MQTTClient client(MQTT_HOSTNAME, MQTT_CLIENT_ID, MQTT_TOPIC, onMQTTReceive);

void setup() {
  Serial.begin(115200);
  initDisplay();
  enableLog();

  pinMode(BOOTMAGIC_PIN, INPUT_PULLDOWN);

  connect(BOOTMAGIC_PIN);
  delay(1000);
  client.begin();
}

void loop() {
  client.loop();
  delay(1000);
}
