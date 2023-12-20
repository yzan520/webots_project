#include <string.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define TIME_STEP 1
#define WHEEL_RADIUS 0.05
#define PI 3.14

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

static void wheels_set_speed_rotate(double speed) {
  int i;
  for (i = 0; i < 4; i++)
    rotate(wheels[i], speed);
}

static void go_straight(WbDeviceTag tag, double speed) {
  wb_motor_set_position(tag, INFINITY);
  wb_motor_set_velocity(tag, speed);
}


int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  wb_robot_init();
  
  // all vehicles
  wheels[0] = wb_robot_get_device("wheel1");
  wheels[1] = wb_robot_get_device("wheel2");
  wheels[2] = wb_robot_get_device("wheel3");
  wheels[3] = wb_robot_get_device("wheel4");
  
  double speed = 1.0;
  
  double start_time = wb_robot_get_time();
  
  // go forward
  while (wb_robot_step(TIME_STEP) != -1) {
     double current_time = wb_robot_get_time();
     double diff_time = current_time - start_time;
     double distance = diff_time * speed * WHEEL_RADIUS;
     
     if (distance < 0.4) {
       go_straight(wheels[1], speed);
       go_straight(wheels[3], -speed);
       go_straight(wheels[0], 0);
       go_straight(wheels[2], 0);
       } // 1
     else if (distance < 0.8) {
       go_straight(wheels[0], speed);
       go_straight(wheels[2], -speed);
       go_straight(wheels[1], 0);
       go_straight(wheels[3], 0);
       } // 2
     else if (distance < 1.2) {
       go_straight(wheels[1], -speed);
       go_straight(wheels[3], speed);
       go_straight(wheels[0], 0);
       go_straight(wheels[2], 0);
       } // 3
     else if (distance < 1.6) {
       go_straight(wheels[0], -speed);
       go_straight(wheels[2], speed);
       go_straight(wheels[1], 0);
       go_straight(wheels[3], 0);
       } // 4
     else if (distance < 1.6 + 0.62) {
       wheels_set_speed_rotate(speed);
       } // clockwise
     else if (distance < 1.6 + 0.62 + 0.1) {
       wheels_set_speed_rotate(0);
       } // wait
     else if (distance < 1.6 + 2 * 0.62 + 0.1) {
       wheels_set_speed_rotate(-speed);
       } // anticlockwise
     else if (distance < 1.6 + 2 * 0.62 + 0.2) {
       wheels_set_speed_rotate(0);
       } // wait
     else if (distance < 1.6 + 2 * 0.62 + 0.2 + 0.62 / 8) {
       wheels_set_speed_rotate(-speed);
       }
       
     else if (distance < 1.6 + 2 * 0.62 + 0.2 + 0.62 / 8 + 0.57) {
       go_straight(wheels[2], -speed);
       go_straight(wheels[0], speed);
       go_straight(wheels[1], 0);
       go_straight(wheels[3], 0);
       }
     else {
       wheels_set_speed_rotate(0);
       }
  }
  wb_robot_cleanup();
  return 0;  
}
