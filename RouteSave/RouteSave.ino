#include "Arduino_Alvik.h"
static Arduino_Alvik alvik;

void randomDrive();
void savedrive();

float sValues[100][2];

void setup(){
  Serial.begin(115200);
  alvik.begin();
}

void loop(){
  alvik.drive(12, 20);
  savedrive();
  Serial.println("Drive saved");
}

void savedrive(){
  static char sSaveIndex = 0;
  alvik.get_drive_speed(sValues[sSaveIndex][0], sValues[sSaveIndex][1]);

  sValues[sSaveIndex][1] = -1 * sValues[sSaveIndex][1];
  sSaveIndex++;
}

