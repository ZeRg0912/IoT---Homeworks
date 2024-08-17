#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define joystick_x A4
#define joystick_y A5
#define joystick_button A3

#define MIN_SYMBOL 65
#define MAX_SYMBOL 90
#define MIN_COL 0
#define MAX_COL 15
#define DEAD_ZONE 20
#define DELAY 100

bool row = 0;
int column = 0;
char ASCII = 0;

unsigned long timer_x = 0, timer_y = 0, timer_button = 0;
char lcd_buffer[2][16];

void setup() {
  pinMode(joystick_x, INPUT_PULLUP);
  pinMode(joystick_y, INPUT_PULLUP);
  pinMode(joystick_button, INPUT_PULLUP);

  lcd.begin(16 , 2);
  lcd.clear();
  lcd.cursor();
  ClearBuffer();
  lcd.setCursor(column, row);
}

void ClearBuffer(){
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 16; j++) {
      lcd_buffer[i][j] = ' ';
    }
  }
}

void CheckJoystickButton() {
  if (digitalRead(joystick_button) == LOW){
    if (millis() - timer_button >= DELAY) {
      if (digitalRead(joystick_button) == LOW) {
        row = !row;
        ASCII = lcd_buffer[row][column];
        lcd.setCursor(column, row);
        timer_button = millis();
      }
    }
  }
}

void XStep() {
  int X = analogRead(joystick_x);
  if (X < 512 - DEAD_ZONE || X > 512 + DEAD_ZONE) {
    if (millis() - timer_x >= DELAY) {
      if (X < 512 - DEAD_ZONE || X > 512 + DEAD_ZONE) {
        if (X < (512 - DEAD_ZONE)) {
          column += 1;
        } else if (X > (512 + DEAD_ZONE)) {
          column -= 1;
        }
        if (column < MIN_COL) column = MIN_COL;
        if (column > MAX_COL) column = MAX_COL;
        ASCII = lcd_buffer[row][column];
        lcd.setCursor(column, row);
        timer_x = millis();
      }
    }
  }      
}

void YStep() {
  int Y = analogRead(joystick_y);
  if (Y < 512 - DEAD_ZONE || Y > 512 + DEAD_ZONE) {
    if (millis() - timer_y >= DELAY) {
      if (Y < 512 - DEAD_ZONE || Y > 512 + DEAD_ZONE) {
        if (Y > (512 + DEAD_ZONE)) {
          if (ASCII == ' ') ASCII = MIN_SYMBOL;
          else ASCII += 1;
        } else if (Y < (512 - DEAD_ZONE)) {
          ASCII -= 1;
        }
        if (ASCII < MIN_SYMBOL) ASCII = ' ';
        if (ASCII > MAX_SYMBOL) ASCII = MAX_SYMBOL;
        lcd_buffer[row][column] = ASCII;
        lcd.print(ASCII);
        lcd.setCursor(column, row);
        timer_y = millis();
      }
    }
  }
}

void ControlLCD() {
  CheckJoystickButton();
  XStep();
  YStep();  
}

void loop() {
  ControlLCD();
}
