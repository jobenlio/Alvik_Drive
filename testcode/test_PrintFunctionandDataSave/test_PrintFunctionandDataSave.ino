#include "Arduino_Alvik.h"
static Arduino_Alvik alvik;

void setup() {
  Serial.begin(115200);
  alvik.begin();
  Serial.println("setup");
}

void loop() {
  float sValues[6][2];

  alvik.get_imu(sValues[0][0], sValues[0][1], sValues[0][2], sValues[0][3], sValues[0][4], sValues[0][5]);

  char buff [50];
  sprintf(buff, "%f\t%f\t%f\t%f\t%f\t%f", sValues[0][0], sValues[0][1], sValues[0][2], sValues[0][3], sValues[0][4], sValues[0][5]);
  Serial.println(buff);

  delay(10);
}
