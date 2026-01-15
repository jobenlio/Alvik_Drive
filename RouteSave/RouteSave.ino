#include "Arduino_Alvik.h"
static Arduino_Alvik alvik;

void randomDrive();
void savedrive();


void setup(){
  Serial.begin(115200);
  alvik.begin();
  float sValues[9];
}
void loop(){
  //alvik.get_orientation(sValues[0], sValues[1], sValues[2]); // Nur Yaw-Value (i=2) wird verwendet werden (ist die Rotation vom Start auf der Z-Achse)
  //randomDrive();
  //savedrive();

  alvik.get_imu(sValues[1], sValues[2], sValues[3], sValues[4], sValues[5], sValues[6]);
  Serial.println(sValues[1]);
  Serial.println(sValues[2]);
  Serial.println(sValues[3]);
  Serial.println(sValues[4]);
  Serial.println(sValues[5]);
  Serial.println(sValues[6]);

  // @Todo: Erkennung widerholte bewegung (wegen feststecken) bei der hinfahrt und auskorigieren bei rückfahrt.
}

void randomDrive(){
  char buff [32];
  int rand_maxValue = 13;
  int rand_minValue = 5;
  srand(time(NULL));

  float testLinVel = rand() % (rand_maxValue - rand_minValue + 1) + rand_minValue;
  float testAngVel = rand() % (25 + 1) + rand_minValue;

  /*sprintf(buff,"LinVel:%f  AngVel:%f", testLinVel, testAngVel);
  Serial.println(buff);*/
  
  alvik.drive(testLinVel, testAngVel);
}

void savedrive(){
  static char i = 0;
  alvik.get_imu(sValues[i][1], sValues[i][2], sValues[i][3], sValues[i][4], sValues[i][5], sValues[i][6]);
  i++;
}


