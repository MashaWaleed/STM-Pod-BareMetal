/*
 * MP3.c
 *
 * Author: Mohamed Waleed
 */
#include "STD_TYPES.h"
#include "stdio.h"
#include "stm32f103x8.h"
#include "USART.h"
#include "MP3.h"

/*

 BAUD RATE  --> 9600 BPS
 PARITY     --> NONE
 STOP BIT   --> ONE
 FLOW CTRL  --> NONE
 MODE       --> ASYNCHRONOUS TX RX

*/

#define DF_UART        USART1
#define Source         0x02  // TF CARD


/*

 START -> VERSION -> LENGTH -> FEEDBACK -> PAR1 -> PAR2 -> CS -> CS -> END

*/

#define Start_Byte 0x7E
#define End_Byte   0xEF
#define Version    0xFF
#define Cmd_Len    0x06

// 0 --> No Feedback  1 --> For Feedback
#define Feedback   0x00

void Send_cmd (uint16_t cmd, uint16_t Parameter1, uint16_t Parameter2)
{
	uint16_t Checksum = Version + Cmd_Len + cmd + Feedback + Parameter1 + Parameter2;
	Checksum = 0-Checksum;

	uint16_t CmdSequence[10] = { Start_Byte, Version, Cmd_Len, cmd, Feedback, Parameter1, Parameter2, (Checksum>>8)&0x00ff, (Checksum&0x00ff), End_Byte};
	MCAL_USART_Send_Data(DF_UART, CmdSequence, enable, 10);
}


uint8_t HAL_DF_Init (uint8_t volume)
{
	uint16_t rec[10];
	Send_cmd(0x3F, 0x00, Source);
	Send_cmd(0x06, 0x00, volume);


	MCAL_USART_Get_Data(DF_UART, rec,enable, 3);
	if(rec[1] == 254)
	{
		return TF_OFFLINE;
	}
	return TF_ONLINE;
}

void HAL_DF_Wait_Push (void)
{
	uint16_t rec[10] = {0,0,0,0,0,0,0,0,0,0};
	while(rec[2] == 0)
	{
		MCAL_USART_Get_Data(DF_UART, rec,enable, 3);
	}

}


void HAL_DF_Next (void)
{
	Send_cmd(0x01, 0x00, 0x00);
}

void HAL_DF_Pause (void)
{
	Send_cmd(0x0E, 0, 0);
}

void HAL_DF_Previous (void)
{
	Send_cmd(0x02, 0, 0);
}

void HAL_DF_Playback (void)
{
	Send_cmd(0x0D, 0, 0);
}

void HAL_DF_SpecifyVolume(uint8_t volume)
{
	Send_cmd(0x06, 0x00, volume);
}

void HAL_DF_SpecifyTrack(uint8_t track)
{
	track ++;
	Send_cmd(0x03, 0x00, track);
}








