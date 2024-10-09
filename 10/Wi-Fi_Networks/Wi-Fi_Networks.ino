#include "WiFi.h"
#include <LiquidCrystal_I2C.h>

#define BUTTON_PIN  2
#define DELAY       50

LiquidCrystal_I2C lcd(0x27,20,4);

struct WiFi_info {
  int     num   = 0;
  String  SSID  = "Name: ";
  String  RSSI  = "Power: ";
};

int num_WiFi = 0;
int current_network = -1;
volatile bool interrupt = false;
unsigned long timer_button = 0;
std::vector<WiFi_info> networks;


void WiFiSetup() {  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing WiFi...");
  WiFi.mode(WIFI_STA);  
  lcd.setCursor(0, 1);
  lcd.print("Setup done!");
  delay(1000);
}

void WiFiScanNetworks() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning WiFis...");
  num_WiFi = WiFi.scanNetworks();
  WiFiGetInfo();
  lcd.setCursor(0, 1);
  lcd.print("Done!");
  lcd.setCursor(0, 2);
  lcd.print("Founded: " + String(num_WiFi));
  lcd.setCursor(0, 3);
  lcd.print("Click button to info");
}

void WiFiGetInfo() {
  for (int i = 0; i < num_WiFi; i++) {
    WiFi_info network;
    network.num   = i + 1;
    network.SSID += WiFi.SSID(i);
    network.RSSI += WiFi.RSSI(i);
    networks.push_back(network);
  }
}

void WiFiPrintInfo(int network_num) {
  if (network_num >= 0 && network_num < networks.size()) {
    lcd.clear();  
    lcd.setCursor(0, 0);
    lcd.print("Network #" + String(networks[network_num].num));
    lcd.setCursor(0, 1);
    lcd.print(networks[network_num].SSID);
    lcd.setCursor(0, 2);
    lcd.print(networks[network_num].RSSI);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Invalid network num");
  }
}

void BtnInterrupt() {
  if (millis() - timer_button >= DELAY) {
    if (digitalRead(BUTTON_PIN) == HIGH) {
      interrupt = true;
    }
    timer_button = millis();
  }
}

void ChangeNetwork() {  
  if (interrupt && digitalRead(BUTTON_PIN) == LOW) {
    delay(25);
    if (interrupt && digitalRead(BUTTON_PIN) == LOW) {
      current_network++;
      if (current_network >= num_WiFi || current_network < 0) current_network = 0;
      WiFiPrintInfo(current_network);
      interrupt = false;
    }
  }
}

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(BUTTON_PIN, BtnInterrupt, RISING);

  lcd.init();    
  lcd.backlight();

  WiFiSetup();
  WiFiScanNetworks();  
}

void loop() {
  ChangeNetwork();
}