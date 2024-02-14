/*
 * ADC.c
 *
 *  Created on: Feb 11, 2024
 *      Author: mw296
 */

#include "stm32f103x8.h"
#include "GPIO.h"
#include "ADC.h"

static uint8_t Pin_Position(uint16_t PinNumber) {
	switch (PinNumber) {
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 1;
		break;
	case GPIO_PIN_2:
		return 2;
		break;
	case GPIO_PIN_3:
		return 3;
		break;
	case GPIO_PIN_4:
		return 4;
		break;
	case GPIO_PIN_5:
		return 5;
		break;
	case GPIO_PIN_6:
		return 6;
		break;
	case GPIO_PIN_7:
		return 7;
		break;
	case GPIO_PIN_8:
		return 8;
		break;
	case GPIO_PIN_9:
		return 9;
		break;
	case GPIO_PIN_10:
		return 10;
		break;
	case GPIO_PIN_11:
		return 11;
		break;
	case GPIO_PIN_12:
		return 12;
		break;
	case GPIO_PIN_13:
		return 13;
		break;
	case GPIO_PIN_14:
		return 14;
		break;
	case GPIO_PIN_15:
		return 15;
		break;
	}
	return 0;
}

static void delay(uint32_t u) {
	int i = 0;
	int j = 0;
	for (i = 0; i < 10000; i++) {
		for (j = 0; j < u; j++)
			;
	}
}

uint8_t MCAL_ADC_Init(ADC_TypeDef *adcx, GPIO_TypeDef *gpiox, uint16_t pin) {
	uint8_t channel;
	if (gpiox == GPIOA) {
		if (pin >= GPIO_PIN_8) {
			return 0;
		}
		channel = Pin_Position(pin);
	}

	else if (gpiox == GPIOB) {
		if (pin >= GPIO_PIN_2) {
			return 0;
		}
		channel = Pin_Position(pin) + 8;
	} else if (gpiox == GPIOC) {
		if (pin >= GPIO_PIN_6) {
			return 0;
		}
		channel = Pin_Position(pin) + 10;
	}

	GPIO_PinConfig_t cfg;
	cfg.GPIO_PinNumber = pin;
	cfg.GPIO_MODE = GPIO_MODE_Analog;
	MCAL_GPIO_Init(gpiox, &cfg);

	adcx->ADC_SQR3 = channel;
	adcx->ADC_CR2 |= 1;
	delay(100);
	adcx->ADC_CR2 |= 1;
	adcx->ADC_CR2 |= 2;
	return 1;
}

uint8_t MCAL_ADC_EOC(ADC_TypeDef *adcx) {
	uint8_t check = 0;
	if (adcx->ADC_SR & 2) {
		check = 1;
	}
	return check;
}

uint32_t MCAL_ADC_Read(ADC_TypeDef *adcx, GPIO_TypeDef *gpiox, uint16_t pin) {
	int data = 0;
	data = adcx->ADC_DR;
	return data;
}
