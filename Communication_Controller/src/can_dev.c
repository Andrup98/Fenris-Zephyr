#include <zephyr/kernel.h>
#include <zephyr/drivers/can.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include "can_dev.h"

const struct device *const get_can_dev(void){
    return DEVICE_DT_GET(DT_CHOSEN(zephyr_canbus));
} 