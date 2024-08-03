#define RED 6                // Пин для красного светодиода
#define GREEN 5              // Пин для зелёного светодиода
#define BLUE 3               // Пин для синего светодиода

#define RED_DOWN 8           // Кнопка уменьшения яркости красного
#define RED_UP 9             // Кнопка увеличения яркости красного
#define GREEN_DOWN 10        // Кнопка уменьшения яркости зелёного
#define GREEN_UP 11          // Кнопка увеличения яркости зелёного
#define BLUE_DOWN 12         // Кнопка уменьшения яркости синего
#define BLUE_UP 13           // Кнопка увеличения яркости синего

#define STEP 50

int red_brightness = 250;     // Начальная яркость красного
int green_brightness = 250;   // Начальная яркость зелёного
int blue_brightness = 250;    // Начальная яркость синего

int red_down_last = LOW;
int red_up_last = LOW;
int green_down_last = LOW;
int green_up_last = LOW;
int blue_down_last = LOW;
int blue_up_last = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  pinMode(RED_DOWN, INPUT_PULLUP);
  pinMode(RED_UP, INPUT_PULLUP);
  pinMode(GREEN_DOWN, INPUT_PULLUP);
  pinMode(GREEN_UP, INPUT_PULLUP);
  pinMode(BLUE_DOWN, INPUT_PULLUP);
  pinMode(BLUE_UP, INPUT_PULLUP);

  analogWrite(RED, red_brightness);
  analogWrite(GREEN, green_brightness);
  analogWrite(BLUE, blue_brightness);
}

void loop() {
  Debounce(RED_DOWN, &red_brightness, -STEP, &red_down_last);
  Debounce(RED_UP,   &red_brightness,  STEP, &red_up_last);

  Debounce(GREEN_DOWN, &green_brightness, -STEP, &green_down_last);
  Debounce(GREEN_UP,   &green_brightness,  STEP, &green_up_last);

  Debounce(BLUE_DOWN, &blue_brightness, -STEP, &blue_down_last);
  Debounce(BLUE_UP,   &blue_brightness,  STEP, &blue_up_last);

  analogWrite(RED, red_brightness);
  analogWrite(GREEN, green_brightness);
  analogWrite(BLUE, blue_brightness);
}

void Debounce(int buttonPin, int* brightness, int step, int* last_state) {
  int current_state = digitalRead(buttonPin);
  if (*last_state != current_state) {
    delay(5);
    current_state = digitalRead(buttonPin);
    if (*last_state == HIGH && current_state == LOW) {
      *brightness = constrain(*brightness + step, 0, 250);
    }
  }
  *last_state = current_state;
}