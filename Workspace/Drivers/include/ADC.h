/*
 * ADC.h
 *
 *  Created on: Feb 11, 2024
 *      Author: mw296
 */

#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_


/*

PC0 -- >PC5   ADC12_IN10 -->  ADC12_IN_15

PA0 --> PA7   ADC12_IN0  -->  ADC12_IN7

PB0 --> PB1   ADC12_IN8  -->  ADC12_IN9

*/

uint8_t MCAL_ADC_Init(ADC_TypeDef *adcx, GPIO_TypeDef *gpiox, uint16_t pin);
uint8_t MCAL_ADC_EOC(ADC_TypeDef *adcx);
uint32_t MCAL_ADC_Read(ADC_TypeDef *adcx, GPIO_TypeDef *gpiox, uint16_t pin);

#endif /* INCLUDE_ADC_H_ */
