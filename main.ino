#include <WiFi.h>
#include <Wire.h>
#include "BME680Sensor.h"
#include "FanController.h"
#include "MQTTClientHandler.h"

const char* ssid = "IoTGrupo10";
const char* password = "12345adri";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* mqtt_topic_fan = "ucb/cba/iot/fan";              
const char* mqtt_topic_temperature = "ucb/cba/iot/bme680/temperature";
const char* mqtt_topic_pressure = "ucb/cba/iot/bme680/pressure";
const char* mqtt_topic_humidity = "ucb/cba/iot/bme680/humidity";
const char* mqtt_topic_gas = "ucb/cba/iot/bme680/gas";        

WiFiClient espClient;
BME680Sensor bmeSensor;
FanController fan(19);
MQTTClientHandler mqttHandler(mqtt_server, mqtt_port, espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  String receivedMessage = "";
  for (int i = 0; i < length; i++) {
    receivedMessage += (char)message[i];
  }
  
  receivedMessage.trim(); 
  
  Serial.print("Mensaje recibido en el topic [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(receivedMessage);
  
  // Control manual del ventilador
  if (String(topic) == mqtt_topic_fan) {
    fan.controlFan(receivedMessage);
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  bmeSensor.begin();

  mqttHandler.setup(mqtt_topic_fan, callback);
}

void loop() {
  if (!espClient.connected()) {
    mqttHandler.connect();
  }

  mqttHandler.loop(); 

  if (!bmeSensor.readSensorData()) {
    Serial.println("Error al leer el sensor BME680");
    return;
  }

  float temperature = bmeSensor.getTemperature();
  float pressure = bmeSensor.getPressure();
  float humidity = bmeSensor.getHumidity();
  float gas_resistance = bmeSensor.getGasResistance();

  // Publicar cada dato en su respectivo tópico
  mqttHandler.publish(mqtt_topic_temperature, String(temperature).c_str());
  mqttHandler.publish(mqtt_topic_pressure, String(pressure).c_str());
  mqttHandler.publish(mqtt_topic_humidity, String(humidity).c_str());
  mqttHandler.publish(mqtt_topic_gas, String(gas_resistance).c_str());

  // Imprimir datos del sensor en el puerto serial
  Serial.println("Datos del BME680:");
  Serial.println("  Temperatura: " + String(temperature) + "°C");
  Serial.println("  Presión: " + String(pressure) + " hPa");
  Serial.println("  Humedad: " + String(humidity) + " %");
  Serial.println("  Resistencia de gas: " + String(gas_resistance) + " kOhms");

  delay(3000); 
}
