#ifndef MQTTCLIENTHANDLER_H
#define MQTTCLIENTHANDLER_H

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTClientHandler {
  public:
    MQTTClientHandler(const char* server, int port, WiFiClient& espClient);
    void setup(const char* topicFan, std::function<void(char*, byte*, unsigned int)> callback);
    void connect();
    void loop();
    void publish(const char* topic, const char* message);

  private:
    PubSubClient client;
    const char* server;
    int port;
    const char* topicFan;
};

#endif
