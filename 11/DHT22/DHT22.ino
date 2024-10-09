#include "DHT_Manager.h"

DHT_Manager dhts(6, 2, 3, 4, 5, 6, 7);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("---Temperature---");
  Serial.print("Max temp: ");
  Serial.print(dhts.MaxTemp());
  Serial.print("C; Avg temp: ");
  Serial.print(dhts.AvgTemp());
  Serial.print("C; Min temp: ");
  Serial.print(dhts.MinTemp());
  Serial.println("C;");

  Serial.println("---Humidity---");
  Serial.print("Max humidity: ");
  Serial.print(dhts.MaxHumidity());
  Serial.print("%; Avg humidity: ");
  Serial.print(dhts.AvgHumidity());
  Serial.print("%; Min humidity: ");
  Serial.print(dhts.MinHumidity());
  Serial.println("%;");

  Serial.println("-------------------------");
  delay(1000);
}
