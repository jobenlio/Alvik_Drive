#include "Arduino_Alvik.h"
static Arduino_Alvik alvik;

void setup() {
  Serial.begin(115200);
  alvik.begin();
}

void loop() {
  char buff [50];

  float sValues[6][6];

  alvik.get_imu(sValues[0][1], sValues[0][2], sValues[0][3], sValues[0][4], sValues[0][5], sValues[0][6]);

  sprintf(buff, "%f\t%f\t", sValues[0][0], sValues[0][1]);
  Serial.println(buff);

  delay(1000);
}
