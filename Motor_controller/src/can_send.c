#include <zephyr/kernel.h>
#include <zephyr/drivers/can.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <stdbool.h>
#include <string.h>
#include "can_send.h"
#include "can_dev.h"

/* Function to convert CAN state to readable string */
const char* can_state_to_str(enum can_state state) {
    switch (state) {
        case CAN_STATE_ERROR_ACTIVE:
            return "ERROR ACTIVE";
        case CAN_STATE_ERROR_WARNING:
            return "ERROR WARNING";
        case CAN_STATE_ERROR_PASSIVE:
            return "ERROR PASSIVE";
        case CAN_STATE_BUS_OFF:
            return "BUS OFF";
        case CAN_STATE_STOPPED:
            return "STOPPED";
        default:
            return "UNKNOWN";
    }
}

void send_string(const struct device *can_dev, const char *str){
    struct can_frame frame;
    memset(&frame, 0, sizeof(frame));

    frame.flags = CAN_FRAME_IDE; // Use extended identifier
    frame.id = MSG_ID;
    frame.dlc = strlen(str);  // Set the DLC to the string length
    memcpy(frame.data, str, frame.dlc);  // Copy string to CAN frame data field

    if (can_send(can_dev, &frame, K_SECONDS(10), NULL, NULL) != 0) {
            printk("Failed to send frame\n");
        } /*else {
            printk("Frame sent\n");
        }*/
}