#include <Stepper.h>

#define LED           13
#define ON_OFF        2
#define DIR           3
#define Ap            6
#define Am            7
#define Bp            5
#define Bm            4
#define DELAY         25

Stepper stepper(200, Bm, Bp, Ap, Am);

volatile bool run = false;
volatile bool dir = false;
volatile int step = 0;

void Dir() {
  if (dir) step = 1;
  else step = -1; 
  dir = !dir;
}

void On_Off() {
  run = !run;
  if (run) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
}

void Stepper() {
  if (run) stepper.step(step);
}

void setup() {
  pinMode(Ap, OUTPUT);
  pinMode(Am, OUTPUT);
  pinMode(Bp, OUTPUT);
  pinMode(Bm, OUTPUT);
  pinMode(LED, OUTPUT);

  pinMode(ON_OFF, INPUT);
  pinMode(DIR, INPUT);
  attachInterrupt(0, On_Off, RISING);
  attachInterrupt(1, Dir, RISING);

  stepper.setSpeed(50);
}

void loop() {
  Stepper();
}
