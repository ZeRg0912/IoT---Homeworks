#include <SD.h>
#include <Stepper.h>

#define Ap            6
#define Am            7
#define Bp            5
#define Bm            4
#define CS            10

#define FILE_NAME     "Stepper.txt"

Stepper stepper(200, Bm, Bp, Ap, Am);
int speed = 50;

int steps = 0, dir = 0, pause = 100, step = 1;


void setup() {
  Serial.begin(115200);
  stepper.setSpeed(speed);
  SDCardInit();
}

void loop() {
  SDCardRead();
  delay(2000);
}

void SDCardInit() {
  Serial.println("Initializing SD card... ");
  if (!SD.begin(CS)) {
    Serial.println("Card initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");  
}

void SDCardRead() {
  File file = SD.open(FILE_NAME);
  if (file) {
    while (file.available()) {
      String line = file.readStringUntil(' '); 
      steps = line.toInt();
      line = file.readStringUntil(' ');  
      dir = line.toInt();
      line = file.readStringUntil('\n');  
      pause = line.toInt();      
      String    stepper_line =   "Steps = ";
                stepper_line +=  steps;
                stepper_line +=  ";\tDirection = ";
      if (dir)  stepper_line +=  "Сounterclockwise;\t";
      else      stepper_line +=  "Clockwise;\t\t";
                stepper_line +=  "Pause time = ";
                stepper_line +=  pause;
                stepper_line +=  "ms";
      Serial.println(stepper_line);
      Stepper();
    }  
    file.close();
  } else {
    String error = "Error opening ";
    error += FILE_NAME;
    error += "!";
    Serial.println(error);
  }
}

void Stepper() {
  if (!dir) {
    for (int i = 0; i < steps; i++) {
      stepper.step(step);
    }
  } else {
    for (int i = 0; i < steps; i++) {
      stepper.step(-step);
    }
  }  
  delay(pause);
}