
#include <stdio.h>
#include <stdbool.h>
#include "path_check.h"

struct path_check_results path_check(int angle, int speed, bool js_num, uint8_t sensorValues){
    uint8_t testBits;
    struct path_check_results forward_results;
    forward_results.angle = angle;
    forward_results.js_num = js_num;
    if (js_num == false){
        
        if (speed > 10){
        // Determine motor control based on angle
            if ((angle >= 337 && angle <= 360) || (angle >= 0 && angle < 23)) {
            // Forward motion
            // Adjust speed based on joystick radius
                printk("FORWARD\n");
                testBits = (uint8_t)1;
                if ((int)(sensorValues & testBits) > 0){
                    forward_results.speed = 0;
                }
                else{
                    forward_results.speed = speed;
                }

            } else if(angle >= 23 && angle < 67){
            // Diagonal Right-forward diagonal motion
                printk("Right-Forward diagonal\n");
                testBits = (uint8_t)3;
                if ((int)(sensorValues & testBits) > 0){
                    forward_results.speed = 0;
                    
                }
                else{
                    forward_results.speed = speed;
                    
                }

            } else if (angle >= 67 && angle < 112) {
            // Right strafe motion
                printf("RIGHT STRAFE\n");
                testBits = (uint8_t)2;
                if ((int)(sensorValues & testBits) > 0){
                    forward_results.speed = 0;
                    
                }
                else{
                    forward_results.speed = speed;
                    
                }

            } else if (angle >= 112 && angle < 157){
            //Diagonal right-backward motion
                printf("Right-Backward diagonal\n");
                testBits = (uint8_t)10;
                if ((int)(sensorValues & testBits) > 0){
                    forward_results.speed = 0;
                    
                }
                else{
                    forward_results.speed = speed;
                    
                }

            } else if (angle >= 157 && angle < 202) {
            // Backward motion
            // Implement backward motor control
                printf("BACKWARDS\n");
                testBits = (uint8_t)8;
                if ((int)(sensorValues & testBits) > 0){
                    forward_results.speed = 0;
                    
                }
                else{
                    forward_results.speed = speed;
                    
                }

            } else if (angle >= 202 && angle < 247) {
            //Diagonal left-backward motion
                printf("Left-Backward diagonal\n");
                testBits = (uint8_t)12;
                if ((int)(sensorValues & testBits) > 0){
                    forward_results.speed = 0;
                    
                }
                else{
                    forward_results.speed = speed;
                    
                }

            } else if (angle >= 247 && angle < 292){
            // Left strafe motion
            // Implement left strafe motor control
                printf("LEFT STRAFE\n");
                testBits = (uint8_t)4;
                if ((int)(sensorValues & testBits) > 0){
                    forward_results.speed = 0;
                    
                }
                else{
                    forward_results.speed = speed;
                    
                }

            } else if (angle >= 292 && angle < 337){
            // diagonal left-forward motion
                printf("Left-Forward diagonal\n");
                testBits = (uint8_t)5;
                if ((int)(sensorValues & testBits) > 0){
                    forward_results.speed = 0;
                    
                }
                else{
                    forward_results.speed = speed;
                    
                }
            }
        }
        else {
            printf("Standing still, no motion\n");
            forward_results.speed = 0;
            }
    
    }

    else if(js_num == true){
        if (speed > 10){
            if (angle >= 20 && angle < 160){
            //Right rotate?
                printf("RIGHT Rotate\n");
                testBits = (uint8_t)15;
                if ((int)(sensorValues & testBits) > 0){
                    forward_results.speed = (int)(speed/2);
                    
                }
                else{
                    forward_results.speed = speed;
                    
                }
            } 
        
        else if (angle > 200 && angle < 340){
            //Left rotate?
            
            printf("LEFT Rotate\n");
            testBits = (uint8_t)15;
                if ((int)(sensorValues & testBits) > 0){
                    forward_results.speed = (int)(speed/2);
                    
                }
                else{
                    forward_results.speed = speed;
                    
                }
            }
            else {
            printf("No rotation\n");
            forward_results.speed = 0;
            }
        }
        else {
            printf("Standing still, no rotation\n");
            forward_results.speed = 0;
            }
        
    }
    return forward_results;
}