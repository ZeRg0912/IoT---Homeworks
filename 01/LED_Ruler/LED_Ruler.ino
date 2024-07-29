void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  for (size_t i = 4; i < 14; i++) {
    digitalWrite(i, HIGH);
  }
  
}

void loop() {
  for (size_t i = 4; i < 14; i++) {
    digitalWrite(i, LOW);
    delay(500);
  }

  for (size_t i = 13; i > 3; i--) {    
    digitalWrite(i, HIGH);
    delay(1000);
  }
}
