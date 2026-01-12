#include "Arduino_Alvik.h"

void testdrive();
void savedrive();

float sValues[10][10];

void setup(){
  Serial.begin(115200);
  alvik.begin();
}

void loop(){
  //alvik.get_orientation(sValues[0], sValues[1], sValues[2]); // Nur Yaw-Value (i=2) wird verwendet werden (ist die Rotation vom Start auf der Z-Achse)
 
  alvik.drive(12, 20);
  Serial.println("LinVel:12 AngVel:20");
  savedrive();
  Serial.println("Drive saved");
}

void testdrive(){
  Serial.println("in di bininging");
  char buff [32];
  int rand_maxValue = 13;
  int rand_minValue = 5;
  srand(time(NULL));

  float testLinVel = rand() % (rand_maxValue - rand_minValue + 1) + rand_minValue;
  float testAngVel = rand() % (25 + 1) + rand_minValue;

  sprintf(buff,"LinVel:%f  AngVel:%f", testLinVel, testAngVel);
  Serial.println(buff);
  
  alvik.drive(testLinVel, testAngVel);
  Serial.println("end of function testdrive");
}

void savedrive(){
  static char i = 0;
  alvik.get_imu(sValues[i][1], sValues[i][2], sValues[i][3], sValues[i][4], sValues[i][5], sValues[i][6]);
  i++;
}


