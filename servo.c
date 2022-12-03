/*
 * servo.c
 *
 *  Created on: Nov 2, 2022
 *      Author: cbcaruso
 */
#include "servo.h"
#include "Timer.h"
float time;
float period;
void servo_init(){
    SYSCTL_RCGCTIMER_R |= 0b00000010;
    SYSCTL_RCGCGPIO_R |= 0b00000010;
    GPIO_PORTB_DEN_R |= 0b00100000;
    GPIO_PORTB_DIR_R |= 0b00100000;
    GPIO_PORTB_AFSEL_R |= 0b00100000;
    GPIO_PORTB_PCTL_R |=  0x00700000;
    TIMER1_CTL_R &= ~0x100;
    TIMER1_CFG_R |= 0x4;
    TIMER1_TBMR_R |= 0xA;
    TIMER1_TBILR_R = 320000;
    TIMER1_TBPR_R = 0x4;
    TIMER1_TBMATCHR_R = 312000;
    TIMER1_TBPMR_R = 0x4;
    TIMER1_CTL_R |= 0x100;


}
int servo_move(float degrees){

    if(degrees > 180 || degrees < 0){
        return 0;
    }

     period = (-155.56 * degrees) + 312000;
    TIMER1_TBMATCHR_R = period;






    return 0;

}

