#include <Preferences.h>
#include <WiFi.h>
#include "log.h"

struct credentials_t {
  String SSID;
  String PSK;
};

Preferences settings;

credentials_t connectSmartConfig() {
  //Init WiFi as Station, start SmartConfig
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  //Wait for SmartConfig packet from mobile
  log("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    delay(500);
  }
  while(WiFi.SSID() == "")
    delay(100);

  return {WiFi.SSID(), WiFi.psk()};
}

credentials_t getCredentials() {
  auto SSID = settings.getString("SSID", "");
  auto psk = settings.getString("PSK", "");
  log("Retrieved credentials:");
  log(SSID);
  log(psk);
  return {SSID, psk};
}

void setCredentials(credentials_t cred) {
  log("Setting credentials: \"" + cred.SSID + "\"  \"" + cred.PSK + "\"");
  settings.putString("SSID", cred.SSID);
  settings.putString("PSK", cred.PSK);
}

void connectWiFi(credentials_t cred) {
  log("Connecting to WiFi...");
  WiFi.begin(cred.SSID.c_str(), cred.PSK.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  delay(1000);
}

void connect(int checkPin = 0) {
  delay(10);
  bool forceSC = false;
  settings.begin("sara_screen");

  if(checkPin > 0 && digitalRead(checkPin)) {
    forceSC = true;
    log("Forcing connection with SmartConfig");
  }
  
  auto cred = getCredentials();
  if(cred.SSID == "" || forceSC) {
    cred = connectSmartConfig();
    setCredentials(cred);
    log("WiFi connected with SmartConfig");
    log(cred.SSID);
    log(cred.PSK);
  } else {
    connectWiFi(cred);
    log("WiFi connected");
  }

  settings.end();
}
