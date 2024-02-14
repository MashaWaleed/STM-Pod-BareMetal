/*
 * GPIO.h
 *
 *  Created on: Aug 31, 2023
 *      Author: mw296
 */

#ifndef GPIO_H_
#define GPIO_H_


//includes
#include "stm32f103x8.h"

//============================================================================

//Config structure
typedef struct
{
	//Specifies the GPIO Pins to be configured
	//This parameter must be set based on @ref GPIO_PINS_define
	uint16_t GPIO_PinNumber;

	//Specifies the Operating mode for the selected pins
	//This parameter can be a value of @ref GPIO_MODE_define
	uint8_t GPIO_MODE;

	//Specifies the speed mode for the selected pins
	//This parameter can be a value of @ref GPIO_SPEED_define
	uint8_t GPIO_Output_Speed;

}GPIO_PinConfig_t;



//======================
//Macro Config Ref
//======================
//@ref GPIO_PINS_define

#define GPIO_PIN_0				((uint16_t)0x0001)
#define GPIO_PIN_1				((uint16_t)0x0002)
#define GPIO_PIN_2				((uint16_t)0x0004)
#define GPIO_PIN_3				((uint16_t)0x0008)
#define GPIO_PIN_4				((uint16_t)0x0010)
#define GPIO_PIN_5				((uint16_t)0x0020)
#define GPIO_PIN_6				((uint16_t)0x0040)
#define GPIO_PIN_7				((uint16_t)0x0080)
#define GPIO_PIN_8				((uint16_t)0x0100)
#define GPIO_PIN_9				((uint16_t)0x0200)
#define GPIO_PIN_10			    ((uint16_t)0x0400)
#define GPIO_PIN_11			   	((uint16_t)0x0800)
#define GPIO_PIN_12				((uint16_t)0x1000)
#define GPIO_PIN_13				((uint16_t)0x2000)
#define GPIO_PIN_14				((uint16_t)0x4000)
#define GPIO_PIN_15				((uint16_t)0x8000)
#define GPIO_PIN_All			((uint16_t)0xFFFF)  // All Pins Selected

#define GPIO_PINS_MASK			0x0000FFFFu  /* Pin mask for assert test */


//@ref GPIO_MODE_define

//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function input

#define GPIO_MODE_Analog			0x00000000u 	 //Analog mode
#define GPIO_MODE_INPUT_FLO 		0x00000001u 	 //Floating input
#define GPIO_MODE_INPUT_PU			0x00000002u 	 //Input with pull-up
#define GPIO_MODE_INPUT_PD			0x00000003u 	 //Input with pull-down
#define GPIO_MODE_OUTPUT_PP			0x00000004u 	 //General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD			0x00000005u 	 //General purpose output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP		0x00000006u 	 //Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD		0x00000007u 	 //Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT			0x00000008u 	 //Alternate function input



//@ref GPIO_SPEED_define

//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.

#define GPIO_SPEED_10M     0x00000001u       //1: Output mode, max speed 10 MHz.
#define GPIO_SPEED_2M      0x00000002u       //2: Output mode, max speed 2 MHz.
#define GPIO_SPEED_50M     0x00000003u      //3: Output mode, max speed 50 MHz.


//@ref GPIO_PIN_state
#define GPIO_PIN_SET       1
#define GPIO_PIN_RESET     0

//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_Enabled    1
#define GPIO_RETURN_LOCK_ERROR  	0



/*
 *===========================================================================
 *                      APIS FOR MCAL GPIO DRIVER
 *==========================================================================
 */


void MCAL_GPIO_Init (GPIO_TypeDef* GPIOX , GPIO_PinConfig_t * pinconfig);
void MCAL_GPIO_DeInit (GPIO_TypeDef* GPIOX );

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOX , uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOX );

void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOX , uint16_t PinNumber, uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOX , uint16_t value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOX , uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOX , uint16_t PinNumber);

#endif /* STM32F103C8_DRIVERS_GPIO_INC_GPIO_H_ */
