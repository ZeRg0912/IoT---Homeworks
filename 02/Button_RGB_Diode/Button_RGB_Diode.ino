#define BLUE 4 
#define GREEN 5 
#define RED 6 
#define BUTTON 7 

int mode = 0;
int button_current = LOW;
int button_last = LOW;

void SwitchMode(int mode) {
  Serial.print("Current color: ");
  switch(mode) {
    case 0: digitalWrite(RED, LOW);
            Serial.println("RED");
            break;   

    case 1: digitalWrite(RED, HIGH);
            digitalWrite(GREEN, LOW);
            Serial.println("GREEN");
            break;

    case 2: digitalWrite(GREEN, HIGH);
            digitalWrite(BLUE, LOW);
            Serial.println("BLUE");
            break;

    case 3: digitalWrite(GREEN, LOW);
            Serial.println("LIGHT BLUE");
            break;

    case 4: digitalWrite(RED, LOW);
            digitalWrite(GREEN, HIGH);
            digitalWrite(BLUE, LOW);
            Serial.println("PINK");
            break;

    case 5: digitalWrite(BLUE, HIGH);
            digitalWrite(GREEN, LOW);
            Serial.println("YELLOW");
            break;

    case 6: digitalWrite(BLUE, LOW);
            Serial.println("WHITE");
            break;

    case 7:
            digitalWrite(RED, HIGH);
            digitalWrite(GREEN, HIGH);
            digitalWrite(BLUE, HIGH);
            Serial.println("OFF");
            break;
  }
}

int Debounce(int last) {
  int current = digitalRead(BUTTON);
  if (last != current) {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

void setup() {  
  Serial.begin(115200);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
}

void loop() {
  button_current = Debounce(button_last);
  if (button_last && !button_current) {
    Serial.println("The button is clicked");
    SwitchMode(mode);
    mode++;
  }  
  button_last = button_current;
  if (mode > 7) mode = 0;
}
