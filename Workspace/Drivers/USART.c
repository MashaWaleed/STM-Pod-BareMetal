/*
 * USART.c
 *
 *  Created on: Sep 29, 2023
 *      Author: mw296
 */

/*********< LIB *************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "stm32f103x8.h"

/*********< MCAL *************/
#include "RCC_interface.h"
#include "GPIO.h"
#include "USART.h"
#include "NVIC_Interface.h"

/*************<Global Variables***********/
USART_Config_t *Global_USART_Config[3] = { NULL };


/*************<Private Helper Functions***********/

static uint8_t GetIndex(USART_TypeDef *USARTx)
{
	if(USARTx == USART1){
		return 0;
	}
	else if(USARTx == USART2)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

/*************<Implementation***********/

void MCAL_USART_Init(USART_TypeDef *USARTx, USART_Config_t *config) {
	u32 pclk, BRR;

	uint8_t LocalIndex = GetIndex(USARTx);
	Global_USART_Config[LocalIndex] = config;
	//EN USART
	USARTx->CR1 |= 1 << 13;
	//Enable TX or RX or both
	USARTx->CR1 |= config->USART_Mode;
	//Configure Parity width
	USARTx->CR1 |= config->PayLoadLength;
	//configure Parity bit
	USARTx->CR1 |= config->Parity;
	//configure Stop bits
	USARTx->CR2 |= config->StopBits;
	//configure Flow Control
	USARTx->CR3 |= config->FlowCTRL;
	//configure Baud Rate
	//call RCC get clk to know the clock for which you will calculate the baud rate
	if (USARTx == USART1) {
		pclk = MCAL_RCC_GetPCLK2();
	} else {
		pclk = MCAL_RCC_GetPCLK1();
	}
	BRR = UART_BRR_VALUE(pclk, config->BaudRate);
	USARTx->BRR = BRR;

	//Enable or Disable interrupt
	if (config->IRQ_Enable != USART_IRQ_ENABLE_NONE) {
		USARTx->CR1 |= (config->IRQ_Enable);
	}

	//NVIC is handled separately as well as RCC initialization
}

void MCAL_USART_DeInit(USART_TypeDef *USARTx) {
	if (USARTx == USART1) {
		MCAL_RCC_DisablePeripheral(RCC_APB2, RCC_APB2ENR_USART1EN);
		MCAL_NVIC_DisableIRQ(NVIC_USART1_IRQn);
	} else if (USARTx == USART2) {
		MCAL_RCC_DisablePeripheral(RCC_APB2, RCC_APB1ENR_USART2EN);
		MCAL_NVIC_DisableIRQ(NVIC_USART2_IRQn);
	} else if (USARTx == USART3) {
		MCAL_RCC_DisablePeripheral(RCC_APB2, RCC_APB1ENR_USART3EN);
		MCAL_NVIC_DisableIRQ(NVIC_USART3_IRQn);
	}
}

void MCAL_USART_Send_Data(USART_TypeDef *USARTx, uint16_t *pTxBuffer,
		enum Polling_Mechanism PollingEN, uint8_t size) {
	uint8_t temp_cnt = 1;
	uint8_t LocalIndex = GetIndex(USARTx);
	while (temp_cnt <= size) {
		if (PollingEN == enable) {
			while (!(USARTx->SR & 1 << 7))
				;
		}
		if (Global_USART_Config[LocalIndex]->PayLoadLength == USART_DATA_9bits) {
			USARTx->DR = (*pTxBuffer & (u16) 0x1FF);
			pTxBuffer += 1;
			temp_cnt++;
		} else {
			USARTx->DR = (*pTxBuffer & (u8) 0xFF);
			pTxBuffer += 1;
			temp_cnt++;
		}
	}

}

void MCAL_USART_WAIT_TC(USART_TypeDef *USARTx) {
	while (!(USARTx->SR & 1 << 6))
		;
}

void MCAL_USART_Get_Data(USART_TypeDef *USARTx, uint16_t *pRxBuffer,
		enum Polling_Mechanism PollingEN) {
	uint8_t LocalIndex = GetIndex(USARTx);
	if (PollingEN == enable) {
		while (!(USARTx->SR & 1 << 5))
			;
	}

	if (Global_USART_Config[LocalIndex]->PayLoadLength == USART_DATA_9bits) {
		if (Global_USART_Config[LocalIndex]->Parity == USART_PARITY_NONE) {
			*((u16*) pRxBuffer) = USARTx->DR;
		}

		else {
			*((u16*) pRxBuffer) = (USARTx->DR & (u8) 0xFF);
		}
	} else {
		if (Global_USART_Config[LocalIndex]->Parity == USART_PARITY_NONE) {
			*((u16*) pRxBuffer) = (USARTx->DR & (u8) 0xFF);
		}

		else {
			*((u16*) pRxBuffer) = (USARTx->DR & (u8) 0x7F);
		}
	}
}

void MCAL_USART_GPIO_SetPins(USART_TypeDef *USARTx) {
	GPIO_PinConfig_t cfg;
	if (USARTx == USART1) {
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		cfg.GPIO_PinNumber = GPIO_PIN_9;
		cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		cfg.GPIO_Output_Speed = GPIO_SPEED_2M;
		MCAL_GPIO_Init(GPIOA, &cfg);

		//PA10 RX
		cfg.GPIO_PinNumber = GPIO_PIN_10;
		cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOA, &cfg);

		//PA11 CTS
		if (Global_USART_Config[0]->FlowCTRL == USART_FLOW_CTRL_CTS
				|| Global_USART_Config[0]->FlowCTRL
						== USART_FLOW_CTRL_CTS_RTS) {
			cfg.GPIO_PinNumber = GPIO_PIN_11;
			cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &cfg);
		}

		//PA12 RTS
		if (Global_USART_Config[0]->FlowCTRL == USART_FLOW_CTRL_RTS
				|| Global_USART_Config[0]->FlowCTRL
						== USART_FLOW_CTRL_CTS_RTS) {
			cfg.GPIO_PinNumber = GPIO_PIN_12;
			cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &cfg);

		}
	} else if (USARTx == USART2) {
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS

		//PA2 TX
		cfg.GPIO_PinNumber = GPIO_PIN_2;
		cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &cfg);

		//PA3 RX
		cfg.GPIO_PinNumber = GPIO_PIN_3;
		cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOA, &cfg);

		//PA0 CTS
		if (Global_USART_Config[1]->FlowCTRL == USART_FLOW_CTRL_CTS
				|| Global_USART_Config[1]->FlowCTRL
						== USART_FLOW_CTRL_CTS_RTS) {
			cfg.GPIO_PinNumber = GPIO_PIN_0;
			cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &cfg);
		}

		//PA1 RTS
		if (Global_USART_Config[1]->FlowCTRL == USART_FLOW_CTRL_RTS
				|| Global_USART_Config[1]->FlowCTRL
						== USART_FLOW_CTRL_CTS_RTS) {
			cfg.GPIO_PinNumber = GPIO_PIN_1;
			cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &cfg);

		}
	} else if (USARTx == USART3) {
		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PB14 RTS

		//PB10 TX
		cfg.GPIO_PinNumber = GPIO_PIN_10;
		cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &cfg);

		//PB11 RX
		cfg.GPIO_PinNumber = GPIO_PIN_11;
		cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(GPIOB, &cfg);

		//PB13 CTS
		if (Global_USART_Config[2]->FlowCTRL == USART_FLOW_CTRL_CTS
				|| Global_USART_Config[2]->FlowCTRL
						== USART_FLOW_CTRL_CTS_RTS) {
			cfg.GPIO_PinNumber = GPIO_PIN_13;
			cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &cfg);
		}

		//PB14 RTS
		if (Global_USART_Config[2]->FlowCTRL == USART_FLOW_CTRL_RTS
				|| Global_USART_Config[2]->FlowCTRL
						== USART_FLOW_CTRL_CTS_RTS) {
			cfg.GPIO_PinNumber = GPIO_PIN_14;
			cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &cfg);

		}
	}
}

//ISR
void USART1_IRQHandler(void) {
	Global_USART_Config[0]->P_IRQ_CallBack();
}

void USART2_IRQHandler(void) {
	Global_USART_Config[1]->P_IRQ_CallBack();
}

void USART3_IRQHandler(void) {
	Global_USART_Config[2]->P_IRQ_CallBack();
}
