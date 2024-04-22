#ifndef CAN_RECEIVE_H
#define CAN_RECEIVE_H

#define RECEIVE_ID_STR 0x0000002 // RECEIVE ID for motor controller
#define RECEIVE_ID_BYTE 0x0000003 // RECEIVE ID for sensor 

int setup_can_filter(const struct device *dev, can_rx_callback_t rx_cb, void *cb_data);

void can_rx_callback(const struct device *dev, struct can_frame *frame, void *user_data);

#endif
