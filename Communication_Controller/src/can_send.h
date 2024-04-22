#ifndef CAN_SEND_H
#define CAN_SEND_H

#define MSG_ID 0x0000001 // Message ID

const char* can_state_to_str(enum can_state state);
void send_custom_data (const struct device *can_dev, uint8_t js_bool, int16_t js_deg_int, int16_t js_spd_int);

#endif // CAN_UTILS_H