#include "Arduino_Alvik.h"
static Arduino_Alvik alvik;

void setup() {
  Serial.begin(115200);
  alvik.begin();
  Serial.println("setup");
}

void loop() {
  alvik.drive(2, 0);
  float sValues[6][2];

  alvik.get_imu(sValues[0][0], sValues[0][1], sValues[0][2], sValues[0][3], sValues[0][4], sValues[0][5]);

  Serial.print(sValues[0][0]);
  Serial.print("\t");
  Serial.print(sValues[0][1]);
  Serial.print("\t");
  Serial.print(sValues[0][2]);
  Serial.print("\t");
  Serial.print(sValues[0][3]);
  Serial.print("\t");
  Serial.print(sValues[0][4]);
  Serial.print("\t");
  Serial.println(sValues[0][5]);

  delay(100);
}
