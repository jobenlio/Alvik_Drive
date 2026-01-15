#include "Arduino_Alvik.h"
static Arduino_Alvik alvik;

void setup() {
  Serial.begin(115200);
  alvik.begin();
  Serial.println("setup");
}

void loop() {
  alvik.drive(5, -9);
  float sValues[50][3];
  static int i = 0;
  i>49? i = 0: i++;

  alvik.get_orientation(sValues[i][0], sValues[i][1], sValues[i][2]);

  Serial.print(sValues[i][0]);
  Serial.print("\t");
  Serial.print(sValues[i][1]);
  Serial.print("\t");
  Serial.println(sValues[i][2]);

  delay(100);
}
