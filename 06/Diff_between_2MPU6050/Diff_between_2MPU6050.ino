#include <LiquidCrystal_I2C.h>
#include <MPU6050.h>

#define COUNT 10
#define FIRST 3
#define SECOND 2

LiquidCrystal_I2C lcd(0x27,16,2);
MPU6050 mpu(0x68);

float ax, ay, az, rx, ry, rz;
unsigned long timer_mpu = 0;
bool selected = false;

void setup() {
  Serial.begin(115200);
  pinMode(FIRST, OUTPUT);
  pinMode(SECOND, OUTPUT);

  lcd.init();    
  lcd.backlight();  
  mpu.initialize();  
  lcd.clear();
}

void LCDClearOlder(float value) {
  int temp = value;
  int zeroes = 3;
  while (temp > 0) {
    zeroes--;
    temp /= 10;
  }
  Serial.println(zeroes);
  for (int i = 0; i < zeroes; i++) lcd.print(" ");
}

void LCDPrintInfo() {
  lcd.setCursor(0, 0);
  lcd.print(ax, 2);
  lcd.setCursor(0, 1);
  lcd.print(rx, 0);
  LCDClearOlder(rx);
  
  lcd.setCursor(6, 0);
  lcd.print(ay, 2);
  lcd.setCursor(6, 1);
  lcd.print(ry, 0);
  LCDClearOlder(ry);

  lcd.setCursor(12, 0);
  lcd.print(az, 2);
  lcd.setCursor(12, 1);
  lcd.print(rz, 0);
  LCDClearOlder(rz);
}

void ReadMPU1() {  
  ax = mpu.getAccelerationX();
  ay = mpu.getAccelerationY();
  az = mpu.getAccelerationZ();
  
  rx = mpu.getRotationX();
  ry = mpu.getRotationY();
  rz = mpu.getRotationZ();
}

void DiffMPU2() {
  ax -= mpu.getAccelerationX();
  ay -= mpu.getAccelerationY();
  az -= mpu.getAccelerationZ();
  
  rx -= mpu.getRotationX();
  ry -= mpu.getRotationY();
  rz -= mpu.getRotationZ();
}

void DataTransform() {  
  ax = abs(ax) / 32768 * 2;
  ay = abs(ay) / 32768 * 2;
  az = abs(az) / 32768 * 2;
  rx = abs(rx) / 32768 * 250;
  ry = abs(ry) / 32768 * 250;
  rz = abs(rz) / 32768 * 250;
}

void ChangeMPU() {
  digitalWrite(FIRST, selected);
  digitalWrite(SECOND, !selected);
  selected = !selected;
}

void DataFromMPUs() {
  if (millis() - timer_mpu >= 50) {
    ChangeMPU();
    ReadMPU1();
    ChangeMPU();
    DiffMPU2();
    DataTransform();
    LCDPrintInfo();
    timer_mpu = millis();
  }
}

void loop() {
  DataFromMPUs();
}
