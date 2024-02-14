/*
 * keypad.c
 *
 *  Created on: Aug 31, 2023
 *      Author: mw296
 */

#include "keypad.h"

int Key_padRow[ROW] = { R0, R1, R2, R3 }; //rows of the keypad
int Key_padCol[COL] = { C0, C1, C2, C3 }; //columns


uint8_t KeypadLayout[ROW][COL]=
{
		{'7','8','9','/'},
		{'4','5','6','X'},
		{'1','2','3','-'},
		{'?','0','=','+'}
};


void Keypad_init() {
	GPIO_PinConfig_t PinCfg;

	PinCfg.GPIO_PinNumber = R0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = R1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = R2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = R3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);
	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);

}

uint8_t Keypad_getkey() {
	uint8_t i, j;
	for (i = 0; i < 4; i++) {
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[0], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[1], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[2], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[3], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, Key_padCol[i], GPIO_PIN_RESET);
		for (j = 0; j < 4; j++) {
			if (MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padRow[j]) == 0) {
				while (MCAL_GPIO_ReadPin(KEYPAD_PORT, Key_padRow[j]) == 0);
				return KeypadLayout[j][i];
			}
		}
	}
	return '~';
}
