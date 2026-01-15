#include "Arduino_Alvik.h"
static Arduino_Alvik alvik;

void setup() {
  Serial.begin(115200);
  alvik.begin();
}

void loop() {
  float sValues[3][2];
  float a = 34.6, b = 12.02, c = 622.56;
  sValues[0][0] = a; sValues[0][1] = b; sValues[1][1] = c;

  /******Version 1 Werte auf verschiedenen Linien******/
  /*for(int index=0; index<3; index++){
    for(int i=0; i<2;i++){
      Serial.println(sValues[index][i]);
    }
  }*/

  /******ODER wie folgt für alles auf einer Linie******/
  char buff [50];
  sprintf(buff, "%f\t%f\t", sValues[0][0], sValues[0][1]);
  Serial.println(buff);

  delay(1000);
}
