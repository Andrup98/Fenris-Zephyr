#include <zephyr/kernel.h>
#include <zephyr/drivers/can.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <stdbool.h>
#include <string.h>
#include "can_receive.h"
#include "can_dev.h"


int setup_can_filter(const struct device *dev, can_rx_callback_t rx_cb, void *cb_data){
    struct can_filter filter = {
        .flags = CAN_FILTER_DATA | CAN_FILTER_IDE,
	    .id = RECEIVE_ID,
	    .mask = CAN_EXT_ID_MASK
    };
    return can_add_rx_filter(dev, rx_cb, cb_data, &filter);
}

void can_rx_callback(const struct device *dev, struct can_frame *frame, void *user_data) {
    char received_str[9];  // Buffer to store received string, +1 for NULL termination

    if (frame->dlc <= 8) {
        memcpy(&received_str, &frame->data, frame->dlc);
        received_str[frame->dlc] = '\0';  // NULL-terminate the string
        printk("Received string: %s\n", received_str);
    }
}