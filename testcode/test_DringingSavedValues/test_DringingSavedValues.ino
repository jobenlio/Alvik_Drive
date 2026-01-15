/**
* @file test_saveDirving.ino
* @author Jonathan Grüninger 
* @brief testing saving the route the alvik drives.
*/

#include "Arduino_Alvik.h"
static Arduino_Alvik alvik;

void savedrive(); // Function to save the driving values

float sValues[100][2];  // Array where the drive values are stored 

/**
* @brief Function to set up the hardware.
*/
void setup(){
  Serial.begin(115200);
  alvik.begin();
}

/**
* @brief Super loop function.
*/
void loop(){
  if(alvik.get_touch_any()){  // Looking if any buton on the alvik got pressed

    /*Up button: driving a defined way for 10 s*/
    if(alvik.get_touch_up()){
      for (int in= 0;in<100;in++ ){
        alvik.drive(5, 45);   // Alvik drives in a Circle with an angle of 45 deg/s 
        savedrive();          // Saving the current values of the lin. and angular velocity
        delay(100);
      }
    }

    /*If the down button got pressed the driving form before gets driven agan*/
    else if(alvik.get_touch_down()){ 
      for(int i = 0; i<100;i++){
        alvik.drive(sValues[i][0], sValues[i][1]);
        delay(100);
      }
    }
  }
  alvik.brake();  // Stop the driving of the Alvik
}

void savedrive(){
  // Initialising Index 
  static int sSaveIndex = 0;
  alvik.get_drive_speed(sValues[sSaveIndex][0], sValues[sSaveIndex][1]); // Saving the linear- and angular velocity of the robot
  sSaveIndex > 99? sSaveIndex = 0: sSaveIndex++;  // Restarting Index since for this test the array is just 100 long
}