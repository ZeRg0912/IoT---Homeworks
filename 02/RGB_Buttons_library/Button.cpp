#include "Button.h"

Button::Button(int button_pin_, int step_) : button_pin(button_pin_), step(step_) {}

void Button::begin() {
  pinMode(button_pin, INPUT_PULLUP);
}

bool Button::Debounce(int* brightness, int* last_state) {
  int current_state = digitalRead(button_pin);
  if (*last_state != current_state) {
    delay(5);
    current_state = digitalRead(button_pin);
    if (*last_state == HIGH && current_state == LOW) {
      *brightness = constrain(*brightness + step, 0, 250);
      *last_state = current_state;
      return true;
    }
  }
  *last_state = current_state;
  return false;
}
