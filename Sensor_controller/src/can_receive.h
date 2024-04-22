#ifndef CAN_RECEIVE_H
#define CAN_RECEIVE_H

#define RECEIVE_ID 0x0000002 // RECEIVE ID

int setup_can_filter(const struct device *dev, can_rx_callback_t rx_cb, void *cb_data);

void can_rx_callback(const struct device *dev, struct can_frame *frame, void *user_data);

#endif