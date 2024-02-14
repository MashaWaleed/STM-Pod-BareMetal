/*
 * Ticker.c
 *
 *  Created on: Jan 31, 2024
 *      Author: mw296
 */

#include "Ticker.h"
#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "NVIC_Interface.h"
#include "stm32f103x8.h"

static volatile uint32_t elapsed_ms = 0;

void TIM2_IRQHandler(void) {
	elapsed_ms += 1000;
	TIMER2->SR &= ~1;
}

void Ticker_Init(void) {
	MCAL_RCC_EnablePeripheral(RCC_APB1, RCC_APB1ENR_TIM2EN);
	MCAL_NVIC_EnableIRQ(NVIC_TIM2_IRQn);
	TIMER2->DIER |= 1;

	TIMER2->PSC = 15999;
	TIMER2->ARR = 1000;

}

void Ticker_Start(void) {
	TIMER2->CR1 |= 1;
}

void Ticker_Stop(void) {
	TIMER2->CR1 &= ~1;
}

void Ticker_Reset_Count(void) {
	elapsed_ms = 0;
	TIMER2->CNT = 0;
}

uint32_t Get_ms(void) {

	return (elapsed_ms + TIMER2->CNT);
}

void Ticker_ms(uint32_t ms) {
	Ticker_Stop();
	Ticker_Reset_Count();
	Ticker_Start();

	while (Get_ms() < ms)
		;
	Ticker_Stop();
	Ticker_Reset_Count();
}
