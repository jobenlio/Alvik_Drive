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
  static char start = 1;
  if(start = 1)
  {
    start = 0;
    for (int i = 0; i<100; i++)
    {
      alvik.drive(12, 20);
      savedrive();
      Serial.println("Drive saved");
    }
    for(int i = 0; i<100; i++)
    {
      alvik.drive(sValues[i][0], sValues[i][1]);
    }
  }

}

void savedrive(){
  static char sSaveIndex = 0;
  alvik.get_drive_speed(sValues[sSaveIndex][0], sValues[sSaveIndex][1]);
  sValues[sSaveIndex][0] = sValues[sSaveIndex][0] / 10;   // correcting fals get of 10x more than in drive given value
  sValues[sSaveIndex][1] = -1 * sValues[sSaveIndex][1];   // changing direction 
  sSaveIndex++;
}

