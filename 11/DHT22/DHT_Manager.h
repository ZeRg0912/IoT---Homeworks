#ifndef DHT_MANAGER_H
#define DHT_MANAGER_H

#include "DHT.h"

#define MAX_SENSORS 6

class DHT_Manager {
public:
  DHT_Manager(int count, ...);
  ~DHT_Manager();

  float MaxTemp();
  float AvgTemp();
  float MinTemp();

  float MaxHumidity();
  float AvgHumidity();
  float MinHumidity();

private:
  int sensors_count;
  int pins[MAX_SENSORS];
  DHT* DHT_sensors[MAX_SENSORS];
};

#endif //DHT_MANAGER_H