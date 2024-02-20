/*
 * USART.h
 *
 *  Created on: Sep 29, 2023
 *      Author: mw296
 */

#ifndef USART_H_
#define USART_H_

typedef struct
{
	u32		USART_Mode;      //specify TX/RX/BOTH
						     //@ref UART_Mode_define
	u32     BaudRate;        //Specify Baud rate
							 //@ref BAUD_RATE
	u32      PayLoadLength;	 //Specify payload length, 8 or 9
							 //@ref PayLoad
	u32 		Parity;			 //	specify parity bit odd even none
							 //@ref Parity
	u32		StopBits;        //specify stop bits
							 //@ref StopBits
	u32      FlowCTRL;        //CTS RTS you know the deal
							 //@ref FLOWCTRL
	u32      IRQ_Enable;      //enable interrupts
							 //@ref IRQ_USART
	void (*P_IRQ_CallBack)(void);

}USART_Config_t;


/*-----------@ref UART_Mode_define----------*/
#define USART_MODE_TX        (u32)(1<<3)
#define USART_MODE_RX        (u32)(1<<2)
#define USART_MODE_TX_RX     ((u32)(1<<2 | 1<<3))

/*----------- @ref BAUD_RATE----------*/
#define USART_BAUD_RATE_2400             2400
#define USART_BAUD_RATE_9600             9600
#define USART_BAUD_RATE_19200            19200
#define USART_BAUD_RATE_57600            57600
#define USART_BAUD_RATE_115200           115200
#define USART_BAUD_RATE_230400           230400
#define USART_BAUD_RATE_460800           460800
#define USART_BAUD_RATE_921600           921600
#define USART_BAUD_RATE_2250000          2250000
#define USART_BAUD_RATE_4500000          4500000

/*----------- @ref PayLoad ----------*/
#define USART_DATA_8bits     (u32)(0)
#define USART_DATA_9bits	 (u32)(1<<12)

/*----------- @ref StopBits ----------*/
/*STOP bits:
These bits are used for programming the stop bits.
00: 1 stop bit: This is the default value.
01: 0.5 stop bit: To be used when receiving data in Smartcard mode.
10: 2 stop bits: This is supported by normal USART, single-wire and modem modes.
11: 1.5 stop bits: To be used when transmitting and receiving data in Smartcard mode.
*/
#define USART_STOP_BITS_1            (u32)(0)
#define USART_STOP_BITS_half         (u32)(1<<12)
#define USART_STOP_BITS_2            (u32)(2<<12)
#define USART_STOP_BITS_1_half       (u32)(3<<12)

/*----------- @ref @ref Parity ----------*/
/*Note: If the PCE bit is set in USART_CR1, then the MSB bit of the data
written in the data register is transmitted but is changed by the parity bit*/
#define USART_PARITY_NONE            (u32)(0)
#define USART_PARITY_EVEN			 ((u32)1<<10)
#define USART_PARITY_ODD		     ((u32)(1<<10 | 1<<9))

/*----------- @ref FLOWCTRL ----------*/
#define USART_FLOW_CTRL_NONE          (u32)(0)
#define USART_FLOW_CTRL_CTS			  ((u32)1<<9)
#define USART_FLOW_CTRL_RTS			  ((u32)1<<8)
#define USART_FLOW_CTRL_CTS_RTS       ((u32)(1<<8 | 1<<9))


/*----------- @ref IRQ_USART ----------*/
#define USART_IRQ_ENABLE_NONE          (u32)(0)
#define USART_IRQ_ENABLE_RXNE          ((u32)(1<<5))	//received data ready to be read and hence flushed  (RX)
#define USART_IRQ_ENABLE_TC            ((u32)(1<<6))	//transmission of multiple successive bytes is complete (TX)
#define USART_IRQ_ENABLE_TXE           ((u32)(1<<7))	//transmit DR empty, you can send more data (TX)
#define USART_IRQ_ENABLE_PE            ((u32)(1<<8))	//parity error (RX)

/*----------- @ref Local configuration ----------*/
#define USART_CFG_1        0
#define USART_CFG_2        1
#define USART_CFG_3        2

/**********< BRR calculation macros ***********/
#define USARTDIV(CLK, baudRate)             ((uint32_t)(CLK / (16 * baudRate)))
#define USARTDIV_MUL100(CLK, baudRate)      ((uint32_t)((25 * CLK) / (4 * baudRate)))
#define DIV_Mantissa(CLK, baudRate)         ((uint32_t)USARTDIV(CLK, baudRate))
#define DIV_Mantissa_MUL100(CLK, baudRate)  ((uint32_t)(DIV_Mantissa(CLK, baudRate) * 100))
#define DIV_Fraction(CLK, baudRate)         ((uint32_t)((USARTDIV_MUL100(CLK, baudRate) - DIV_Mantissa_MUL100(CLK, baudRate)) * 16 )/ 100)
#define UART_BRR_VALUE(CLK, baudRate)       ((DIV_Mantissa(CLK, baudRate) << 4) | (DIV_Fraction(CLK,baudRate) & 0xF))

enum Polling_Mechanism
{
	enable,
	disable
};


/*
======================================================================================================================
* @Func_name	:   MCAL_UART_Init
* @brief		:   Intitialization of the specified UART instance using the specified parameters in the config structure.
* @param [in]	:   USART: specifies the UART instance to be initialized can be (USART1, USART2 or USART3).
* @param [in]	:   config: specifies the configuration parameters for the specified UART instance.
* @return_value :   none.
* Note			:   To enable any of the interrupts use the function "MCAL_UART_Interrupt_EN".
======================================================================================================================
*/
void MCAL_USART_Init(USART_TypeDef * USARTx, USART_Config_t* config);

/*
======================================================================================================================
* @Func_name	:   MCAL_UART_DeInit
* @brief		:   Reset the specified UART instance to its original state.
* @param [in]	:   USART: specifies the UART instance to be reset, can be (USART1, USART2 or USART3).
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_USART_DeInit(USART_TypeDef * USARTx);


/*
======================================================================================================================
* @Func_name	:   MCAL_UART_DeInit
* @brief		:   Reset the specified UART instance to its original state.
* @param [in]	:   USART: specifies the UART instance to be reset, can be (USART1, USART2 or USART3).
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_USART_GPIO_SetPins(USART_TypeDef * USARTx);

/*
======================================================================================================================
* @Func_name	:   MCAL_UART_Send_Data
* @brief		:   Sends data through the specified UART instance.
* @param [in]	:   USART: specifies the UART instance, can be (USART1, USART2 or USART3).
* @param [in]	:   pTxBuffer: pointer to the data to be sent.
* @param [in]	:   PollingEn: Whether to use the polling mechanism or not, must be set based on @ref UART_POLLING_DEFINE.
* @return_value :   none.
* Note			:   If the PCE bit is set in USART_CR1, then the MSB bit of the data
*               :   written in the data register is transmitted but is changed by the parity bit.
======================================================================================================================
*/
void MCAL_USART_Send_Data(USART_TypeDef * USARTx, uint16_t* pTxBuffer,enum Polling_Mechanism PollingEN ,uint8_t size);

/*
======================================================================================================================
* @Func_name	:   MCAL_UART_Get_Data
* @brief		:   Receives the data from the UART.
* @param [in]	:   USART: specifies the UART instance, can be (USART1, USART2 or USART3).
* @param [in]	:   PollingEn: Whether to use the polling mechanism or not, must be set based on @ref UART_POLLING_DEFINE.
* @param [out]	:   pRxBuffer: pointer to the buffer to receive the data in.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_USART_Get_Data(USART_TypeDef * USARTx, uint16_t* pRxBuffer,  enum Polling_Mechanism PollingEN ,uint8_t size);

/*
======================================================================================================================
* @Func_name	:   MCAL_UART_WAIT_TC
* @brief		:   This function waits for the transmission of data from the UART to be completed.
* @param [in]	:   none.
* @param [out]	:   none.
* @return_value :   none.
* Note			:   none.
======================================================================================================================
*/
void MCAL_USART_WAIT_TC(USART_TypeDef * USARTx);

///*
//======================================================================================================================
//* @Func_name	:   MCAL_UART_Interrupt_EN
//* @brief		:   Enable a specific interrupt and set its callback function.
//* @param [in]	:   USART: specifies the UART instance, can be (USART1, USART2 or USART3).
//* @param [in]	:   IRQ: specifies the interrupt to be enabled, must be set based on @ref USART_IRQ_DEFINE.
//* @param [in]	:   p_IRQ_callback: pointer to the callback function to be executed.
//* @return_value :   none.
//* Note			:   none.
//======================================================================================================================
//*/
//void MCAL_USART_Interrupt_EN(USART_TypeDef * USARTx, uint8 IRQ, void (* p_IRQ_callback)(void));
//
///*
//======================================================================================================================
//* @Func_name	:   MCAL_UART_Interrupt_Disable
//* @brief		:   Disable a specific interrupt
//* @param [in]	:   USART: specifies the UART instance, can be (USART1, USART2 or USART3).
//* @param [in]	:   IRQ: specifies the interrupt to be disabled, must be set based on @ref USART_IRQ_DEFINE.
//* @return_value :   none.
//* Note			:   This function won't disable the USART instance interrupt in NVIC you have to manually disable it.
//======================================================================================================================
//*/
//void MCAL_USART_Interrupt_Disable(USART_TypeDef * USARTx, uint8 IRQ);


#endif /* USART_H_ */
