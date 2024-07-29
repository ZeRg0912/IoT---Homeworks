#define BLUE 2
#define GREEN 3
#define RED 4

void setup() {
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
}

void loop() {
  // RED
  delay(1000);
  digitalWrite(RED, HIGH);

  // GREEN
  delay(1000);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);

  // BLUE
  delay(1000);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);

  // LIGHT BLUE
  delay(1000);
  digitalWrite(GREEN, HIGH);

  // PINK
  delay(1000);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);

  // YELLOW
  delay(1000);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, HIGH);

  // WHITE
  delay(1000);
  digitalWrite(BLUE, HIGH);

  // OFF
  delay(1000);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}
