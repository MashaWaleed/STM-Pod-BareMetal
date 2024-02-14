/*
 * SPI.c
 *
 *  Created on: Jan 28, 2024
 *      Author: mw296
 */

#include "SPI.h"
#include "GPIO.h"
#include "BIT_MATH.h"

/////////////////////////////////////////////////////////////////////////////
//                           GLOBAL VARIABLE                              //
////////////////////////////////////////////////////////////////////////////

SPI_Config_t *Global_SPI_CFG[2] = { NULL, NULL };

/////////////////////////////////////////////////////////////////////////////
//                                MACROS                                  //
////////////////////////////////////////////////////////////////////////////

#define SPI1_CFG                 0
#define SPI2_CFG                 1

/////////////////////////////////////////////////////////////////////////////
//                          Private functions                             //
////////////////////////////////////////////////////////////////////////////

static uint8_t CheckFlag_TXE(SPI_TypeDef *SPIx) {
	return (GET_BIT(SPIx->SPI_SR, 1));

}

static uint8_t CheckFlag_RXNE(SPI_TypeDef *SPIx) {
	return (GET_BIT(SPIx->SPI_SR, 0));
}
static uint8_t CheckFlag_ERR(SPI_TypeDef *SPIx) {
	return (GET_BIT(SPIx->SPI_SR, 4));
}

//static uint8_t CheckFlag_BSY(SPI_TypeDef *SPIx) {
//	return (GET_BIT(SPIx->SPI_SR, 7));
//}

/////////////////////////////////////////////////////////////////////////////
//                                A P I                                   //
////////////////////////////////////////////////////////////////////////////

void MCAL_SPI_Init(SPI_TypeDef *SPIx, SPI_Config_t *cfg) {
	// Temporary registers image for configurations to be mirrored onto without worrying about option precedence
	uint16_t tempregcr1 = 0;
	uint16_t tempregcr2 = 0;

	if (SPIx == SPI1) {
		Global_SPI_CFG[SPI1_CFG] = cfg;
	} else if (SPIx == SPI2) {
		Global_SPI_CFG[SPI2_CFG] = cfg;
	}
	tempregcr1 |= (0x1U << 6);

	tempregcr1 |= cfg->Device_Mode;
	tempregcr1 |= cfg->Com_Mode;
	tempregcr1 |= cfg->Frame_Format;
	tempregcr1 |= cfg->Data_Size;
	tempregcr1 |= cfg->CLK_POL;
	tempregcr1 |= cfg->CLK_PHA;
	tempregcr1 |= cfg->Baud_PS;
	tempregcr1 |= cfg->NSS;

	tempregcr2 |= cfg->IRQ_En;

	SPIx->SPI_CR1 = tempregcr1;
	SPIx->SPI_CR2 = tempregcr2;
}

void MCAL_SPI_GPIO_PINS(SPI_TypeDef *SPIx) {
	GPIO_PinConfig_t cfg;
	if (SPIx == SPI1) {
		// PA4 NSS
		// PA5 SCK
		// PA6 MISO
		// PA7 MOSI

		if (Global_SPI_CFG[SPI1_CFG]->Device_Mode == SPI_Device_Mode_Master) {

			//NSS TO DOOOOOOO I WILL JUST USE SW NIGGER

			// SCK PA5 AFPP
			cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			cfg.GPIO_PinNumber = GPIO_PIN_5;
			cfg.GPIO_Output_Speed = GPIO_SPEED_50M;
			MCAL_GPIO_Init(GPIOA, &cfg);

			// MISO PA6 AFPP only in bidirectional
			if (Global_SPI_CFG[SPI1_CFG]->Com_Mode == SPI_Com_Mode_2L) {
				cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				cfg.GPIO_PinNumber = GPIO_PIN_6;
				cfg.GPIO_Output_Speed = GPIO_SPEED_50M;
				MCAL_GPIO_Init(GPIOA, &cfg);
			}

			// MOSI PA7 AFPP
			cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			cfg.GPIO_PinNumber = GPIO_PIN_7;
			cfg.GPIO_Output_Speed = GPIO_SPEED_50M;
			MCAL_GPIO_Init(GPIOA, &cfg);

		} else {

			// SCK PA5 FLO
			cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			cfg.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIO_Init(GPIOA, &cfg);

			// MOSI PA7 FLO
			if (Global_SPI_CFG[SPI1_CFG]->Com_Mode == SPI_Com_Mode_2L) {
				cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				cfg.GPIO_PinNumber = GPIO_PIN_7;
				MCAL_GPIO_Init(GPIOA, &cfg);
			}

			// MISO PA6 AFPP
			cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			cfg.GPIO_PinNumber = GPIO_PIN_6;
			cfg.GPIO_Output_Speed = GPIO_SPEED_50M;
			MCAL_GPIO_Init(GPIOA, &cfg);

		}

	} else {
		// PB12 NSS
		// PB13 SCK
		// PB14 MISO
		// PB15 MOSI

		if (Global_SPI_CFG[SPI2_CFG]->Device_Mode == SPI_Device_Mode_Master) {

			//NSS TO DOOOOOOO I WILL JUST USE SW NIGGER

			// SCK PB13 AFPP
			cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			cfg.GPIO_PinNumber = GPIO_PIN_13;
			cfg.GPIO_Output_Speed = GPIO_SPEED_50M;
			MCAL_GPIO_Init(GPIOB, &cfg);

			// MISO PB14 AFPP only in bidirectional
			if (Global_SPI_CFG[SPI1_CFG]->Com_Mode == SPI_Com_Mode_2L) {
				cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				cfg.GPIO_PinNumber = GPIO_PIN_14;
				cfg.GPIO_Output_Speed = GPIO_SPEED_50M;
				MCAL_GPIO_Init(GPIOB, &cfg);
			}

			// MOSI PB15 AFPP
			cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			cfg.GPIO_PinNumber = GPIO_PIN_15;
			cfg.GPIO_Output_Speed = GPIO_SPEED_50M;
			MCAL_GPIO_Init(GPIOB, &cfg);

		} else {

			// SCK PB13 FLO
			cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			cfg.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIO_Init(GPIOB, &cfg);

			// MOSI PB14 FLO
			if (Global_SPI_CFG[SPI1_CFG]->Com_Mode == SPI_Com_Mode_2L) {
				cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				cfg.GPIO_PinNumber = GPIO_PIN_14;
				MCAL_GPIO_Init(GPIOB, &cfg);
			}

			// MISO PB15 AFPP
			cfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			cfg.GPIO_PinNumber = GPIO_PIN_15;
			cfg.GPIO_Output_Speed = GPIO_SPEED_50M;
			MCAL_GPIO_Init(GPIOB, &cfg);

		}

	}
}

// this only really works in full duplux 2 line uindirectional , or 1 line unidirectional, bidirectional requires more logic (i think ?)

void MCAL_SPI_TX(SPI_TypeDef *SPIx, uint8_t *Pdata, uint16_t size) {
	uint16_t tempctr = 1;
	uint8_t *tempPdata = Pdata;

	while (!CheckFlag_TXE(SPIx))
		;

	SPIx->SPI_DR = *tempPdata;
	tempPdata += sizeof(uint8_t);
	tempctr++;

	while (tempctr <= size) {
		if (CheckFlag_TXE(SPIx)) {
			SPIx->SPI_DR = *tempPdata;
			tempPdata += sizeof(uint8_t);
			tempctr++;
		}
	}

	// TO DO WAIT FOR END OF TRANSMITTION --> BUSY FLAG "MAYBE UNNECESSARY"

	//while(CheckFlag_BSY);

}
void MCAL_SPI_RX(SPI_TypeDef *SPIx, uint8_t *Pdata, uint16_t size) {

	uint16_t tempctr = 1;

	while (!CheckFlag_RXNE(SPIx))
		;

	*Pdata = SPIx->SPI_DR;
	Pdata += sizeof(uint8_t);
	tempctr++;

	while (tempctr <= size) {
		if (CheckFlag_RXNE(SPIx)) {
			*Pdata = SPIx->SPI_DR;
			Pdata += sizeof(uint8_t);
			tempctr++;
		}
	}

	// TO DO WAIT FOR END OF TRANSMITTION --> BUSY FLAG "MAYBE UNNECESSARY"

	//while(CheckFlag_BSY);

}

void MCAL_SPI_TX_IT(SPI_TypeDef *SPIx, uint8_t *Pdata, uint16_t size) {

	uint16_t tempctr = 1;

	SPIx->SPI_DR = *Pdata;
	Pdata += sizeof(uint8_t);
	tempctr++;

	while (tempctr <= size) {
		if (CheckFlag_TXE(SPIx)) {
			SPIx->SPI_DR = *Pdata;
			Pdata += sizeof(uint8_t);
			tempctr++;
		}
	}

}
void MCAL_SPI_RX_IT(SPI_TypeDef *SPIx, uint8_t *Pdata, uint16_t size) {

	uint16_t tempctr = 1;

	*Pdata = SPIx->SPI_DR;
	Pdata += sizeof(uint8_t);
	tempctr++;

	while (tempctr <= size) {
		if (CheckFlag_RXNE(SPIx)) {
			*Pdata = SPIx->SPI_DR;
			Pdata += sizeof(uint8_t);
			tempctr++;
		}
	}
}

void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint8_t *Pdata, uint16_t size) {

}
void MCAL_SPI_TX_RX_IT(SPI_TypeDef *SPIx, uint8_t *Pdata, uint16_t size) {

}

/////////////////////////////////////////////////////////////////////////////
//                                I R Q                                   //
////////////////////////////////////////////////////////////////////////////

void SPI1_IRQHandler(void) {
	struct SPI_IRQ_SRC src;

	src.TXE = CheckFlag_TXE(SPI1);
	src.RXNE = CheckFlag_RXNE(SPI1);
	src.ERRI = CheckFlag_ERR(SPI1);

	Global_SPI_CFG[SPI1_CFG]->P_IRq_CallBack(src);
}

void SPI2_IRQHandler(void) {
	struct SPI_IRQ_SRC src;

	src.TXE = CheckFlag_TXE(SPI2);
	src.RXNE = CheckFlag_RXNE(SPI2);
	src.ERRI = CheckFlag_ERR(SPI2);

	Global_SPI_CFG[SPI2_CFG]->P_IRq_CallBack(src);
}
