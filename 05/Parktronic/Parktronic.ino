#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define BLUE 9 
#define GREEN 10 
#define RED 11
#define TRIG 13
#define ECHO 12

#define DELAY_ULTRASONIC 100
#define DELAY_DISPLAY_LCD 1000

float distance_meters;

unsigned long timer_ultrasonic = 0, timer_display_lcd = 0;
unsigned long timer_led = 0;

void ReadUltrasonicDistance() {  
  if (millis() - timer_ultrasonic >= DELAY_ULTRASONIC) {
    pinMode(TRIG, OUTPUT); // сброс Trig
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH); // установка TRIG на 10 мкс
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    pinMode(ECHO, INPUT); // измерение длительности ECHO
    distance_meters = (pulseIn(ECHO, HIGH) / 58) / 100.0;
    timer_ultrasonic = millis();
  }
}

void LCDSetText() {
  lcd.setCursor(0, 0);
  lcd.print("Meters:");
}

void LCDClearDistance() {
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.print(" ");
  }
}

void PrintLCD() {
  if (millis() - timer_display_lcd >= DELAY_DISPLAY_LCD) {
    LCDClearDistance();
    lcd.setCursor(0, 1);
    lcd.print(distance_meters, 1);
    timer_display_lcd = millis();
  }
}

void SetLEDColor(int r, int g, int b) {
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}

void CheckDistance() {
  if (distance_meters < 1.0) {
    if (millis() - timer_led >= 100) {
      SetLEDColor(0, 255, 255); // Красный
      delay(100);
      SetLEDColor(255, 255, 255);
      timer_led = millis();
    }
  } else if (distance_meters >= 1.0 && distance_meters < 2.0) {
    if (millis() - timer_led >= 500) {
      SetLEDColor(0, 0, 255); // Жёлтый
      delay(500);
      SetLEDColor(255, 255, 255);
      timer_led = millis();
    }
  } else if (distance_meters >= 2.0) {
    SetLEDColor(255, 0, 255); // Зеленый
  } else {
    SetLEDColor(255, 255, 255);
  }
}

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  lcd.begin(16 , 2);
  lcd.clear();
  LCDSetText();
}

void loop() {
  ReadUltrasonicDistance();
  PrintLCD();
  CheckDistance();
}
