/*
 * keypad.h
 *
 *  Created on: Aug 31, 2023
 *      Author: mw296
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32f103x8.h"
#include "GPIO.h"

#define KEYPAD_PORT GPIOB
#define ROW         4U
#define COL         4U

#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8


void Keypad_init();
uint8_t Keypad_getkey();

#endif /* KEYPAD_H_ */
