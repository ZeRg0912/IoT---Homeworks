#define PIN A0

#define COUNT 10

int num_readings[COUNT];
int index = 0;
int result = 0;
double avg = 0;
int angle = 0;

void setup() {
  pinMode(PIN, INPUT);
  Serial.begin(115200);
  for (int thisReading = 0; thisReading < COUNT; thisReading++) {
    num_readings[thisReading] = 0;
  }
}

void Filter() {
  result = result - num_readings[index];
  num_readings[index] = analogRead(PIN);
  result = result + num_readings[index];
  index += 1;

  if (index >= COUNT) {
    index = 0;
  }

  avg = result / COUNT;
  delay(100);
}

void Angle() {
  Filter();
  if (avg <= 511.5) angle = map(avg, 0, 511.5, -135, 0);
  if (avg >= 511.5) angle = map(avg, 511.5, 1023, 0, 135);

  Serial.println("ANGLE: " + static_cast<String>(angle));
}

void loop() {
  Angle();
}
