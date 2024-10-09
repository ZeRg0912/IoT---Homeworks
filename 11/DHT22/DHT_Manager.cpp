#include "DHT_Manager.h"

DHT_Manager::DHT_Manager(int count, ...) {
  sensors_count = (count > MAX_SENSORS) ? MAX_SENSORS : count;

  va_list args;
  va_start(args, count);
  
  for (int i = 0; i < sensors_count; i++) {
    pins[i] = va_arg(args, int);
    DHT_sensors[i] = new DHT(pins[i], DHT22);
    DHT_sensors[i]->begin();
  }
  
  va_end(args);
}

DHT_Manager::~DHT_Manager() {
  for (int i = 0; i < sensors_count; i++) {
    delete DHT_sensors[i];
  }
}

// Temperature
float DHT_Manager::MaxTemp() {  
  float t = 0;

  if (sensors_count == 1) return DHT_sensors[0]->readTemperature(false);

  for (int i = 0; i < sensors_count; i++) {
    float temp_t = DHT_sensors[i]->readTemperature(false);
    t = (t > temp_t) ? t : temp_t;
  }

  return t;
}

float DHT_Manager::AvgTemp() {  
  float t = 0;

  if (sensors_count == 1) return DHT_sensors[0]->readTemperature(false);

  for (int i = 0; i < sensors_count; i++) {
    t += DHT_sensors[i]->readTemperature(false);
  }

  t /= sensors_count;

  return t;
}

float DHT_Manager::MinTemp() {  
  float t = 0;

  if (sensors_count == 1) return DHT_sensors[0]->readTemperature(false);

  for (int i = 0; i < sensors_count; i++) {
    float temp_t = DHT_sensors[i]->readTemperature(false);
    t = (t < temp_t) ? t : temp_t;
  }

  return t;
}


// Humidity
float DHT_Manager::MaxHumidity() {  
  float h = 0;

  if (sensors_count == 1) return DHT_sensors[0]->readHumidity();

  for (int i = 0; i < sensors_count; i++) {
    float temp_h = DHT_sensors[i]->readHumidity();
    h = (h > temp_h) ? h : temp_h;
  }

  return h;
}

float DHT_Manager::AvgHumidity() {  
  float h = 0;

  if (sensors_count == 1) return DHT_sensors[0]->readHumidity();

  for (int i = 0; i < sensors_count; i++) {
    h += DHT_sensors[i]->readHumidity();
  }

  h /= sensors_count;

  return h;
}

float DHT_Manager::MinHumidity() {  
  float h = 0;

  if (sensors_count == 1) return DHT_sensors[0]->readHumidity();

  for (int i = 0; i < sensors_count; i++) {
    float temp_h = DHT_sensors[i]->readHumidity();
    h = (h < temp_h) ? h : temp_h;
  }

  return h;
}