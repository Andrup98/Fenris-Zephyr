#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H
#include <stdbool.h>
// Function prototypes
int control_motors(int angle, int speed, bool joystick_nr);
int mapValue(int value, int direction);

#endif
