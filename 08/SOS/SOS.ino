#include <TimerOne.h>

#define LED_PIN     13
#define BUTTON_PIN  2
#define DOT         200000
#define DASH        600000
#define SOS_BLINKS  9

int led_state = LOW;
volatile unsigned int SOS_count = 0;
volatile bool button_state = false;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  attachInterrupt(0, Button, RISING);

  Timer1.initialize(DOT);
  Timer1.attachInterrupt(SOS);
  Timer1.stop();
}

void Button() {
  if (!button_state) {
    button_state = true;
    Timer1.start();
  }
}

void SOS() {
  if (SOS_count < (((SOS_BLINKS * 2) / 3) - 1) || SOS_count > ((SOS_BLINKS * 2) - ((SOS_BLINKS * 2) / 3) - 1))  Timer1.setPeriod(DOT);
  else                                                                                        Timer1.setPeriod(DASH);

  if (SOS_count < (SOS_BLINKS * 2)) {
    if (led_state == LOW) {
      led_state = HIGH;
    } else {
      led_state = LOW;
    }

    digitalWrite(LED_PIN, led_state);  
    SOS_count++;
  } else if (SOS_count >= (SOS_BLINKS * 2)) {
    digitalWrite(LED_PIN, LOW); 
    button_state = false;
    Timer1.stop();
    SOS_count = 0;
  }
}

void loop() {
  
}
