/**
 * @file main.ino
 * @author Gabriel Heinzer
 * @brief Main firmware for the Alvik robot implementing a simple pathfinding algorithm.
 */

#include "Arduino_Alvik.h"

/**
 * @brief Instance of the Alvik robot class.
 */
Arduino_Alvik alvik;

/**
 * @brief Minimum distance to an obstacle before the robot starts turning to the longest distance.
 */
#define DISTANCE_TURN_MIN 30
/**
 * @brief Distance threshold to trigger a reverse-turn maneuver. This is also the distance which
 * the robot moves back before turning.
 */
#define DISTANCE_REVERSE 5
/**
 * @brief Angle to turn when reversing.
 */
#define ANGLE_REVERSE 90
/**
 * @brief Linear speed when driving straight
 */
#define DRIVE_STRAIGHT_LINEAR_SPEED 50
/**
 * @brief Linear speed when driving an angle.
 */
#define DRIVE_ANGLE_LINEAR_SPEED 10
/**
 * @brief Base angular speed when driving an angle. This is multiplied by the index of the longest distance (-2 .. +2).
 */
#define DRIVE_ANGLE_ANGULAR_SPEED_BASE 20

#define ARRAY_LENGTH 10000
/**
 * @brief Pathfinding modes for the robot.
 */
typedef enum {
  /**
   * @brief Finds the farthest path available.
   */
  PATHFINDER_FIND_FARTHEST,
  /**
   * @brief Finds the closest object available.
   */
  PATHFINDER_FIND_CLOSEST
} PathFinderMode_t;


float sValues[ARRAY_LENGTH][2];
static int sArrayTail = 0;

PathFinderMode_t GlobalMode = PATHFINDER_FIND_FARTHEST;


/**
 * @brief Function to set up all the hardware.
 */
void setup() {
  Serial.begin(115200);

  alvik.begin();
}

/**
 * @brief Function to calculate the linear speed and angular speed based on the pathfinding mode and the distance.
 * 
 * @param linear_speed Pointer to a variable which wil hold the linear speed.
 * @param angular_speed Pointer to a variable which will hold the angular speed.
 * @param mode Pathfinding mode to use.
 */
void pathfinder_find_path(float& linear_speed, float& angular_speed, PathFinderMode_t mode) {
  /* Read all distances to an array*/
  float distances[5];
  alvik.get_distance(distances[0], distances[1], distances[2], distances[3], distances[4]);

  /**
   * @brief Maximum distance which the distance sensor measured.
   */
  float max_distance = distances[2];
  /**
   * @brief Minimum distance which the distance sensor measured.
   */
  float min_distance = UINT32_MAX;
  /**
   * @brief Index of the `min_distance`.
   */
  int8_t max_distance_index = 2;
  /**
   * @brief Index of the `max_distance`.
   */
  int8_t min_distance_index = 2;

  /* Iterate through al distances and determine the minimum and maximum distance. */
  for(int i = 0; i < (sizeof(distances) / sizeof(*distances)); i++) {
    float& distance = distances[i];

    if(distance > max_distance)  {
      max_distance_index = i;
      max_distance = distance;
    }

    if(distance < min_distance) {
      min_distance_index = i;
      min_distance = distance;
    }
  }

  /* Determine the path based on the mode.*/
  switch(mode) {
    case PATHFINDER_FIND_FARTHEST:
      if(distances[2] <= DISTANCE_REVERSE) {
        /* Reverse and rotate 90 deg when the distance is under a certain threshold */
        alvik.move(-DISTANCE_REVERSE);
        alvik.rotate(ANGLE_REVERSE);
        linear_speed = -1000;
      } else if(distances[2] <= DISTANCE_TURN_MIN) {
        /* If the distance is less than the turn threshold, turn towards the longest distance. */
        int8_t turn_direction = 2 - max_distance_index;
        angular_speed = (float)turn_direction * DRIVE_ANGLE_ANGULAR_SPEED_BASE;
        linear_speed = DRIVE_ANGLE_LINEAR_SPEED;
      } else {
        /* If the distance is greater than the turn threshold, drive straight. */
        linear_speed = DRIVE_STRAIGHT_LINEAR_SPEED;
        angular_speed = 0;
      }
      break;

    case PATHFINDER_FIND_CLOSEST:
      /* Always drive to the closest object. */
      int8_t turn_direction = 2 - min_distance_index;
      angular_speed = (float)turn_direction * DRIVE_ANGLE_ANGULAR_SPEED_BASE;
      linear_speed = DRIVE_ANGLE_LINEAR_SPEED;
      break;
  }
}
/**
* 
*/
void savedrive(float& linear_speed, float& angular_speed){
  // Initialising Index 
  static int sSaveIndex = 0;

  if (sArrayTail < 0)
  {
    sSaveIndex = 0;
    sArrayTail = 0;
  }

  sValues[sSaveIndex][0] = linear_speed;
  sValues[sSaveIndex][1] = -1 * angular_speed;   // changing direction

  sSaveIndex = (sSaveIndex + 1) % ARRAY_LENGTH;
  sArrayTail++;
}

/**
 * @brief Super loop function which continuously executes the application.
 */
void loop() {
  static char parcourStarted = 0;
  static char FlagTouchUp = 0;

  if (alvik.get_touch_up() || FlagTouchUp == 1)
  {
    FlagTouchUp = 1;
    if (alvik.get_color_label() == "green" || parcourStarted == 1)
    {
      parcourStarted = 1;

      float linear_speed, angular_speed;

      /* Calculate the velocities. */
      pathfinder_find_path(linear_speed, angular_speed, GlobalMode);

      /* Drive the robot.*/
      alvik.drive(linear_speed, angular_speed);
      savedrive(linear_speed, angular_speed);
    }

    // End of parcour 
    if (alvik.get_color_label() == "red")
    {
      parcourStarted = 0;
      FlagTouchUp = 0;

      alvik.stop();
    }
  }

  static char FlagDriveBack = 0;
  if (alvik.get_touch_down() || FlagDriveBack == 1)
  {
    FlagDriveBack = 1;

    //* Return path starts with rotation 180° to drive forward
    alvik.rotate(180)
    if (sValues[sArrayTail][0] <= -999)
    {
      alvik.rotate(ANGLE_REVERSE + 180);
      alvik.move(DISTANCE_REVERSE);
    }
    else
    {
      alvik.drive(sValues[sArrayTail][0], sValues[sArrayTail][1]);
    }

    sArrayTail--;

    // End of return path 
    if (sArrayTail < 0)
    {
      FlagDriveBack = 0;

      alvik.stop();
    }
  }

  // Change Pathfinder mode to chase after another alvik
  if (alvik.get_touch_center())
  {
    GlobalMode = PATHFINDER_FIND_CLOSEST;
  }

  /* A delay reduces the speed of the pathfinding. */
  delay(10);
}
