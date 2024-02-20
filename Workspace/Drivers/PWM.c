/*
 * PWM.c
 *
 *  Created on: Feb 16, 2024
 *      Author: mw296
 */
#include"STD_TYPES.h"
#include "stm32f103x8.h"
#include "GPIO.h"
#include "RCC_interface.h"

#include "PWM.h"


void PWM_Init(uint32_t duty)
{
	MCAL_RCC_EnablePeripheral(RCC_APB2, RCC_APB2ENR_TIM1EN);
	GPIO_PinConfig_t cfg;
	cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
	cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	cfg.GPIO_PinNumber = GPIO_PIN_8;

	MCAL_GPIO_Init(GPIOA, &cfg);

	TIMER1->PSC = (16 - 1);
	TIMER1->ARR = 60000;
	TIMER1->CNT = 0;

	TIMER1->CCMR1 |= 0x60;

	TIMER1->CCER |= 0x3;

	TIMER1->BDTR |= 0x8000;

	TIMER1->CCR1 = duty ;
}
void PWM_Duty(uint32_t duty)
{
	TIMER1->CCR1 = duty ;
}

void PWM_Freq(uint32_t newFreq)
{
	uint32_t tempFreq = newFreq;
		if(newFreq == 0) tempFreq = 1;

		uint32_t tempNewValue = 16000000/ 16 / tempFreq;

		// setting new value
		TIMER1 ->ARR = (uint32_t)tempNewValue;
		TIMER1 -> CCR1 = (uint32_t)tempNewValue/2;
}

void PWM_Start(void)
{
	TIMER1->CR1 |= 1;
}

void PWM_Stop(void)
{
	TIMER1->CR1 &= ~1;
}
