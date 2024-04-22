#ifndef CAN_SEND_H
#define CAN_SEND_H

#define MSG_ID 0x0000003 // Message ID

const char* can_state_to_str(enum can_state state);
void send_byte(const struct device *can_dev, uint8_t sensor_byte);

#endif // CAN_UTILS_H