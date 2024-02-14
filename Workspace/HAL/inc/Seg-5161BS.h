/*
 * 5161BS.h
 *
 *  Created on: Sep 25, 2023
 *      Author: mw296
 */

#ifndef SEG_5161BS_H_
#define SEG_5161BS_H_

#define SEG_PORT    GPIOB

#define SEG_A		GPIO_PIN_8
#define SEG_C		GPIO_PIN_14
#define SEG_B		GPIO_PIN_9
#define SEG_D		GPIO_PIN_15
#define SEG_E		GPIO_PIN_5
#define SEG_G		GPIO_PIN_6
#define SEG_F		GPIO_PIN_7

void HAL_SEG_init();
void HAL_SEG_DisplayNumber(u8 num);
void HAL_SEG_DisplayLED(u16 num);



#endif /* 5161BS_H_ */
