/*
 * File:          my_controller1.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */

#include <string.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define TIME_STEP 16

// motor wheels
static WbDeviceTag wheels[4];

static void rotate(WbDeviceTag tag, double speed) {
  if (speed >= 0.0) {
    wb_motor_set_position(tag, INFINITY);
    wb_motor_set_velocity(tag, speed);
  } else {
    wb_motor_set_position(tag, INFINITY);
    wb_motor_set_velocity(tag, speed);
  }
}

static void go_straight(WbDeviceTag tag, double speed) {
  wb_motor_set_position(tag, INFINITY);
  wb_motor_set_velocity(tag, speed);
  }

static void wheels_set_speed(double speed) {
  int i;
  for (i = 0; i < 4; i++)
    rotate(wheels[i], speed);
}

int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  wb_robot_init();
  
  // all vehicles
  wheels[0] = wb_robot_get_device("wheel1");
  wheels[1] = wb_robot_get_device("wheel2");
  wheels[2] = wb_robot_get_device("wheel3");
  wheels[3] = wb_robot_get_device("wheel4");

  // go forward
  wheels_set_speed(-2.0);
  
  // forever
  double time = 0.0;
  while (wb_robot_step(TIME_STEP) != -1) {
     time += TIME_STEP / 1000.0;
     }

  wb_robot_cleanup();

  return 0;
}