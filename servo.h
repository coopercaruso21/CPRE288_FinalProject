/*
 * servo.h
 *
 *  Created on: Nov 2, 2022
 *      Author: cbcaruso
 */

#ifndef SERVO_H_
#define SERVO_H_
#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"
void servo_init(void);
int servo_move(float degrees);




#endif /* SERVO_H_ */
