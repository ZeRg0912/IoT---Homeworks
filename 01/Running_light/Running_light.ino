int temp_delay = 2000;

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
}

void loop() {
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 4; j < 14; j++) {
        digitalWrite(j, HIGH);
        if (j > 4) digitalWrite(j - 1, LOW);
        delay(temp_delay);
        if (j == 13) digitalWrite(13, LOW);
    }
    temp_delay = temp_delay / 2;
  }
  temp_delay = 2000;  
}
