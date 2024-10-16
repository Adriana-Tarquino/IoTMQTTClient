#include "MQTTClientHandler.h"
#include <Arduino.h>

MQTTClientHandler::MQTTClientHandler(const char* server, int port, WiFiClient& espClient) : client(espClient) {
  this->server = server;
  this->port = port;
}

void MQTTClientHandler::setup(const char* topicFan, std::function<void(char*, byte*, unsigned int)> callback) {
  client.setServer(server, port);
  client.setCallback(callback);
  this->topicFan = topicFan;
}

void MQTTClientHandler::connect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    if (client.connect("IoT")) {
      Serial.println("Conectado");
      client.subscribe(topicFan);
    } else {
      Serial.print("fallido, rc=");
      Serial.print(client.state());
      Serial.println(" intentando de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void MQTTClientHandler::loop() {
  client.loop();
}

void MQTTClientHandler::publish(const char* topic, const char* message) {
  client.publish(topic, message);
}
