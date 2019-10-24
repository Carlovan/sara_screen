#include "mqtt.h"
#include <string.h>
#include "log.h"
#include "ssl.h"

const char* USERNAME = "sara_screen";
const char* PASSWORD = "sara_screen";
const char* CLIENT_ID = "sara_screen"; 

MQTTClient::MQTTClient(const String& _server, const String& _id, const String& _topic, MQTTClient::callback_t _callback)
  : PubSubClient(wifiClient), id{_id}, topic{_topic}, server{_server}, callback{_callback} {}

void MQTTClient::begin() {
  wifiClient.setCACert(CA_CERT);
//  wifiClient.setCertificate(CLIENT_CERT);
//  wifiClient.setPrivateKey(CLIENT_KEY);
  
  setServer(server.c_str(), 8883);
  setCallback(this->callback);
}

void MQTTClient::loop() {
  while(!connected()) {
    log("Connecting MQTT");
    if (connect(CLIENT_ID, USERNAME, PASSWORD)) {
      log("MQTT connected");
      subscribe(topic.c_str());
    } else {
      log(String{"Failed, rc="} + state() + " try again in 5 seconds");
      delay(5000);
    }
  }
  PubSubClient::loop();
}
