#include <zephyr/kernel.h>
#include <zephyr/drivers/can.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <stdbool.h>
#include <string.h>
#include "can_send.h"
#include "can_receive.h"
#include "can_dev.h"




void main(void) {
    //printf("In main\n");
    const struct device *const can_dev = get_can_dev();
    
    if (!can_dev) {
        printk("Cannot find CAN device!\n");
        return;
    }
    /*else{
        printf("Found CAN device!\n");
    }
    */

    uint8_t js_bool = 1; //True(1) for left joystick, False(0) for right.
    int16_t js_deg_int = 180; //Joystick for degrees 0-360 
    int16_t js_spd_int = 80; //Joystick values for speed 0-100
    

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

    while (1) {
        //printk("In the while loop\n");
        
        if (can_get_state(can_dev, &state, &err_cnt) != 0) {
            printk("Failed to get CAN state\n");
        } else {
        printf("CAN State: %s\n", can_state_to_str(state));
        printf("TX Errors: %d, RX Errors: %d\n", err_cnt.tx_err_cnt, err_cnt.rx_err_cnt);
        }
        
        send_custom_data(can_dev, js_bool, js_deg_int, js_spd_int);
        k_sleep(K_SECONDS(1)); // Send periodically
    }
    
}
