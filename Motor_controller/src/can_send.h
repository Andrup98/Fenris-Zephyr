#ifndef CAN_SEND_H
#define CAN_SEND_H

#define MSG_ID 0x0000002 // Message ID

const char* can_state_to_str(enum can_state state);
void send_string(const struct device *can_dev, const char *str);

#endif // CAN_UTILS_H