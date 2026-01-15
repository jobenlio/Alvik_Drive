#include "Arduino_Alvik.h"
static Arduino_Alvik alvik;

void setup() {
  Serial.begin(115200);
  alvik.begin();
  Serial.println("setup");
}

void loop() {
  alvik.drive(3, -40);
  float sValues[50][2];
  static int i = 0;
  i>49? i = 0: i++;
  alvik.get_drive_speed(sValues[i][0], sValues[i][1]);

  Serial.print(sValues[i][0]);
  Serial.print("\t");
  Serial.println(sValues[i][1]);

  delay(100);
}
