#define joystick_x A0
#define joystick_y A1
#define joystick_button 13

#define debounce 100

const int led_pins[] = {11, 10, 9, 6, 5, 3};
const int leds_num = sizeof(led_pins) / sizeof(led_pins[0]);

int active = 0;
int brightness = 0;

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < leds_num; i++) {
    pinMode(led_pins[i], OUTPUT);
  }

  pinMode(joystick_x, INPUT_PULLUP);
  pinMode(joystick_y, INPUT_PULLUP);
  pinMode(joystick_button, INPUT_PULLUP);
}

void CheckButton() {
  if (digitalRead(joystick_button) == LOW) {
    delay(debounce);
    if (digitalRead(joystick_button) == LOW) {
      active = 0;
    }
  }
}

void JoystickRead() {
  int xValue = analogRead(joystick_x);
  int yValue = analogRead(joystick_y);

  if (xValue < (512 - debounce)) {
    active = min(active + 1, leds_num - 1);
  } else if (xValue > (512 + debounce)) {
    active = max(active - 1, 0);
  }

  if (yValue < (512 - debounce)) {
    brightness = max(brightness - 10, 0);
  } else if (yValue > (512 + debounce)) {
    brightness = min(brightness + 10, 250);
  }
}

void UpdateLeds() {
  for (int i = 0; i < leds_num; i++) {
    if (i == active) {
      analogWrite(led_pins[i], brightness);
    } else {
      analogWrite(led_pins[i], 0);
    }
  }
}

void loop() {
  JoystickRead();
  CheckButton();
  UpdateLeds();
  delay(debounce);
}