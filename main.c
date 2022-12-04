

/**
 * main.c
 */
#include "lcd.h"
#include "uart.h"
#include "movement.h"
#include "open_interface.h"
#include "Timer.h"
#include "adc.h"
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "servo.h"
#include "ping.h"
int main(void)
{
    //initialize Variables
    lcd_init();
    oi_t *sensor = oi_alloc();
    oi_init(sensor);
    uart_init(115200);
    adc_init();
    ping_init();
    servo_init();
    int degrees = 0;
    int i;
    float adc = 0;
    unsigned int ping = 0;
    float average_adc;
    float distance_adc;
    float distance_ping;
    char adc_uart[10];
    float average_distance;
    unsigned int average_ping;
    float last = 0;
    int angles[10];
    int j = 0;
    int obj = 0;
    int k = 0;
    float object_distances[30];
    float object_distance_final[10];
    int s = 0;
    int angle;
    char object_angle[10];
    char object_width[10];
    int width;
    char input;
    while(1){
        //this is the goto spot in the movement loop
        scan:
        degrees = 0;
        //scan for objects
    while(degrees < 180){
        servo_move(degrees);
        for(i = 0; i < 3; i++){
            adc += adc_read();

        }
        average_adc = adc / 3;
        ping = ping_read();
        distance_adc = (12289 * pow(average_adc, -0.861));
        distance_ping = (((float)ping / 16000000) * 34300) / 2;
        average_distance = (distance_ping + distance_adc) / 2;
        //checks if the distances between the previous scan has dropped
        if(last - average_distance >= 15){
            angles[j] = degrees;
            j++;
            obj += 1;
            //used this to aviod detecting false objects
            if(obj >= 5){
             object_distances[k] = average_distance;
             k++;
            }
            //this if statement is for when the object is done being scanned
        }else if(last - average_distance < 15 && last > 0 && obj >= 5){
            //find the distance, angle, and width of the object and print it in putty
            last = average_distance;
            object_distance_final[s] = object_distances[1];
            angle = angles[(j / 2) + 1];
            width = angles[j - 1] - angles[0];
            if(width )
            sprintf(adc_uart , "%f", object_distance_final[s]);
            sprintf(object_angle, "%d", angle);
            sprintf(object_width, "%d", width);
            for(i = 0; i < strlen(adc_uart); i++){
                uart_sendChar(adc_uart[i]);
            }
            for(i = 0; i < 20; i++){
                uart_sendChar(' ');
            }
            for(i = 0; i < strlen(object_angle); i++){
                uart_sendChar(object_angle[i]);
            }
            for(i = 0; i < 20; i++){
                uart_sendChar(' ');
            }
            for(i = 0; i < strlen(object_width); i++){
                uart_sendChar(object_width[i]);
            }
            obj = 0;
            j = 0;
            k = 0;
            uart_sendChar('\r');
            uart_sendChar('\n');

        }else{
            j = 0;
            obj = 0;
            last = average_distance;
        }
        timer_waitMillis(200);
        adc = 0;
        degrees += 2;
    }
    //handles the movement of the cybot
    while(1){
       input = uart_receive();
       if(input == 'w'){
           move_forward(sensor, 300);
       }
       if(input == 'a'){
           turn_counterclockwise(sensor, 90);
       }
       if(input == 's'){
           reverse(sensor, 300);
       }
       if(input == 'q'){
           goto done;
       }if(input == 'd'){
           turn_clockwise(sensor, 90);
       }
       if(input == 'm'){
           goto scan;
       }
    }

    }
    done:
    oi_free(sensor);
	return 0;
}
