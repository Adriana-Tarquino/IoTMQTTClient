#include "BME680Sensor.h"
#include <Arduino.h>

BME680Sensor::BME680Sensor() {}

void BME680Sensor::begin() {
  if (!bme.begin()) {
    Serial.println("Error: no se encontró el sensor BME680");
    while (1);
  }

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);
}

bool BME680Sensor::readSensorData() {
  return bme.performReading();
}

float BME680Sensor::getTemperature() {
  return bme.temperature;
}

float BME680Sensor::getPressure() {
  return bme.pressure / 100.0F;
}

float BME680Sensor::getHumidity() {
  return bme.humidity;
}

float BME680Sensor::getGasResistance() {
  return bme.gas_resistance / 1000.0;
}
