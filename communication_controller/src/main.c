#include <zephyr/drivers/can.h>
#include "interrupt_and_threads.h"
#include "canbus.h"
#include "math_calc.h"
#include "path_check.h"
#include "canbus.h"
#include "bt_controller.h"


void main(void)
{
    canBegin();
    start_sensor_thread();
    start_js_thread();
    interruptThreadBegin();

    while(1) {
        k_msleep(100);  // Sleep for 100 milliseconds
    }

}
