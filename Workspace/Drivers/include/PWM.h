/*
 * PWM.h
 *
 *  Created on: Feb 16, 2024
 *      Author: mw296
 */

#ifndef INCLUDE_PWM_H_
#define INCLUDE_PWM_H_
#include "stdint.h"

void PWM_Init(uint32_t duty);
void PWM_Duty(uint32_t duty);
void PWM_Freq(uint32_t freq);
void PWM_Start(void);
void PWM_Stop(void);

#endif /* INCLUDE_PWM_H_ */
