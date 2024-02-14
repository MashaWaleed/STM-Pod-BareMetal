/*
 * Ticker.h
 *
 *  Created on: Jan 31, 2024
 *      Author: mw296
 */

#ifndef TICKER_H_
#define TICKER_H_
#include <stdint.h>

void Ticker_Init(void);
void Ticker_Start(void);
void Ticker_Stop(void);
void Ticker_Reset_Count(void);
uint32_t Get_ms(void);
void Ticker_ms(uint32_t ms);

#endif /* TICKER_H_ */
