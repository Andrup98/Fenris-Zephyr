#ifndef __INTERRUPT_AND_THREADS_H
#define __INTERRUPT_AND_THREADS_H

#include <stdio.h>
#include <stdbool.h>
#include <zephyr/sys/printk.h>
#include <nrfx_timer.h>

struct js_data_raw {
    int pot_x; 
    int pot_y; 
    bool js;
};
struct data_for_motorcontroller {
    int angle; 
    int speed; 
    bool js;
};

void process_data();
void continous_js_thread();
void continous_sensor_thread();
static void timer_handler(nrf_timer_event_t event_type, void *p_context);

void interruptBegin();
void start_js_thread();
void start_sensor_thread();
//void terminate_thread();
int get_counter();

#endif