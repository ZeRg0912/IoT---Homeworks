#include "fDigitsSegtPin.h" 

#define STOP A0
#define START A1

int start_last = LOW;
int stop_last = LOW;
bool running = false;
float deci_seconds = 0;
unsigned long last_millis = 0;  // Время последнего обновления таймера

fDigitsSegtPin Display(6, 5, 9, 4, 8, 13, 3, 12, 11, 7, 2, 10);

void setup() {
  Serial.begin(115200);
  Display.begin();
 
  pinMode(STOP, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
}

void StopButton() {
  if (!running) {
    int current_state = digitalRead(STOP);
    if (stop_last != current_state) {
      delay(50);
      current_state = digitalRead(STOP);
      if (stop_last == HIGH && current_state == LOW) {
        deci_seconds = 0;
        last_millis = millis();
      }
    }
    stop_last = current_state;
  }
}

void StartButton() {
  int current_state = digitalRead(START);
  if (start_last != current_state) {
    delay(50);
    current_state = digitalRead(START);
    if (start_last == HIGH && current_state == LOW) {
      running = !running;
      if (running) {
        last_millis = millis();
      }
    }
  }
  start_last = current_state;
}

void Timer() {
  if (running) {
    unsigned long current = millis();
    if (current - last_millis >= 100) {
      last_millis += 100;
      deci_seconds += 0.1;
      if (deci_seconds >= 1000) {
        deci_seconds = 0;
      }
    }
  }

  Display.print(deci_seconds);
}

void loop() {
  StopButton();
  StartButton();
  Timer();
}