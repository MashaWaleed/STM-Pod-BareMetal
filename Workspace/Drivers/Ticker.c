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

/////////// PROGRESS SECTION ///////////////

void TIM2_IRQHandler(void) {
	elapsed_ms += 1000;
	TIMER2->SR &= ~1;
}

void Ticker_Init(void) {
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


//////////////  PRE DELAY SECTION  //////////////////

void Ticker_us(uint32_t us) {
	TIMER2->CNT = 0;
	TIMER2->PSC = (16 -1);

	TIMER2->ARR = (us - 1);
	TIMER2->CR1 |= 0x9;

	while(TIMER2->CR1 & 1);
}



void Ticker_ms(uint32_t ms)
{

	int i;
	for(i = 0; i<ms; i++)
	{
		Ticker_us(1000);
	}

	// RESET CONFIGURTIONS FOR TICKER INIT
	TIMER2->CR1 &= ~(1<<3); //zero out opm option
}
