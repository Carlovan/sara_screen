#ifndef _SARA_MQTT
#define _SARA_MQTT

#include <WiFiClientSecure.h>
#include <PubSubClient.h>


class MQTTClient : public PubSubClient {
  public: using callback_t = void (*)(const char* topic, byte* payload, unsigned int length);
  private:
    WiFiClientSecure wifiClient{};
    String id;
    String topic;
    String server;
    callback_t callback;
  public:

    MQTTClient(const String& server, const String& id, const String& topic, MQTTClient::callback_t callback);
    void loop();
    void begin();
};

#endif
