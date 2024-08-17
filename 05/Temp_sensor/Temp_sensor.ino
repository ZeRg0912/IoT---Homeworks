#include <LiquidCrystal.h>
#include <math.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define SENSOR_1 A0
#define SENSOR_2 A1
#define SENSOR_3 A2

#define COUNT 10
#define DELAY 100

int buffer_1[COUNT] = {0}, buffer_2[COUNT] = {0}, buffer_3[COUNT] = {0};
int index_1 = 0, index_2 = 0, index_3 = 0;
unsigned long timer_sensor_1 = 0, timer_sensor_2 = 0, timer_sensor_3 = 0;

double last_min_temp = 0, last_max_temp = 0, last_avg_temp = 0;

void setup() {
  pinMode(SENSOR_1, INPUT_PULLUP);
  pinMode(SENSOR_2, INPUT_PULLUP);
  pinMode(SENSOR_3, INPUT_PULLUP);

  lcd.begin(16 , 2);
  lcd.clear();
  SetTextInfo();
}

void SetTextInfo(){  
  lcd.setCursor(0, 0);
  lcd.print("MIN:");
  lcd.setCursor(8, 0);
  lcd.print("MAX:");
  lcd.setCursor(0, 1);
  lcd.print("AVG:");
}

float GetTerm(int raw) {
  float celsius = 1 / (log(1 / (1023. / raw - 1)) / 3050 + 1.0 / 298.15) - 273.15;
  return celsius;
}

double Sensor(int PIN, int* buffer, int& index, unsigned long& timer) { 
  double result = 0; 
  if (millis() - timer >= DELAY) {
    result = 0;
    buffer[index] = GetTerm(analogRead(PIN));
    for (int i = 0; i < COUNT; i++) {
      result += buffer[i];
    }
    index = (index + 1) % COUNT;
    timer = millis();
  } else {
    for (int i = 0; i < COUNT; i++) {
      result += buffer[i];
    }
  }
  return result / COUNT;
}

void LCDPrint(){
  double temp_1 = Sensor(SENSOR_1, buffer_1, index_1, timer_sensor_1);
  double temp_2 = Sensor(SENSOR_2, buffer_2, index_2, timer_sensor_2);
  double temp_3 = Sensor(SENSOR_3, buffer_3, index_3, timer_sensor_3);

  double min_temp = min(min(temp_1, temp_2), temp_3);
  double max_temp = max(max(temp_1, temp_2), temp_3);
  double avg_temp = (temp_1 + temp_2 + temp_3) / 3;

  if (last_min_temp != min_temp) {
    lcd.setCursor(4, 0);
    lcd.print("   ");
    lcd.setCursor(4, 0);
    lcd.print(min_temp, 0);
    last_min_temp = min_temp;
  }

  if (last_max_temp != max_temp) {
    lcd.setCursor(12, 0);
    lcd.print("   ");
    lcd.setCursor(12, 0);
    lcd.print(max_temp, 0);
    last_max_temp = max_temp;
  }

  if (last_avg_temp != avg_temp) {
    lcd.setCursor(4, 1);
    lcd.print("   ");
    lcd.setCursor(4, 1);
    lcd.print(avg_temp, 0);
    last_avg_temp = avg_temp;
  }
}

void loop() {
  LCDPrint();
}
