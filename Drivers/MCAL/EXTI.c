/*
 * EXTI.c
 *
 *  Created on: Sep 2, 2023
 *      Author: mw296
 */

#include "EXTI.h"

/*
 * =======================================================================================
 * 										GLOBAL VARIABLES
 * =======================================================================================
 */

	void (*GP_IRQ_Callback[15])(void);
/*
 * =======================================================================================
 * 										GENERIC MACROS
 * =======================================================================================
 */

#define AFIO_GPIO_EXTI_Mapping(x)	((x==GPIOA)?0:\
									(x==GPIOB)?1:\
									(x==GPIOC)?2:\
									(x==GPIOD)?3:0)
/*
 * =======================================================================================
 * 										GENERIC FUNCTIONS
 * =======================================================================================
 */
void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ){
		case EXTI0:
			NVIC_IRQ6_EXTI0_Enable();
			break;
		case EXTI1:
			NVIC_IRQ7_EXTI1_Enable();
			break;
		case EXTI2:
			NVIC_IRQ8_EXTI2_Enable();
			break;
		case EXTI3:
			NVIC_IRQ9_EXTI3_Enable();
			break;
		case EXTI4:
			NVIC_IRQ10_EXTI4_Enable();
			break;
		case EXTI5:
		case EXTI6:
		case EXTI7:
		case EXTI8:
		case EXTI9:
			NVIC_IRQ23_EXTI5_9_Enable();
			break;
		case EXTI10:
		case EXTI11:
		case EXTI12:
		case EXTI13:
		case EXTI14:
		case EXTI15:
			NVIC_IRQ40_EXTI10_15_Enable();
			break;
		}
}
void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
		{
		case EXTI0:
			NVIC_IRQ6_EXTI0_Disable();
			break;

		case EXTI1:
			NVIC_IRQ7_EXTI1_Disable();
			break;

		case EXTI2:
			NVIC_IRQ8_EXTI2_Disable();
			break;

		case EXTI3:
			NVIC_IRQ9_EXTI3_Disable();
			break;

		case EXTI4:
			NVIC_IRQ10_EXTI4_Disable();
			break;

		case EXTI5:
		case EXTI6:
		case EXTI7:
		case EXTI8:
		case EXTI9:
			NVIC_IRQ23_EXTI5_9_Disable();
			break;

		case EXTI10:
		case EXTI11:
		case EXTI12:
		case EXTI13:
		case EXTI14:
		case EXTI15:
			NVIC_IRQ40_EXTI10_15_Disable();
			break;
		}
}



/*
 * =======================================================================================
 * 							APIs Supported by "MCAL EXTI DRIVER"
 * =======================================================================================
 */



/*=====================================================================
 * @Fn				- MCAL_EXTI_GPIO_Init
 * @brief 			- this is used to Initializes the EXTI from specific GPIO PIN and specify the Mask/Trigger condition and IRQ CallBack
 * @param [in] 		- EXTI_Config set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval			- none
 * Note				- stm32F103c6 MCU has GPIO A,B,C,D,E Modules
 * 					- but LQFP48 package has only GPIO A,B,Part of C/D exported as external PINS from the MCU
 * 					- Also Mandatory to enable RCC clock for AFIO and corresponding GPIO
 */

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t * EXTI_CFG)
{
	MCAL_EXTI_GPIO_Update(EXTI_CFG);
}

/*=====================================================================
 * @Fn				- MCAL_EXTI_GPIO_DeInit
 * @brief 			- this is used to reset all EXTI registersand disable all NVIC
 * @param [in] 		- none
 * @retval			- none
 * Note				-none
 */



void MCAL_EXTI_GPIO_Deinit(void)
{
	//Disable masks
	EXTI->IMR = 0x00000000;
	EXTI->EMR = 0x00000000;
	//reset trigger
	EXTI->RTSR = 0x00000000;
	EXTI->FTSR = 0x00000000;

	EXTI->SWIER = 0x00000000;

	EXTI->PR = 0xFFFFFFFF;

	//reset pin select for every EXTI line

	AFIO->EXTICR[0] = 0x00000000;
	AFIO->EXTICR[1] = 0x00000000;
	AFIO->EXTICR[2] = 0x00000000;
	AFIO->EXTICR[3] = 0x00000000;

	//DISABLE NVIC

	NVIC_IRQ6_EXTI0_Disable();
	NVIC_IRQ7_EXTI1_Disable();
	NVIC_IRQ8_EXTI2_Disable();
	NVIC_IRQ9_EXTI3_Disable();
	NVIC_IRQ10_EXTI4_Disable();
	NVIC_IRQ23_EXTI5_9_Disable();
	NVIC_IRQ40_EXTI10_15_Disable();

}





void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t * EXTI_CFG)
{
	//CONFIG PIN to be GPIO INPUT

	GPIO_PinConfig_t PinCfg;
	PinCfg.GPIO_PinNumber = EXTI_CFG->EXTI_Pin.GPIO_Pin;
	PinCfg.GPIO_MODE = EXTI_CFG->PULL_RES;
	MCAL_GPIO_Init(EXTI_CFG->EXTI_Pin.GPIO_Port, &PinCfg);


	//Set AFIO \ update the routing
	uint8_t AFIO_EXTICR_Index = EXTI_CFG->EXTI_Pin.EXTI_LineNumber/4;              //afio reg
	uint8_t AFIO_EXTICR_Position = (EXTI_CFG->EXTI_Pin.EXTI_LineNumber%4) * 4;    //line count in reg :)

	//clear then update the  4 bit first
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF<<AFIO_EXTICR_Position);
	AFIO->EXTICR[AFIO_EXTICR_Index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_CFG->EXTI_Pin.GPIO_Port) & 0xF)<<AFIO_EXTICR_Position);

	//clear rise and fall
	EXTI->RTSR &= ~(1<<EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
	EXTI->FTSR &= ~(1<<EXTI_CFG->EXTI_Pin.EXTI_LineNumber);

	//rising or falling ?
	if(EXTI_CFG->TriggerCase == EXTI_TriggerRising)
	{
		EXTI->RTSR |=  (1<<EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
		EXTI->FTSR &= ~(1<<EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
	}
	else if(EXTI_CFG->TriggerCase == EXTI_TriggerFalling)
	{
		EXTI->RTSR &= ~(1<<EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
		EXTI->FTSR |= (1<<EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
	}
	else if(EXTI_CFG->TriggerCase == EXTI_TriggerRisingAndFalling)
	{
		EXTI->RTSR |= (1<<EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
		EXTI->FTSR |= (1<<EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
	}

	//UPDATE IRQ CALLBACK
	GP_IRQ_Callback[EXTI_CFG->EXTI_Pin.EXTI_LineNumber] = EXTI_CFG->P_IRQ_CallBack;

	//EN/DIS IRQ
	if(EXTI_CFG->IRQ_EN == EXTI_IRQ_Enable)
	{
		SET_BIT(EXTI->IMR, EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
		Enable_NVIC(EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
	}

	else
	{
		CLR_BIT(EXTI->IMR, EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
		Disable_NVIC(EXTI_CFG->EXTI_Pin.EXTI_LineNumber);
	}
}


/*
 * =======================================================================================
 * 										ISR FUNCTIONS
 * =======================================================================================
 */


void EXTI0_IRQHandler(void){
	//clear the corresponding pending bit
	EXTI->PR = 1<<0;
	//callback funtion
	GP_IRQ_Callback[0]();
}


void EXTI1_IRQHandler(void){
	//clear the corresponding pending bit
	EXTI->PR = 1<<1;
	//callback funtion
	GP_IRQ_Callback[1]();
}

void EXTI2_IRQHandler(void){
	//clear the corresponding pending bit
	EXTI->PR = 1<<2;
	//callback funtion
	GP_IRQ_Callback[2]();
}

void EXTI3_IRQHandler(void){
	//clear the corresponding pending bit
	EXTI->PR = 1<<3;
	//callback funtion
	GP_IRQ_Callback[3]();
}



void EXTI4_IRQHandler(void){
	//clear the corresponding pending bit
	EXTI->PR = 1<<4;
	//callback funtion
	GP_IRQ_Callback[4]();
}



void EXTI9_5_IRQHandler(void){

	if(EXTI->PR & 1<<5) { EXTI->PR  = 1<<5;   GP_IRQ_Callback[5](); }
	if(EXTI->PR & 1<<6) { EXTI->PR  = 1<<6;   GP_IRQ_Callback[6](); }
	if(EXTI->PR & 1<<7) { EXTI->PR  = 1<<7;   GP_IRQ_Callback[7](); }
	if(EXTI->PR & 1<<8) { EXTI->PR  = 1<<8;   GP_IRQ_Callback[8](); }
	if(EXTI->PR & 1<<9) { EXTI->PR  = 1<<9;   GP_IRQ_Callback[9](); }
}



void EXTI15_10_IRQHandler(void){

	if( EXTI->PR & 1<<10 ) { EXTI->PR |= 1<<10; GP_IRQ_Callback[10](); }
	if( EXTI->PR & 1<<11 ) { EXTI->PR |= 1<<11; GP_IRQ_Callback[11](); }
	if( EXTI->PR & 1<<12 ) { EXTI->PR |= 1<<12; GP_IRQ_Callback[12](); }
	if( EXTI->PR & 1<<13 ) { EXTI->PR |= 1<<13; GP_IRQ_Callback[13](); }
	if( EXTI->PR & 1<<14 ) { EXTI->PR |= 1<<14; GP_IRQ_Callback[14](); }
	if( EXTI->PR & 1<<14 ) { EXTI->PR |= 1<<15; GP_IRQ_Callback[15](); }
}



