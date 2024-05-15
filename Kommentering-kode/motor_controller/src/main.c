#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/adc.h>
#include <stdio.h>
#include "pwm.h"
#include "motorkontroller.h"
#include "canbus.h"


int main(void)
{
        //Alt som skjer før while-loopen skjer kun en gang før koden loopen evig i while.

        // lager en variabel kalt drive_command som er av samme data-type som
        // kommandoen som kommer over CANBUS fra kommunikasjons-kontrolleren
        struct can_ret_data drive_command;

        // Initialiseringsfunksjon med nødvendig oppsett og konfigurering for CANBUS
        can_begin();

        // Initialiseringsfunksjon med nødvendig oppsett og konfigurering for PWM
        pwm_begin();
        while (true)
        {
                // Henter verdiene til variabelen som oppdateres hver gang en kommando
                // sendes over CANBUS
                drive_command = get_drive_command();

                //Kjører motorene med verdiene til drive_command: joystick vinkel, hastighet og js_bool
                control_motors(drive_command.js_deg_int_data, drive_command.js_spd_int_data, drive_command.js_bool_data);

                //Systemet sover i x-antall millisekunder.
                k_msleep(100);
        }
}
