#include <Servo.h>

Servo servo;

#define TRIG 13
#define ECHO 12
#define SERVO 9

#define DELAY_ULTRASONIC 10

float distance_cm;
unsigned long timer_ultrasonic = 0;

void ReadUltrasonicDistance() {  
  if (millis() - timer_ultrasonic >= DELAY_ULTRASONIC) {
    pinMode(TRIG, OUTPUT);
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    pinMode(ECHO, INPUT);
    distance_cm = (pulseIn(ECHO, HIGH) / 58);
    timer_ultrasonic = millis();
  }
}

void SetServo(){
  servo.write(map(distance_cm, 0, 400, 180, 0));
}

void setup() {
  servo.attach(SERVO);
}

void loop() {
  ReadUltrasonicDistance();
  SetServo();
}
