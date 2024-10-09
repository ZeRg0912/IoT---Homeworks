#include "WiFi.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

#define BUTTON_PIN          2
#define DELAY_BBUTTON       50
#define DELAY_GET_WEATHER   30000
#define SSID                "Wokwi-GUEST"
#define PASS                ""
#define MAX_PARAMETERS      3

LiquidCrystal_I2C lcd(0x27, 20, 4);

const String endpoint =    "http://api.openweathermap.org/data/2.5/weather?q=Moscow,ru,pt&APPID=";
const String key      =    "cdecb72a7903eb3bb1964c39615f1764";

struct WeatherInfo {
  String city         = "";
  String temperature  = "";
  String feels_like   = "";
  String humidity     = "";
};

WeatherInfo weather;
int current_parameter = 0;

volatile bool interrupt = false;
unsigned long timer_button = 0, timer_get_weather = -DELAY_GET_WEATHER;

void WiFiSetup() {
  lcd.clear();
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    lcd.setCursor(0, 0);
    lcd.print("Initializing WiFi...");
    delay(1000);
  }
  lcd.setCursor(0, 1);
  lcd.print("Setup done!");
  delay(1000);  
}

void GetWeatherParameters() {
  if (millis() - timer_get_weather >= DELAY_GET_WEATHER) {

    if ((WiFi.status() == WL_CONNECTED)) {
      HTTPClient http;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Receiving weather...");
      http.begin(endpoint + key);
      int httpCode = http.GET();

      if (httpCode > 0) {
        String message = http.getString();
        ReceiveMessage(message);
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Error HTTP-request");
        delay(1000);
      }

      http.end();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WEATHER in city:");
      lcd.setCursor(0, 1);
      lcd.print(weather.city);  
      WeatherParameterPrint(current_parameter);
      timer_get_weather = millis();
    }
  }  
}

void ReceiveMessage(String message) {
  StaticJsonDocument<1500> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("deserializeJson() failed: "));
    lcd.setCursor(0, 1);
    lcd.print(error.c_str());
    return;
  }

  weather.city        = String(doc["name"]);

  float temp = doc["main"]["temp"];
  temp -= 273,15;
  weather.temperature = "Temperature: ";
  weather.temperature += String(temp);
  weather.temperature += "C";

  float temp_feels_like = doc["main"]["feels_like"];
  temp_feels_like -= 273,15;
  weather.feels_like  = "Feels like: ";
  weather.feels_like  += String(temp_feels_like);
  weather.feels_like  += "C";

  weather.humidity    = "Humidity: ";
  weather.humidity    += String(doc["main"]["humidity"]);
  weather.humidity    += "%";
}

void WeatherParameterPrint(int parameter) {
  lcd.setCursor(0, 2);
  for (int i = 0; i < 20; i++) {
    lcd.print(" ");
  }
  lcd.setCursor(0, 2);
  switch(parameter) {
    case 0:
    lcd.print(weather.temperature);
    break;
    case 1:
    lcd.print(weather.feels_like);
    break;
    case 2:
    lcd.print(weather.humidity);
    break;
    default:
    lcd.print("Invalid parameter");
    break;
  }
  lcd.setCursor(0, 3);
  lcd.print("Click for next");
}

void BtnInterrupt() {
  if (millis() - timer_button >= DELAY_BBUTTON) {
    if (digitalRead(BUTTON_PIN) == HIGH) {
      interrupt = true;
    }
    timer_button = millis();
  }
}

void ChangeParameter() {
  if (interrupt && digitalRead(BUTTON_PIN) == LOW) {
    delay(25);
    if (interrupt && digitalRead(BUTTON_PIN) == LOW) {
      current_parameter++;
      if (current_parameter >= MAX_PARAMETERS || current_parameter < 0) current_parameter = 0;
      WeatherParameterPrint(current_parameter);
      interrupt = false;
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(BUTTON_PIN, BtnInterrupt, RISING);

  lcd.init();
  lcd.backlight();

  WiFiSetup();
  lcd.clear();
  GetWeatherParameters();
}

void loop() {
  GetWeatherParameters();
  ChangeParameter();
}