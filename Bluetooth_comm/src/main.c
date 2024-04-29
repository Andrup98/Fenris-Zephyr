#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/ring_buffer.h>
#include <string.h>
#include <stdlib.h>
#include "bt_controller.h"



void main(void) {
    const struct device *const uart_dev = get_uart_dev();
    if (!device_is_ready(uart_dev)) {
        printk("UART device is not ready\n");
        return;
    }

    configure_uart(uart_dev);
    printk("Starting to receive data...\n");

    while (1) {
        process_joystick_data();  // Process any new joystick data
        k_sleep(K_MSEC(100));  // Sleep to allow other system tasks and reduce CPU usage
    }
}