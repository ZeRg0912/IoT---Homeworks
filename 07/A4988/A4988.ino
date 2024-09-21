#include "A4988.h"

#define DIR_PIN 2
#define STEP_PIN 3
#define STEPS_REVOLUTION 200

A4988 driver(DIR_PIN, STEP_PIN, STEPS_REVOLUTION);

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
}

void TestDriver(){  
  driver.SetSpeed(50);
  driver.Move(-200);
  delay(2000);
  driver.SetSpeed(9000);
  driver.Move(200);
  delay(2000);
}

void loop() {
  TestDriver();
}