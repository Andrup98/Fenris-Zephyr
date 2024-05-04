#ifndef CAN_RECEIVE_H
#define CAN_RECEIVE_H

#define RECEIVE_ID 0x0000001 // RECEIVE ID
#define CAN_MSGQ_SIZE 10

struct can_ret_data {
    bool js_bool_data;     // Converted from uint8_t to bool
    int js_deg_int_data;   // Converted from int16_t to int
    int js_spd_int_data;   // Converted from int16_t to int
};

extern struct k_msgq can_msgq;

int setup_can_filter(const struct device *dev, can_rx_callback_t rx_cb, void *cb_data);

void can_rx_callback(const struct device *dev, struct can_frame *frame, void *user_data);

#endif