#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define joystick_x A4
#define joystick_y A5
#define joystick_button A3
#define DIODE 13
#define SENSOR 12

#define DEAD_ZONE 20
#define DELAY 100

unsigned long timer_y = 0, timer_button = 0;

int delay_time = 2;
bool led_on = false;
unsigned long led_timer = 0;

void ReadJoystick() {
  int Y = analogRead(joystick_y);
  if (Y < 512 - DEAD_ZONE || Y > 512 + DEAD_ZONE) {
    if (millis() - timer_y >= DELAY) {
      if (Y < 512 - DEAD_ZONE || Y > 512 + DEAD_ZONE) {
        if (Y > (512 + DEAD_ZONE)) {
          delay_time++;
          if (delay_time > 10) {
            delay_time = 10;
          }
        } else if (Y < (512 - DEAD_ZONE)) {
          delay_time--;
          if (delay_time < 2) {
            delay_time = 2;
          }
        }
      }      
      timer_y = millis();
    }
  }
}

void CheckJoystickButton() {
  if (digitalRead(joystick_button) == LOW){
    if (millis() - timer_button >= DELAY) {
      if (digitalRead(joystick_button) == LOW) {
        delay_time = 2;
        timer_button = millis();
      }
    }
  }
}

void DisplayTime() {
  lcd.setCursor(0, 1);
  lcd.print(delay_time);
  lcd.print(" sec ");
}

void CheckMotionSensor() {
  if (digitalRead(SENSOR) == HIGH && !led_on) {
    led_on = true;
    digitalWrite(DIODE, HIGH);
    led_timer = millis();
  }
}

void ManageLED() {
  if (led_on && (millis() - led_timer >= delay_time * 1000)) {
    digitalWrite(DIODE, LOW);
    led_on = false;
  }
}

void setup() {
  pinMode(joystick_x, INPUT_PULLUP);
  pinMode(joystick_y, INPUT_PULLUP);
  pinMode(joystick_button, INPUT_PULLUP);
  pinMode(DIODE, OUTPUT);
  pinMode(SENSOR, INPUT);

  lcd.begin(16 , 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time:");
}

void loop() {
  CheckJoystickButton();
  ReadJoystick();
  DisplayTime();
  CheckMotionSensor();
  ManageLED();
}
