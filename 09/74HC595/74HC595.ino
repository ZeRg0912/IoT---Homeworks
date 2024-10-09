#include <SPI.h>

#define LATCH_PIN   9
#define BUTTON_PIN  2

#define NUM_SHIFT_REGS  2

#define SPEED_DECREASE  150
#define INITIAL_SPEED   900
#define DELAY           50

uint16_t num_leds = 0x8000;

const int reg_pins = NUM_SHIFT_REGS * 8;
bool registers[reg_pins];
volatile int speed = INITIAL_SPEED;

volatile bool Interrupt = false;
unsigned long timer_button = 0, timer_leds = 0;

void BtnInterrupt() {
  if (millis() - timer_button >= DELAY) {
    if (digitalRead(BUTTON_PIN) == HIGH) {
      Interrupt = true;
    }
    timer_button = millis();
  }
}

void ChangeMode() {  
  if (Interrupt && digitalRead(BUTTON_PIN) == LOW) {
    delay(25);
    if (Interrupt && digitalRead(BUTTON_PIN) == LOW) {
      Serial.println("Clicked");
      speed -= SPEED_DECREASE;
      if (speed <= 0) speed = INITIAL_SPEED;
      Interrupt = false;
    }
  }
}

void RunningLEDS() {
  if (millis() - timer_leds >= speed) {
    SPI.transfer(num_leds >> 8);
    SPI.transfer(num_leds);
    digitalWrite(LATCH_PIN, HIGH);
    digitalWrite(LATCH_PIN, LOW);
    RotateRight(num_leds);
    timer_leds = millis();
  }
}

void ClearRegs() {
  digitalWrite(LATCH_PIN, LOW);
  SPI.transfer(0);
  SPI.transfer(0);
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}

void SetRegPin(int index, int value) {
  registers[index] = value;
}

void RotateRight(uint16_t &bits) {
  uint16_t low_bit = bits & 1;
  bits = (bits >> 1) | (low_bit << 15);
}

void setup() {
  Serial.begin(115200);
  SPI.begin();

  pinMode(LATCH_PIN, OUTPUT);

  attachInterrupt(0, BtnInterrupt, RISING);

  ClearRegs();
}

void loop() {
  RunningLEDS();
  ChangeMode();
}