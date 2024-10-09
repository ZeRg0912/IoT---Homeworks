#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define IR_PIN      3
#define SERVO_PIN   9

LiquidCrystal_I2C lcd(0x27,16,2);
Servo servo;

String angle = "";
bool play_servo = false;

void setup() {
  Serial.begin(115200);

  lcd.init();    
  lcd.backlight();
  servo.attach(SERVO_PIN);
  servo.write(0);
  delay(100);
  servo.detach();
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  LCDSetText();
}

void LCDSetText() {
  lcd.setCursor(0, 0);
  lcd.print("Set angle:");
  lcd.setCursor(0, 1);
  lcd.print('0');
}

void IRdecode() {
  switch (IrReceiver.decodedIRData.command) {    
      case 104:
        angle += '0';
        break;
      case 48:
        angle += '1';
        break;
      case 24:
        angle += '2';
        break;
      case 122:
        angle += '3';
        break;
      case 16:
        angle += '4';
        break;
      case 56:
        angle += '5';
        break;
      case 90:
        angle += '6';
        break;
      case 66:
        angle += '7';
        break;
      case 74:
        angle += '8';
        break;
      case 82:
        angle += '9';
        break;
      case 176:
        angle.remove(angle.length() - 1);
        lcd.setCursor(angle.length(), 1);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        break;
      case 168:
        play_servo = true;
        break;
      }
}

void IRget() {
  if (!play_servo) {
    if (IrReceiver.decode()) {
      
      lcd.setCursor(0, 1);
      IRdecode();

      if (angle.toInt() > 180 || angle.toInt() < 0) {
        lcd.setCursor(0, 1);
        lcd.print("Wrong angle!");
        delay(1500);
        ClearAngle();
      } else if (angle == "") lcd.print("0");
      else lcd.print(angle);

      if (play_servo) ServoControl();
      IrReceiver.resume();
    }
  }
}

void ClearAngle() {  
  angle = "";
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.print(" ");
  }
  lcd.setCursor(0, 1);
  lcd.print('0');
}

void ServoControl() {
  servo.attach(SERVO_PIN);
  servo.write(angle.toInt());
  delay(100);
  servo.detach();
  ClearAngle();
  play_servo = false;
}

void loop() {
  IRget();
}