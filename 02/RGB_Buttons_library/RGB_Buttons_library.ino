#include "RGBDiode.h"
#include "Button.h"

// Пины и параметры
#define RED 6
#define GREEN 5
#define BLUE 3

#define RED_DOWN 8
#define RED_UP 9
#define GREEN_DOWN 10
#define GREEN_UP 11
#define BLUE_DOWN 12
#define BLUE_UP 13

#define STEP 50

// Объекты библиотек
RGBDiode RGB_diode(RED, GREEN, BLUE);
Button button_red_down(RED_DOWN, -STEP);
Button button_red_up(RED_UP, STEP);
Button button_green_down(GREEN_DOWN, -STEP);
Button button_green_up(GREEN_UP, STEP);
Button button_blue_down(BLUE_DOWN, -STEP);
Button button_blue_up(BLUE_UP, STEP);

// Яркости
int red_brightness = 250;
int green_brightness = 250;
int blue_brightness = 250;

// Последние состояния кнопок
int red_down_last = LOW;
int red_up_last = LOW;
int green_down_last = LOW;
int green_up_last = LOW;
int blue_down_last = LOW;
int blue_up_last = LOW;

void setup() {
  Serial.begin(115200);
  RGB_diode.begin();
  button_red_down.begin();
  button_red_up.begin();
  button_green_down.begin();
  button_green_up.begin();
  button_blue_down.begin();
  button_blue_up.begin();

  RGB_diode.SetBrightness(red_brightness, green_brightness, blue_brightness);
}

void loop() {
  if (button_red_down.Debounce(&red_brightness, &red_down_last) ||
      button_red_up.Debounce(&red_brightness, &red_up_last) ||
      button_green_down.Debounce(&green_brightness, &green_down_last) ||
      button_green_up.Debounce(&green_brightness, &green_up_last) ||
      button_blue_down.Debounce(&blue_brightness, &blue_down_last) ||
      button_blue_up.Debounce(&blue_brightness, &blue_up_last)) {
    RGB_diode.SetBrightness(red_brightness, green_brightness, blue_brightness);
  }
}
