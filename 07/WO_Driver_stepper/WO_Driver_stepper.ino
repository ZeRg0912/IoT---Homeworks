#include <Stepper.h>

#define POTENCIOMETER A5
#define LED           13
#define ON_OFF        11
#define LEFT          10
#define RIGHT         9
#define Ap            6
#define Am            7
#define Bp            5
#define Bm            4
#define DELAY         25

Stepper stepper(200, Bm, Bp, Ap, Am);

bool run = false;
unsigned long on_off_timer = 0, left_timer = 0, right_timer = 0;
int on_off_last = LOW, left_last = LOW, right_last = LOW;
int step = 0;

void Debounce(int button, unsigned long &timer, int &last) {  
  int current = digitalRead(button);
  if (last != current) {
    if (millis() - timer >= DELAY) {
      current = digitalRead(button);
      if (current == HIGH && last == LOW) {
        switch (button) {
          case ON_OFF: On_Off(); break;
          case LEFT: Left(); break;
          case RIGHT: Right(); break;
        }
      }
      timer = millis();
    }
  }
  last = current;
}

void Left() {
  step = -1;
}

void Right() {
  step = 1;
}

void On_Off() {
  run = !run;
  if (run) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
}

void SetSpeed() {
  int raw_speed = analogRead(POTENCIOMETER);
  stepper.setSpeed(map(raw_speed, 0, 1024, 1, 100));
}

void Run() {
  if (run) stepper.step(step);
}

void Stepper() {
  SetSpeed();
  Debounce(ON_OFF, on_off_timer, on_off_last);
  Debounce(LEFT, left_timer, left_last);
  Debounce(RIGHT, right_timer, right_last);
  Run();
}

void setup() {
  pinMode(Ap, OUTPUT);
  pinMode(Am, OUTPUT);
  pinMode(Bp, OUTPUT);
  pinMode(Bm, OUTPUT);
  pinMode(LED, OUTPUT);

  pinMode(ON_OFF, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(POTENCIOMETER, INPUT);

}

void loop() {
  Stepper();
}
