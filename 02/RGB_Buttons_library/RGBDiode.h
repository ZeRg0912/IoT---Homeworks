#ifndef RGBDIODE_H
#define RGBDIODE_H

#include <Arduino.h>

class RGBDiode {
public:
  RGBDiode(int red_pin_, int green_pin_, int blue_pin_);
  void begin();
  void SetBrightness(int red, int green, int blue);

private:
  int red_pin;
  int green_pin;
  int blue_pin;
};

#endif //RGBDIODE_H