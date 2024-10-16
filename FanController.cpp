#include "FanController.h"

FanController::FanController(int relayPin) {
  this->relayPin = relayPin;
  pinMode(relayPin, OUTPUT);
}

void FanController::controlFan(String command) {
  if (command == "On") {
    digitalWrite(relayPin, HIGH);
    Serial.println("Ventilador encendido (control manual)");
  } else if (command == "Off") {
    digitalWrite(relayPin, LOW);
    Serial.println("Ventilador apagado (control manual)");
  }
}
