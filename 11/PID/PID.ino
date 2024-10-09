//подключение библиотеки ПИД регулятора
#include "PID_v1.h"
// номера выводов
const int PWMPin = 3;
const int inputPin = -1;
const int setPointPin = A1;
const int setPointIndicator = 6;
const int inputIndicator = 5;
//Переменные для ПИД регулятора
double Setpoint, Input, Output;
//Параметры ПИД и ПИ регулятора
//double Kp = 5, Ki = 0.015, Kd = 0; // PI
double Kp = 2.5, Ki = 0.01, Kd = 3; // PID
//Объект ПИД регулятора
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, P_ON_E, DIRECT);

void setup() {
  Serial.begin(115200);
  myPID.SetOutputLimits(-4, 255); //диапазон выхода
  //индикаторы для отладки
  if (setPointIndicator >= 0) pinMode(setPointIndicator, OUTPUT);
  if (inputIndicator >= 0) pinMode(inputIndicator, OUTPUT);
  Setpoint = 0; //начальное значение уставки - ноль
  myPID.SetMode(AUTOMATIC); //включение регулятора
  if (inputPin > 0) //выбор источника входного сигнала
  {
    Input = analogRead(inputPin);
  } else {
    Input = simPlant(0.0, 1.0); //внутренняя модель входного сигнала
  }
  Serial.println("Setpoint Input Output Watts");
}

void loop() {
  float heaterWatts = (int)Output * 20.0 / 255; //мощность нагревателя для модели
  if (inputPin > 0 )
  {
    Input = analogRead(inputPin);
  } else
  {
    Input = simPlant(heaterWatts, Output > 0 ? 1.0 : 1 - Output);
    //моделирование нагрева
  }
  if (myPID.Compute()) //ПИД регулятор
  {
    analogWrite(PWMPin, (int)Output); //выход на нагреватель
    Setpoint = analogRead(setPointPin) / 4; // чтение уставки температуры (от 0 до 255)
    if (inputIndicator >= 0) analogWrite(inputIndicator, Input); // для отладки
    if (setPointIndicator >= 0) analogWrite(setPointIndicator, Setpoint);
  }
  report(); //вывод отладочных данных в com порт
}
/*Функция вывода результата работы ПИД-регулятора*/
void report(void)
{
  static uint32_t last = 0;
  const int interval = 1000; //вывод раз в секунду
  if (millis() - last > interval)
  {
    last += interval;
    Serial.print("SP:");
    Serial.print(Setpoint);
    Serial.print(" PV:");
    Serial.print(Input);
    Serial.print(" CV:");
    Serial.print(Output);
    Serial.print(' ');
    Serial.println();
  }
}

/*Функция модели нагрева
  Q - мощность [Вт],
  hfactor - относительный коэффициент теплопроводности*/
float simPlant(float Q, float hfactor)
{
  //Имитация алюминиевого блока размером 1x1x2 см с нагревателем и пассивным охлаждением
  float h = 5 * hfactor ; // Вт/м2K коэффициент конвекции
  float Cps = 0.89; // теплоемкость Дж/грамм°C
  float area = 1e-4; // площадь конвекции, м2
  float mass = 1 ; // масса, граммы
  float Tamb = 25; // температура окружающей среды °C
  static float T = Tamb; // текущая температура °C
  static uint32_t last = 0; // время для моделирования
  uint32_t interval = 100; // период обновления данных, мс
  if (millis() - last >= interval)
  {
    last += interval;
    T = T + Q * interval / 1000 / mass / Cps - (T - Tamb) * area * h;
  }
  return T;
}