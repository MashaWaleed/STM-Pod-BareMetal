/*
 * SPI.h
 *
 *  Created on: Jan 28, 2024
 *      Author: mw296
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f103x8.h"
#include "GPIO.h"


struct SPI_IRQ_SRC
{
	uint8_t TXE:1;
	uint8_t RXNE:1;
	uint8_t ERRI:1;
	uint8_t Reserved:5;
};


//CONFIG STRUCT
typedef struct
{
	uint16_t	Device_Mode;             // SPI operating mode  @ref dev_mode
	uint16_t	Com_Mode;				 // specify bidirectional mode state @ref com_mode
	uint16_t	Frame_Format;			 // LSB OR MSB ? @ref frame_form
	uint16_t	Data_Size;				 // 8 or 16 ? @ref data_size
	uint16_t	CLK_POL;				 // high or low ? @ref clk_Pol
	uint16_t	CLK_PHA;				 // 1st or 2nd ? @ref clk_pha
	uint16_t	NSS;					 // slave select hard or soft ? @ref nss
	uint16_t	Baud_PS;                 // prescaler @ref PS
	uint16_t	IRQ_En;          		 // @ref irq_en
	void (* P_IRq_CallBack)(struct SPI_IRQ_SRC irq_src);

}SPI_Config_t;


/////////////////////////////////////////////////////////////////////////////
//                              REFRENCE MACROS                           //
////////////////////////////////////////////////////////////////////////////

// @ref dev_mode
//all spi cr1, MSTR bit
#define SPI_Device_Mode_Slave             (0x00000000)
#define SPI_Device_Mode_Master            (0x1U<<2)

// @ref com mode
// all spi cr1, BIDIMODE --> LINES, BIDIOE --> RX OR TX ONLY IN ONE LINE BIDIRECTIONAL, ONLY MOSI IN MASTER MODE AND MISO IN SLAVE MODE?
#define SPI_Com_Mode_2L                   (0x00000000)        //FULL DUPLUEX TWO LINE MISO MOSI
#define SPI_Com_Mode_2L_RX				  (0x1U<<10)          //2 line but only receive
#define SPI_Com_Mode_1L_RX				  (0x1U<<15)
#define SPI_Com_Mode_1L_TX                (0x1U<<15) | (0x1U<<14)

// @ref frame_form
//cr1 LSB
#define SPI_Frame_Format_LSB              (0x1U<<7)
#define SPI_Frame_Format_MSB              (0X00000000)

// @ref data_size
//cr1 DFF
#define SPI_Data_Size_8                   (0x00000000)
#define SPI_Data_Size_16                  (0x1U<<11)

// @ref clk_pol
//cr1 , cpol 1
#define SPI_CLK_POL_Low                   (0x00000000)
#define SPI_CLK_POL_High                  (0x1U<<1)

// @ref clk_pha
//cr1 cpha 0
#define SPI_CLK_PHA_1					  (0x00000000)
#define SPI_CLK_PHA_2                     (0x1U<<0)

//@ref nss
//cr1
#define SPI_NSS_Software_En_Reset         (0x1U<<9)
#define SPI_NSS_Software_En_Set           (0x1U<<9) | (0x1U<<8)

//@ref PS
//cr1
#define SPI_Baud_PS_2                     (0x00000000)
#define SPI_Baud_PS_4                     (0x8U)
#define SPI_Baud_PS_8                     (0x10U)
#define SPI_Baud_PS_16                    (0x18U)
#define SPI_Baud_PS_32                    (0x20U)
#define SPI_Baud_PS_64					  (0x28U)
#define SPI_Baud_PS_128                   (0x30U)
#define SPI_Baud_PS_256		              (0x38U)

//@ref irq_en
//cr2
#define SPI_IRQ_NONE                     (0x00000000)
#define SPI_IRQ_TXE                      (0x1U<<7)
#define SPI_IRQ_RXNE                     (0x1U<<6)
#define SPI_IRQ_ERR                      (0x1U<<5)


/////////////////////////////////////////////////////////////////////////////
//                                A P I                                   //
////////////////////////////////////////////////////////////////////////////

void MCAL_SPI_Init(SPI_TypeDef * SPIx, SPI_Config_t * cfg);
void MCAL_SPI_GPIO_PINS(SPI_TypeDef * SPIx);


void MCAL_SPI_TX(SPI_TypeDef * SPIx, uint8_t * Pdata, uint16_t size);
void MCAL_SPI_RX(SPI_TypeDef * SPIx, uint8_t * Pdata, uint16_t size);
void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx, uint8_t * Pdata, uint16_t size);

void MCAL_SPI_TX_IT(SPI_TypeDef * SPIx, uint8_t * Pdata, uint16_t size);
void MCAL_SPI_RX_IT(SPI_TypeDef * SPIx, uint8_t * Pdata, uint16_t size);
void MCAL_SPI_TX_RX_IT(SPI_TypeDef * SPIx, uint8_t * Pdata, uint16_t size);




#endif /* SPI_H_ */
