#ifndef BME680SENSOR_H
#define BME680SENSOR_H

#include <Adafruit_BME680.h>

class BME680Sensor {
  public:
    BME680Sensor();
    void begin();
    bool readSensorData();
    float getTemperature();
    float getPressure();
    float getHumidity();
    float getGasResistance();

  private:
    Adafruit_BME680 bme;
};

#endif
