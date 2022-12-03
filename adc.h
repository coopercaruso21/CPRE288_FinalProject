/*
 * adc.h
 *
 *  Created on: Oct 19, 2022
 *      Author: cbcaruso
 */

#ifndef ADC_H_
#define ADC_H_
#include <inc/tm4c123gh6pm.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Timer.h"

void adc_init(void);
int adc_read(void);


#endif /* ADC_H_ */
