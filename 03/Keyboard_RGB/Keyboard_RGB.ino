#include "Keypad.h"

#define RED 5
#define GREEN 4
#define BLUE 3

const byte rows = 4;
const byte cols = 4;
char keymap[rows][cols] =
{
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'},
 {'*', '0', '#','D'}
};

byte rows_pins[rows]= { 13, 12, 11, 10 };
byte cols_pins[cols]= { 9, 8, 7, 6 };

Keypad keypad = Keypad(makeKeymap(keymap), rows_pins, cols_pins, rows, cols);

bool red_state = true;
bool green_state = true;
bool blue_state = true;
bool is_on = false;

unsigned long previousMillis = 0;
int interval = 1000;
bool blinking = false;


void setup() {
  Serial.begin(115200);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
}

void SelectColor(char color) {
  switch(color) {
    case '1': 
              red_state = false;
              green_state = true;
              blue_state = true;
              Serial.println("RED");
    break;   

    case '2': 
              red_state = true;
              green_state = false;
              blue_state = true;
              Serial.println("GREEN");
    break;

    case '3':
              red_state = true;
              green_state = true;
              blue_state = false;
              Serial.println("BLUE");
    break;

    case '4': 
              red_state = true;
              green_state = false;
              blue_state = false;
              Serial.println("LIGHT BLUE");
    break;

    case '5': 
              red_state = false;
              green_state = true;
              blue_state = false;
              Serial.println("PINK");
    break;

    case '6':
              red_state = false;
              green_state = false;
              blue_state = true;
              Serial.println("YELLOW");
    break;

    case '7': 
              red_state = false;
              green_state = false;
              blue_state = false;
              Serial.println("WHITE");
    break;

    case '0':
              red_state = true;
              green_state = true;
              blue_state = true;
            Serial.println("OFF");
    break;
  }
}

void SelectMode(char mode) {
  switch(mode) {
    case 'A':
              blinking = false;
              interval = 0;
              Serial.println("Mode A: ON");
    break;

    case 'B':
              blinking = true;
              interval = 1000;
              Serial.println("Mode B: Blink 1s");
    break;

    case 'C':
              blinking = true;
              interval = 500;
              Serial.println("Mode C: Blink 0.5s");
    break;

    case 'D':
              blinking = true;
              interval = 250;
              Serial.println("Mode D: Blink 0.25s");
    break;
  }
}

void ApplyColor() {
  digitalWrite(RED, red_state ? HIGH : LOW);
  digitalWrite(GREEN, green_state ? HIGH : LOW);
  digitalWrite(BLUE, blue_state ? HIGH : LOW);
}

void Blinking() {  
  unsigned long currentMillis = millis();

  if (blinking) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
      if (is_on) {
        ApplyColor();
      }
      else {        
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, HIGH);
        digitalWrite(BLUE, HIGH);
      }
      is_on = !is_on;
    }
  } else {
    ApplyColor();
  }
}

void CheckKey(char key) {
  SelectColor(key);
  SelectMode(key);
}

void loop() {
  char keypressed = keypad.getKey();

  if (keypressed != NO_KEY) {
    CheckKey(keypressed);
  } 

  Blinking();
}
