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
    struct can_filter filter_str = {
        .flags = CAN_FILTER_DATA | CAN_FILTER_IDE,
	    .id = RECEIVE_ID_STR,
	    .mask = CAN_EXT_ID_MASK
    };

    struct can_filter filter_byte = {
        .flags = CAN_FILTER_DATA | CAN_FILTER_IDE,
	    .id = RECEIVE_ID_BYTE,
	    .mask = CAN_EXT_ID_MASK
    };

    int filter_id_str = can_add_rx_filter(dev, rx_cb, cb_data, &filter_str);
    int filter_id_byte = can_add_rx_filter(dev, rx_cb, cb_data, &filter_byte);

    return (filter_id_str >= 0 && filter_id_byte >= 0) ? 0 : -1;  // Return 0 if both filters are added successfully
}

void can_rx_callback(const struct device *dev, struct can_frame *frame, void *user_data) {
    if (frame->id == RECEIVE_ID_STR && frame->dlc <= 8) {
        char received_str[9];
        memcpy(received_str, frame->data, frame->dlc);
        received_str[frame->dlc] = '\0';
        printk("Received string from ID 0x%X: %s\n", frame->id, received_str);
    } else if (frame->id == RECEIVE_ID_BYTE && frame->dlc == 1) {
        uint8_t received_byte = frame->data[0];
        printk("Received byte from ID 0x%X: %02X\n", frame->id, received_byte);
    } else {
        printk("Unexpected data format or ID\n");
    }
}