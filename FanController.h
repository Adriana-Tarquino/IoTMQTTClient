#ifndef FANCONTROLLER_H
#define FANCONTROLLER_H

#include <Arduino.h>

class FanController {
  public:
    FanController(int relayPin);
    void controlFan(String command);

  private:
    int relayPin;
};

#endif
