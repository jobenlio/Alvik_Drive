#include "Arduino_Alvik.h"
static Arduino_Alvik alvik;

void setup() {
  Serial.begin(115200);
  alvik.begin();
  Serial.println("setup");
}

void loop() {
  alvik.drive(3, -40);
  float sValues[2][2];

  alvik.get_drive_speed(sValues[0][0], sValues[0][1]);

  Serial.print(sValues[0][0]);
  Serial.print("\t");
  Serial.println(sValues[0][1]);

  delay(100);
}
