#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
public:
  Button(int button_pin_, int step_);
  void begin();
  bool Debounce(int* brightness, int* last_state);

private:
  int button_pin;
  int step;
};

#endif //BUTTON_H
