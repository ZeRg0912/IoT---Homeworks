#include <LiquidCrystal_I2C.h>
#include <MPU6050.h>

#define COUNT 10

LiquidCrystal_I2C lcd(0x27,16,2);
MPU6050 mpu(0x68);

float ax, ay, az;
unsigned long timer_accelerometer = 0;
float buffer_ax[COUNT] = {0}, buffer_ay[COUNT] = {0}, buffer_az[COUNT] = {0};
int index = 0;

void setup() {  
  //Serial.begin(115200);
  lcd.init();    
  lcd.backlight();
  
  mpu.initialize();  
  LCDSetText();
}

void LCDSetText() {
  lcd.clear();  
  lcd.setCursor(0, 0);
  lcd.print("AX:");
  lcd.setCursor(8, 0);
  lcd.print("AY:");
  lcd.setCursor(0, 1);
  lcd.print("AZ:");
}

void LCDPrintAcceleration() {
  //Serial.println("AX = " + String(ax) + " AY = " + String(ay) + " AZ = " + String(az));
  lcd.setCursor(3, 0);
  lcd.print(ax);
  if (ax >= 0) lcd.print(" ");
  lcd.setCursor(11, 0);
  lcd.print(ay);
  if (ay >= 0) lcd.print(" ");
  lcd.setCursor(3, 1);
  lcd.print(az);
  if (az >= 0) lcd.print(" ");
}

void AccelerometerFilter() {
  if (millis() - timer_accelerometer >= 100) {
    buffer_ax[index] = mpu.getAccelerationX();
    buffer_ay[index] = mpu.getAccelerationY();
    buffer_az[index] = mpu.getAccelerationZ();
    for (int i = 0; i < COUNT; i++) {
      ax += buffer_ax[i];
      ay += buffer_ay[i];
      az += buffer_az[i];
    }
    index = (index + 1) % COUNT;
    timer_accelerometer = millis();
  } else {
    for (int i = 0; i < COUNT; i++) {
      ax += buffer_ax[i];
      ay += buffer_ay[i];
      az += buffer_az[i];
    }
  }      
  ax = (ax / COUNT) / 32768 * 2;
  ay = (ay / COUNT) / 32768 * 2;
  az = (az / COUNT) / 32768 * 2;
  LCDPrintAcceleration();
}


void loop() {  
  AccelerometerFilter();
}
