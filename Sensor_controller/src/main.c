#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/can.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys_clock.h>
#include <zephyr/timing/timing.h>
#include <stdbool.h>
#include <string.h>
#include "hc_sr04.h"
#include "can_send.h"
#include "can_receive.h"
#include "can_dev.h"

hc_sr04_t sensors[2];

int main(void) {
    const struct device *const can_dev = get_can_dev();
    
    if (!can_dev) {
        printk("Cannot find CAN device!\n");
        return;
    }
    /*else{
        printf("Found CAN device!\n");
    }
    */

    

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

    hc_sr04_init(&sensors[0], "GPIO_0", 4, 3); //Forward sensor
    hc_sr04_init(&sensors[1], "GPIO_0", 10, 9); //Right Sensor
    //hc_sr04_init(&sensors[2], "GPIO_0", 6, 1); //Left Sensor
    //hc_sr04_init(&sensors[3], "GPIO_0", 7, 0); //Rear Sensor

    while (1) {
        uint8_t sensor_byte = 0;
        if (can_get_state(can_dev, &state, &err_cnt) != 0) {
            printk("Failed to get CAN state\n");
        } else {
        printf("CAN State: %s\n", can_state_to_str(state));
        printf("TX Errors: %d, RX Errors: %d\n", err_cnt.tx_err_cnt, err_cnt.rx_err_cnt);
        }
        
        double distances[2];
        distances[0] = hc_sr04_read_distance(&sensors[0]);
        distances[1] = hc_sr04_read_distance(&sensors[1]);
        //distances[2] = hc_sr04_read_distance(&sensors[2]);
        //distances[3] = hc_sr04_read_distance(&sensors[3]);

        for (int i = 0; i < 2; i++) {
            printk("Sensor %d Distance: %d cm\n", i + 1, (int)distances[i]);
            if ((int)distances[i] < 20) {
                sensor_byte |= (1 << i); // Set the bit corresponding to the sensor if blocked
            }
        }

        printk("Sensor Status: 0x%02X\n", sensor_byte);
        send_byte(can_dev, sensor_byte);
        k_sleep(K_SECONDS(1));
    }
}