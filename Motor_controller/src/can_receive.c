#include <zephyr/kernel.h>
#include <zephyr/drivers/can.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <stdbool.h>
#include <string.h>
#include "can_receive.h"
#include "can_dev.h"


K_MSGQ_DEFINE(can_msgq, sizeof(struct can_ret_data), CAN_MSGQ_SIZE, 4);

int setup_can_filter(const struct device *dev, can_rx_callback_t rx_cb, void *cb_data){
    struct can_filter filter = {
        .flags = CAN_FILTER_DATA | CAN_FILTER_IDE,
	    .id = RECEIVE_ID,
	    .mask = CAN_EXT_ID_MASK
    };
    return can_add_rx_filter(dev, rx_cb, cb_data, &filter);
}

void can_rx_callback(const struct device *dev, struct can_frame *frame, void *user_data) {
    printk("Received frame with ID: 0x%x\n", frame->id);
    if (frame->dlc == 5) { // Expecting 5 byte of data
        struct can_ret_data js_data;
        
         js_data.js_bool_data = (frame->data[0] != 0);  // True if non-zero, false otherwise

        // Convert int16_t to int (assuming the system is little-endian or matching endianness)
        int16_t js_deg_int, js_spd_int;
        memcpy(&js_deg_int, &frame->data[1], sizeof(js_deg_int));
        memcpy(&js_spd_int, &frame->data[3], sizeof(js_spd_int));
        
        js_data.js_deg_int_data = js_deg_int;  // Automatic promotion to int
        js_data.js_spd_int_data = js_spd_int;  // Automatic promotion to int

        printk("Received data: js_bool=%d, js_deg=%d, js_spd=%d\n",
               js_data.js_bool_data, js_data.js_deg_int_data, js_data.js_spd_int_data);

        if (k_msgq_put(&can_msgq, &js_data, K_NO_WAIT) != 0) {
            printk("Failed to put data in queue\n");
        }
    }
}

