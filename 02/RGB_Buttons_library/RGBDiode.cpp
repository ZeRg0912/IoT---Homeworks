#include "RGBDiode.h"

RGBDiode::RGBDiode(int red_pin_, int green_pin_, int blue_pin_) : red_pin(red_pin_), green_pin(green_pin_), blue_pin(blue_pin_) {}

void RGBDiode::begin() {
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
}

void RGBDiode::SetBrightness(int red, int green, int blue) {
  analogWrite(red_pin, constrain(red, 0, 255));
  analogWrite(green_pin, constrain(green, 0, 255));
  analogWrite(blue_pin, constrain(blue, 0, 255));
}
