#define SEG_COUNT 7
#define BUTTON 13

const int firstSeg = 12;
int number = 0;  
int button_current = LOW;
int button_last = LOW;

byte numberSegments[16] = {
 0b11000000, // 0
 0b11111001, // 1
 0b10100100, // 2
 0b10110000, // 3
 0b10011001, // 4
 0b10010010, // 5
 0b10000010, // 6
 0b11111000, // 7
 0b10000000, // 8
 0b10010000, // 9
 0b10001000, // A
 0b10000011, // B
 0b11000110, // C
 0b10100001, // D
 0b10000110, // E
 0b10001110  // F
};

int Debounce(int last) {
  int current = digitalRead(BUTTON);
  if (last != current) {
    delay(50);
    current = digitalRead(BUTTON);
  }
  return current;
}

void setup() {

  pinMode(BUTTON, INPUT_PULLUP);

  for (int i = 0; i < SEG_COUNT; i++) {
    pinMode(firstSeg - i, OUTPUT);
  }
}


  
void loop() {  
  int mask;
  mask = numberSegments[number];

  for (int i = 0; i < SEG_COUNT; i++) {
    int enableSegment = bitRead(mask, i);
    digitalWrite(firstSeg - i, enableSegment);
  }

  button_current = Debounce(button_last);
  if (button_last && !button_current) {
    number = (number + 1) % 16;
  }  
  button_last = button_current;
}
