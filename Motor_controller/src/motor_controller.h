#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H
#include <stdbool.h>
// Function prototypes
int control_motors(int angle, int speed, bool joystick_nr);
int mapValue(int value, int direction);
int speed_to_ds(int duty_cycle);

#endif