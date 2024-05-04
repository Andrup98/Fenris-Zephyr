#include <zephyr/kernel.h>
#include <zephyr/drivers/can.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/device.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "can_send.h"
#include "can_receive.h"
#include "can_dev.h"
#include "pwm.h"
#include "motor_controller.h"

void process_can_data(void) {
    struct can_ret_data received_data;
    if (k_msgq_get(&can_msgq, &received_data, K_FOREVER) == 0) {
        printk("Processing CAN data: Bool=%d, Degree=%d, Speed=%d\n",
        received_data.js_bool_data,
        received_data.js_deg_int_data,
        received_data.js_spd_int_data);
        // Process your motor control logic here
        control_motors(received_data.js_deg_int_data, received_data.js_spd_int_data, received_data.js_bool_data);
    }
}

void main(void) {
    //printf("In main\n");
    const struct device *const can_dev = get_can_dev();
    

    if (!can_dev) {
        printk("Cannot find CAN device!\n");
        return;
    }
    /*else{
        printf("Can device found!\n");
    }*/
    
    enum can_state state;
    struct can_bus_err_cnt err_cnt;

    int ret = can_start(can_dev);
    if (ret != 0) {
        printf("Failed to start CAN controller: Error %d\n", ret);
        return;
    } /*else {
        printf("CAN controller started successfully\n");
    }*/

    if (setup_can_filter(can_dev, can_rx_callback, NULL) < 0) {
        printk("Failed to add CAN filter\n");
        return;
    }

    int ret2 = pwm_begin();
    if(ret2 < 0){
        printf("\nError initializing PWM. Error code = %d\n", ret2);
        while(1);
    }
    k_msleep(100);

    while (1) {
        //printf("In the while loop\n");

        if (can_get_state(can_dev, &state, &err_cnt) != 0) {
            printk("Failed to get CAN state\n");
        } else {
        printf("CAN State: %s\n", can_state_to_str(state));
        printf("TX Errors: %d, RX Errors: %d\n", err_cnt.tx_err_cnt, err_cnt.rx_err_cnt);
        }

        process_can_data();
        send_string(can_dev, "Hello");
        k_sleep(K_SECONDS(1)); // Sleep forever, letting the callback handle messages
    }
}