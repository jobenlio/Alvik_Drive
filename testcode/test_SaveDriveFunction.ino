#include "Arduino_Alvik.h"

static Arduino_Alvik alvik;

float sValues[10][6];

void setup(){
  Serial.begin(115200);
  alvik.begin();
}

void savedrive();

void loop(){
  //alvik.get_orientation(sValues[0], sValues[1], sValues[2]); // Nur Yaw-Value (i=2) wird verwendet werden (ist die Rotation vom Start auf der Z-Achse)
  if (alvik.get_touch_any()){
    if(alvik.get_touch_up()){
      Serial.println("up");
      alvik.drive(10, 27);
      savedrive();
    }

    else if(alvik.get_touch_down()){
      Serial.println("down");
      for(int index=0; index < 10; index++){
        for(int i=0; i<6;i++){
          Serial.println(sValues[index][i]);
        }
      }
    }
  }
}

void savedrive(){
  static int aIndexSave = 0;
  for(aIndexSave; aIndexSave<5; aIndexSave++){
    alvik.get_imu(sValues[aIndexSave][1], sValues[aIndexSave][2], sValues[aIndexSave][3], sValues[aIndexSave][4], sValues[aIndexSave][5], sValues[aIndexSave][6]);
    Serial.println("Drive saved");
  }
}


