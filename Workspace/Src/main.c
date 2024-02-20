#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stdio.h"
#include "string.h"
#include <stdint.h>
#include "stm32f103x8.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

//////////////////////////////////////////////////////
//                      UTIL                       //
/////////////////////////////////////////////////////

#include "BIT_MATH.h"
#include "STD_TYPES.h"

//////////////////////////////////////////////////////
//                      MCAL                       //
/////////////////////////////////////////////////////

#include "GPIO.h"
#include "RCC_interface.h"
#include "USART.h"
#include "SPI.h"
#include "EXTI.h"
#include "Ticker.h"
#include "ADC.h"
#include "PWM.h"
#include "img.h"

//////////////////////////////////////////////////////
//                      HAL                        //
/////////////////////////////////////////////////////
#include "st7735.h"
#include "GFX_FUNCTIONS.h"
#include "fonts.h"
#include "MP3.h"
#include "Tracks.h"
#include "Menu.h"
#include "Buzzer.h"

void Start_Screen(void);
uint8_t Draw_Next_Tracks(uint8_t track);
uint8_t Erase_Prev_Tracks(uint8_t track);
void Draw_Selector(uint8_t pos);
void Erase_Selector(uint8_t pos);

int8_t Menu_Counter = 0;
int8_t Vol_Counter = 15;
int8_t Track_Counter = 0;
int8_t Slide_Counter = 0;
uint32_t Brightness_Counter = 0;

uint8_t BSY = 0;
uint8_t smphrPlaceHolder = 0;

/***Task Handles***/
TaskHandle_t xUpdate_Screen_Handle = NULL;
TaskHandle_t xMP3_Player_Handle = NULL;
TaskHandle_t xButton_Handle = NULL;
TaskHandle_t xTicker_Handle = NULL;
TaskHandle_t xBrightness_Handle = NULL;
TaskHandle_t xMenu_Handle = NULL;

/***Task Prototype***/
void vUpdate_Screen_Handler(void *params);
void vMP3_Player_Handler(void *params);
void vButton_Handler(void *params);
void vTicker_Handler(void *params);
void vBrightness_Handler(void *params);
void vMenu_Handler(void *params);

/***Event Group Handle handle***/
EventGroupHandle_t buttonEventGroup;
EventGroupHandle_t buttonEventGroup_M;
EventGroupHandle_t MenuEventGroup;
EventGroupHandle_t TickerEventGroup;
/***Queue handles***/
QueueHandle_t xBrightnessQueue;
QueueHandle_t xProgressQueue;

/*** Semaphore Handles***/
//SemaphoreHandle_t xProgressSemaphore;
int main(void) {

	// Event Groups

	buttonEventGroup = xEventGroupCreate();
	buttonEventGroup_M = xEventGroupCreate();
	MenuEventGroup = xEventGroupCreate();
	TickerEventGroup = xEventGroupCreate();

	// Task Creation

	xTaskCreate(vUpdate_Screen_Handler, "Screen Updater", 512, NULL, 1,
			&xUpdate_Screen_Handle);
	xTaskCreate(vMP3_Player_Handler, "MP3 USART1", configMINIMAL_STACK_SIZE,
	NULL, 1, &xMP3_Player_Handle);
	xTaskCreate(vButton_Handler, "Check Butttons", configMINIMAL_STACK_SIZE,
	NULL, 1, &xButton_Handle);
	xTaskCreate(vTicker_Handler, "track time track",
	configMINIMAL_STACK_SIZE, NULL, 2, &xTicker_Handle);
	xTaskCreate(vBrightness_Handler, "ADC AND DAC",
	configMINIMAL_STACK_SIZE, NULL, 1, &xBrightness_Handle);
	xTaskCreate(vMenu_Handler, "Menu",
	configMINIMAL_STACK_SIZE, NULL, 1, &xMenu_Handle);

	// Queue Creation

	xBrightnessQueue = xQueueCreate(1, sizeof(uint32_t));
	xProgressQueue = xQueueCreate(1, sizeof(float));


	// Hardware initialization

	MCAL_RCC_InitSysClock();
	MCAL_RCC_EnablePeripheral(RCC_APB2, RCC_APB2ENR_IOPAEN);
	MCAL_RCC_EnablePeripheral(RCC_APB2, RCC_APB2ENR_IOPBEN);
	MCAL_RCC_EnablePeripheral(RCC_APB2, RCC_APB2ENR_IOPDEN);
	MCAL_RCC_EnablePeripheral(RCC_APB2, RCC_APB2ENR_AFIOEN);
	MCAL_RCC_EnablePeripheral(RCC_APB2, RCC_APB2ENR_SPI1EN);
	MCAL_RCC_EnablePeripheral(RCC_APB2, RCC_APB2ENR_USART1EN);
	MCAL_RCC_EnablePeripheral(RCC_APB2, RCC_APB2ENR_ADC1EN);
	MCAL_RCC_EnablePeripheral(RCC_APB1, RCC_APB1ENR_TIM2EN);

	USART_Config_t uartcfg;
	uartcfg.BaudRate = USART_BAUD_RATE_9600;
	uartcfg.FlowCTRL = USART_FLOW_CTRL_NONE;
	uartcfg.IRQ_Enable = USART_IRQ_ENABLE_NONE;
	uartcfg.P_IRQ_CallBack = NULL;
	uartcfg.Parity = USART_PARITY_NONE;
	uartcfg.PayLoadLength = USART_DATA_8bits;
	uartcfg.StopBits = USART_STOP_BITS_1;
	uartcfg.USART_Mode = USART_MODE_TX_RX;

	MCAL_USART_Init(USART1, &uartcfg);
	MCAL_USART_GPIO_SetPins(USART1);

	SPI_Config_t spicfg;
	spicfg.Baud_PS = SPI_Baud_PS_2;
	spicfg.Device_Mode = SPI_Device_Mode_Master;
	spicfg.Com_Mode = SPI_Com_Mode_1L_TX;
	spicfg.Data_Size = SPI_Data_Size_8;
	spicfg.Frame_Format = SPI_Frame_Format_MSB;
	spicfg.IRQ_En = SPI_IRQ_NONE;
	spicfg.NSS = SPI_NSS_Software_En_Set;
	spicfg.P_IRq_CallBack = NULL;
	spicfg.CLK_PHA = SPI_CLK_PHA_1;
	spicfg.CLK_POL = SPI_CLK_POL_Low;

	MCAL_SPI_Init(SPI1, &spicfg);
	MCAL_SPI_GPIO_PINS(SPI1);

	/* TFT LCD CONTROL */
	GPIO_PinConfig_t ccfg;
	ccfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	ccfg.GPIO_Output_Speed = GPIO_SPEED_2M;
	ccfg.GPIO_PinNumber = GPIO_PIN_2;
	MCAL_GPIO_Init(GPIOA, &ccfg);

	ccfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	ccfg.GPIO_Output_Speed = GPIO_SPEED_2M;
	ccfg.GPIO_PinNumber = GPIO_PIN_3;
	MCAL_GPIO_Init(GPIOA, &ccfg);

	ccfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	ccfg.GPIO_Output_Speed = GPIO_SPEED_2M;
	ccfg.GPIO_PinNumber = GPIO_PIN_4;
	MCAL_GPIO_Init(GPIOA, &ccfg);

	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

	// PIN B6 BSY LINE
	ccfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	ccfg.GPIO_Output_Speed = GPIO_SPEED_2M;
	ccfg.GPIO_PinNumber = GPIO_PIN_6;
	MCAL_GPIO_Init(GPIOB, &ccfg);

	/* MENU CONTROL */
	// PIN B7 FORWARD BUTTON
	ccfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	ccfg.GPIO_Output_Speed = GPIO_SPEED_2M;
	ccfg.GPIO_PinNumber = GPIO_PIN_7;
	MCAL_GPIO_Init(GPIOB, &ccfg);

	// PIN B8 ACTION BUTTON
	ccfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	ccfg.GPIO_Output_Speed = GPIO_SPEED_2M;
	ccfg.GPIO_PinNumber = GPIO_PIN_8;
	MCAL_GPIO_Init(GPIOB, &ccfg);

	// PIN B9 BACKWARD BUTTON
	ccfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	ccfg.GPIO_Output_Speed = GPIO_SPEED_2M;
	ccfg.GPIO_PinNumber = GPIO_PIN_9;
	MCAL_GPIO_Init(GPIOB, &ccfg);

	// PIN A11 VOL UP
	ccfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	ccfg.GPIO_Output_Speed = GPIO_SPEED_2M;
	ccfg.GPIO_PinNumber = GPIO_PIN_11;
	MCAL_GPIO_Init(GPIOA, &ccfg);

	// PIN A12 VOL DOWN
	ccfg.GPIO_MODE = GPIO_MODE_INPUT_PU;
	ccfg.GPIO_Output_Speed = GPIO_SPEED_2M;
	ccfg.GPIO_PinNumber = GPIO_PIN_12;
	MCAL_GPIO_Init(GPIOA, &ccfg);

	PWM_Init(60000);
	ST7735_Init();
	MCAL_ADC_Init(ADC1, GPIOA, GPIO_PIN_0);
	Brightness_Counter = MCAL_ADC_Read(ADC1, GPIOA, GPIO_PIN_0);
	if (Brightness_Counter > 4040)
		Brightness_Counter = 4040;
	Brightness_Counter = (Brightness_Counter - 0) * (50 - 10) / (4040 - 0) + 10;

	// NOT ENOUGH FLASH SIZE FOR WELCOME IMAGE --> CHANGE THE FLASH SIZE IN FLASHLD
	ST7735_DrawImage(0, 0, 160, 128, img);

	PWM_Duty(60000);
	playNote();

	if (HAL_DF_Init(15) == TF_OFFLINE) {
		// ALARM SCREEN
		fillRect(19, 36, 145-19, 103-36, ST7735_BLACK);
		drawRect(24, 41, 140-24, 99-41, ST7735_YELLOW);

		ST7735_WriteString(32, 56, "SD UNDETECTED", Font_7x10, ST7735_YELLOW, ST7735_BLACK);
		fillTriangle(65,88, 75, 78, 85, 88, ST7735_YELLOW);
		fillRect(75, 81, 2, 4, ST7735_BLACK);
		fillRect(75, 86, 2, 2, ST7735_BLACK);

		HAL_DF_Wait_Push();

		ST7735_WriteString(32, 56, "SD UNDETECTED", Font_7x10, ST7735_BLACK, ST7735_BLACK);
		fillTriangle(65,88, 75, 78, 85, 88, ST7735_BLACK);

		ST7735_WriteString(32, 56, "SD DETECTED", Font_7x10, ST7735_YELLOW, ST7735_BLACK);
		fillCircle(76, 84, 13, ST7735_YELLOW);

		fillCircle(70, 80, 3, ST7735_BLACK);
		fillCircle(83, 80, 3, ST7735_BLACK);

		fillCircle(76, 90, 4, ST7735_BLACK);
		fillCircle(76, 88, 4, ST7735_YELLOW);


	}

	Ticker_ms(5000);
	Ticker_Init();
	vTaskStartScheduler();

	for (;;)
		;
}

void vUpdate_Screen_Handler(void *params) {

	Start_Screen();

	int8_t Prev_Track_Counter = Track_Counter;
	int8_t Prev_Vol_Counter = Vol_Counter;

	float perc;
	float Prev_Perc = 0;

	uint32_t Prev_Brightness = 0;
	uint32_t Brightness;

	for (;;) {
		EventBits_t suspend = xEventGroupWaitBits(MenuEventGroup, Menu_Trigger,
		pdFALSE, pdFALSE, 0);
		if (suspend & Menu_Trigger) {
			vTaskSuspend(NULL);
		}

		if (suspend & Screen_Resume) {
			Start_Screen();
			Track_Counter = Slide_Counter;
			xEventGroupClearBits(MenuEventGroup, Screen_Resume);
		}
		EventBits_t bits = xEventGroupWaitBits(buttonEventGroup,
				BUTTON_PP_BIT | BUTTON_UP_BIT | BUTTON_DOWN_BIT
						| BUTTON_BACK_BIT | BUTTON_FOR_BIT,
				pdFALSE, pdFALSE, 1);

		if (bits & BUTTON_BACK_BIT) {
			xEventGroupClearBits(buttonEventGroup, BUTTON_BACK_BIT);
			if (Menu_Counter == 0) {
				drawRect(51, 92, 25, 29, ST7735_BLACK);
				drawRect(10, 92, 25, 29, ST7735_GREEN);
			} else if (Menu_Counter == 1) {
				drawRect(92, 92, 25, 29, ST7735_BLACK);
				drawRect(51, 92, 25, 29, ST7735_GREEN);
			} else if (Menu_Counter == 2) {
				drawRect(126, 92, 25, 29, ST7735_BLACK);
				drawRect(92, 92, 25, 29, ST7735_GREEN);
			} else if (Menu_Counter == 3) { //true
				drawRect(10, 92, 25, 29, ST7735_BLACK);
				drawRect(126, 92, 25, 29, ST7735_GREEN);
			}

		}

		else if (bits & BUTTON_FOR_BIT) {
			xEventGroupClearBits(buttonEventGroup, BUTTON_FOR_BIT);
			if (Menu_Counter == 0) {
				drawRect(126, 92, 25, 29, ST7735_BLACK);
				drawRect(10, 92, 25, 29, ST7735_GREEN);
			} else if (Menu_Counter == 1) {
				drawRect(10, 92, 25, 29, ST7735_BLACK);
				drawRect(51, 92, 25, 29, ST7735_GREEN);
			} else if (Menu_Counter == 2) {
				drawRect(51, 92, 25, 29, ST7735_BLACK);
				drawRect(92, 92, 25, 29, ST7735_GREEN);
			} else if (Menu_Counter == 3) {
				drawRect(92, 92, 25, 29, ST7735_BLACK);
				drawRect(126, 92, 25, 29, ST7735_GREEN);
			}
		}

		if ((bits & BUTTON_PP_BIT)) {

			xEventGroupClearBits(buttonEventGroup, BUTTON_PP_BIT);
			if (BSY) {
				fillTriangle(56, 107, 68, 95, 68, 118, ST7735_BLACK);
				fillRect(55, 96, 4, 21, ST7735_RED);
				fillRect(68, 96, 4, 21, ST7735_RED);
			}

			else {
				fillRect(55, 96, 4, 21, ST7735_BLACK);
				fillRect(68, 96, 4, 21, ST7735_BLACK);
				fillTriangle(56, 107, 68, 95, 68, 118, ST7735_RED);
			}
		}

		if ((Prev_Track_Counter != Track_Counter)) {
			ST7735_WriteString(9, 25, getTrackName(Prev_Track_Counter),
					Font_11x18,
					ST7735_BLACK, ST7735_BLACK);

			ST7735_WriteString(9, 25, getTrackName(Track_Counter), Font_11x18,
			ST7735_RED, ST7735_BLACK);

		}

		if (Prev_Vol_Counter != Vol_Counter) {
			char str[4];
			snprintf(str, sizeof(str), "%d", Prev_Vol_Counter);
			ST7735_WriteString(130, 5, str, Font_11x18, ST7735_BLACK,
			ST7735_BLACK);
			snprintf(str, sizeof(str), "%d", Vol_Counter);
			ST7735_WriteString(130, 5, str, Font_11x18, ST7735_RED,
			ST7735_BLACK);
		}
		if (xQueueReceive(xProgressQueue, &perc, 0)) {
			if ((uint8_t) Prev_Perc != (uint8_t) perc) {

				if (perc == 0) {
					fillRect(31, 86, 100, 2, ST7735_BLACK);
				} else {
					uint8_t pos = 0;
					pos = (uint8_t) perc + 30;
					fillRect(pos, 86, 1, 2, ST7735_BLUE);
				}
			}
		}

		if (xQueueReceive(xBrightnessQueue, &Brightness, 0) == pdPASS) {
			if (Prev_Brightness != Brightness) {
				//WE UPDATE THE SCREEN
				if (Brightness > Prev_Brightness) {
					ST7735_FillRectangle(6 + (Prev_Brightness), 9,
							(Brightness - Prev_Brightness), 7, ST7735_WHITE);
				}

				else if (Brightness < Prev_Brightness) {
					ST7735_FillRectangle(6 + (Brightness), 9,
							(Prev_Brightness - Brightness), 7, ST7735_BLACK);
				}
			}
		}

		Prev_Track_Counter = Track_Counter;
		Prev_Vol_Counter = Vol_Counter;
		Prev_Perc = perc;
		Prev_Brightness = Brightness;

		vTaskDelay(10);

	}
}
void vMP3_Player_Handler(void *params) {
	uint8_t prev_busy = BSY;
	for (;;) {
		EventBits_t suspend = xEventGroupWaitBits(MenuEventGroup, Menu_Trigger,
		pdFALSE, pdFALSE, 0);
		if (suspend & Menu_Trigger) {
			vTaskSuspend(NULL);
		}

		if (suspend & MP3_Resume) {
			HAL_DF_SpecifyTrack(Slide_Counter);
			Track_Counter = Slide_Counter;
			xEventGroupClearBits(MenuEventGroup, MP3_Resume);
		}
		prev_busy = BSY;
		if (MCAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_RESET) {
			BSY = 1;
		} else {
			BSY = 0;
		}

		if (prev_busy != BSY) {
			xEventGroupSetBits(buttonEventGroup, BUTTON_PP_BIT);
			smphrPlaceHolder = 1;
		}

		EventBits_t bits = xEventGroupWaitBits(buttonEventGroup_M,
		BUTTON_ACT_BIT_M | BUTTON_UP_BIT_M | BUTTON_DOWN_BIT_M,
		pdFALSE, pdFALSE, 1);

		if (bits & BUTTON_ACT_BIT_M) {
			xEventGroupClearBits(buttonEventGroup_M, BUTTON_ACT_BIT_M);
			if (Menu_Counter == 0) {
				HAL_DF_Previous();
				Track_Counter--;
				//update_track = 1;
			}

			else if (Menu_Counter == 2) {
				HAL_DF_Next();
				Track_Counter++;
				//update_track = 1;
			} else if (Menu_Counter == 1) {
				if (BSY) {
					HAL_DF_Pause();
				} else {
					HAL_DF_Playback();
				}
			} else if (Menu_Counter == 3) {
				xEventGroupSetBits(MenuEventGroup, Menu_Trigger);
				xEventGroupSetBits(MenuEventGroup, Menu_First);
			}

			if (Track_Counter < 0) {
				Track_Counter = MAX_TRACK_NUM - 1;
			} else if (Track_Counter > MAX_TRACK_NUM - 1) {
				Track_Counter = 0;
			}
		}

		if (bits & (BUTTON_DOWN_BIT_M | BUTTON_UP_BIT_M)) {
			HAL_DF_SpecifyVolume(Vol_Counter);
			xEventGroupClearBits(buttonEventGroup_M, BUTTON_UP_BIT_M);
			xEventGroupClearBits(buttonEventGroup_M, BUTTON_DOWN_BIT_M);
		}
		vTaskDelay(20);
	}
}
void vButton_Handler(void *params) {

	for (;;) {
		EventBits_t suspend = xEventGroupWaitBits(MenuEventGroup, Menu_Trigger,
		pdFALSE, pdFALSE, 0);
		if (suspend & Menu_Trigger) {
			if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET) {
				xEventGroupSetBits(buttonEventGroup, BUTTON_UP_BIT);
				Slide_Counter++;
			}
			if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_RESET) {
				xEventGroupSetBits(buttonEventGroup, BUTTON_DOWN_BIT);
				Slide_Counter--;
			}
			if (MCAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET) {
				xEventGroupSetBits(MenuEventGroup, Menu_Finish);
			}

			if (Slide_Counter > MAX_TRACK_NUM - 1) {
				Slide_Counter = 0;
			} else if (Slide_Counter < 0) {
				Slide_Counter = MAX_TRACK_NUM - 1;
			}
		} else {
			if (MCAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == GPIO_PIN_RESET) {
				xEventGroupSetBits(buttonEventGroup, BUTTON_FOR_BIT);
				Menu_Counter++;
			}
			if (MCAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET) {
				xEventGroupSetBits(buttonEventGroup_M, BUTTON_ACT_BIT_M);
			}
			if (MCAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_RESET) {
				xEventGroupSetBits(buttonEventGroup, BUTTON_BACK_BIT);
				Menu_Counter--;
			}
			if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET) {
				xEventGroupSetBits(buttonEventGroup, BUTTON_UP_BIT);
				xEventGroupSetBits(buttonEventGroup_M, BUTTON_UP_BIT_M);
				Vol_Counter++;
			}
			if (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_RESET) {
				xEventGroupSetBits(buttonEventGroup, BUTTON_DOWN_BIT);
				xEventGroupSetBits(buttonEventGroup_M, BUTTON_DOWN_BIT_M);
				Vol_Counter--;
			}

			// Sliding Constraint
			if (Menu_Counter < 0) {
				Menu_Counter = 2;
			} else if (Menu_Counter > 3) {
				Menu_Counter = 0;
			}

			//Volume Constraint
			if (Vol_Counter < 0) {
				Vol_Counter = 0;
				xEventGroupClearBits(buttonEventGroup, BUTTON_DOWN_BIT);
				xEventGroupClearBits(buttonEventGroup_M, BUTTON_DOWN_BIT_M);
			} else if (Vol_Counter > 30) {
				Vol_Counter = 30;
				xEventGroupClearBits(buttonEventGroup, BUTTON_UP_BIT);
				xEventGroupClearBits(buttonEventGroup_M, BUTTON_UP_BIT_M);
			}

		}
		// Mainly to avoid bouncing
		vTaskDelay(200);

	}
}

void vTicker_Handler(void *params) {
	uint8_t prev_track = Track_Counter;
	uint8_t prev_state = BSY;
	float perc = 0;
	float tick;

	for (;;) {
		if (smphrPlaceHolder == 1)  // FLAG TO ASSUME WORKING
				{
			EventBits_t suspend = xEventGroupWaitBits(MenuEventGroup,
			Menu_Trigger,
			pdFALSE, pdFALSE, 0);

			if (suspend & Menu_Trigger) {
				Ticker_Stop();
				Ticker_Reset_Count();

				smphrPlaceHolder = 0;
				vTaskSuspend(xTicker_Handle);
			}

			tick = Get_ms();
			// CASE 1 STARTUP
			if (tick == 0 && BSY) // ITS THE FIRST TIME ACTIVATING --> NEW TRACK / STARTUP
					{
				// I ONLY WANT TO START THE TICKER ONCE
				Ticker_Start();
			}

			// CASE 2 TRACK CHANGE
			if (prev_track != Track_Counter) {
				Ticker_Stop();
				Ticker_Reset_Count();
			}

			// CASE 3 SAME TRACK -> CHECK STATE
			else {
				if (!BSY) {
					Ticker_Stop();
				} else if (prev_state != BSY) {
					Ticker_Start();
				}
			}
			float us = duration[Track_Counter] * 1000;
			perc = (tick / us) * 100;

			// CASE 4 FINISHED TRACK
			if (perc >= 100) {
				perc = 0;
				// QUEUE SEND
				xQueueSend(xProgressQueue, (void* ) &perc, 0);
				Ticker_Stop();
				Ticker_Reset_Count();
				// TASK NO LONGER NEEDED
				smphrPlaceHolder = 0;
			}
			// QUEUE SEND
			xQueueSend(xProgressQueue, (void* ) &perc, 0);
		}
		prev_track = Track_Counter;
		prev_state = BSY;
		vTaskDelay(200);
	}
}

void vBrightness_Handler(void *params) {
	uint32_t val;
	for (;;) {
		if (MCAL_ADC_EOC(ADC1)) {
			val = MCAL_ADC_Read(ADC1, GPIOA, GPIO_PIN_0);
			if (val > 3860)
				val = 3860;
			val = (val - 0) * (50 - 10) / (3860 - 0) + 10;
			//queue send
			xQueueSend(xBrightnessQueue, (void* )&val, 0);
		}
		vTaskDelay(20);
	}
}

void vMenu_Handler(void *params) {

	uint8_t Prev_Slide_Counter = Slide_Counter;
	uint8_t pages = MAX_TRACK_NUM / 5;
	uint8_t current_page = 1;
	for (;;) {

		EventBits_t suspend = xEventGroupWaitBits(MenuEventGroup,
		Menu_Trigger | Menu_First | Menu_Finish,
		pdFALSE, pdFALSE, 0);
		EventBits_t bits = xEventGroupWaitBits(buttonEventGroup,
		BUTTON_UP_BIT | BUTTON_DOWN_BIT,
		pdFALSE, pdFALSE, 0);
		if (suspend & Menu_Finish) {

			Track_Counter = Slide_Counter;

			xEventGroupSetBits(MenuEventGroup, MP3_Resume);
			xEventGroupSetBits(MenuEventGroup, Screen_Resume);

			// for pause play refresh
			xEventGroupSetBits(buttonEventGroup, BUTTON_PP_BIT);

			// for volume
			xEventGroupClearBits(MenuEventGroup, Menu_First);
			xEventGroupClearBits(MenuEventGroup, Menu_Finish);
			xEventGroupClearBits(MenuEventGroup, Menu_Trigger);

			vTaskResume(xUpdate_Screen_Handle);
			vTaskResume(xMP3_Player_Handle);
			vTaskResume(xTicker_Handle);

		}
		if (suspend & Menu_Trigger) {
			if (suspend & Menu_First) {
				ST7735_FillScreen(ST7735_BLACK);
				Slide_Counter = 0;

				// DRAW VERY FIRST 4 TRACK NAMES
				Draw_Next_Tracks(Slide_Counter);
				// DRAW THE H LINE SELECTOR
				Draw_Selector(Slide_Counter);
				// DRAW CURRENT PAGE

				ST7735_WriteString(70, 107, "1 / 2", Font_11x18, ST7735_WHITE, ST7735_BLACK);

				xEventGroupClearBits(MenuEventGroup, Menu_First);
			}
			if (bits & (BUTTON_UP_BIT | BUTTON_DOWN_BIT)) {

				// CHEK CURRENT LOCATION IF ITS % 4 ERASE AND REWRITE NEXT 4 WITH SAME FUNCTION
				if (Slide_Counter % 5 == 0) {
					current_page ++;
					if(current_page > 2 )
					{
						current_page = 1;
					}
					if(current_page == 1)
					{
						ST7735_WriteString(70, 107, "1 / 2", Font_11x18, ST7735_WHITE, ST7735_BLACK);
					}
					else if(current_page == 2)
					{
						ST7735_WriteString(70, 107, "2 / 2", Font_11x18, ST7735_WHITE, ST7735_BLACK);
					}
					// Erase Logic of tracks
					Erase_Prev_Tracks(Prev_Slide_Counter);
					Draw_Next_Tracks(Slide_Counter);

					Erase_Selector(Prev_Slide_Counter);
					Draw_Selector(Slide_Counter);
				}

				// DRAW SELECTOR on new pos
				else {
					Erase_Selector(Prev_Slide_Counter);
					Draw_Selector(Slide_Counter);
				}

				xEventGroupClearBits(buttonEventGroup, BUTTON_UP_BIT);
				xEventGroupClearBits(buttonEventGroup, BUTTON_DOWN_BIT);
			}

		}

		Prev_Slide_Counter = Slide_Counter;
		vTaskDelay(10);

	}
}

void Start_Screen(void) {
	// START SCREEN
	ST7735_FillScreen(ST7735_BLACK);
	//BACKWARD
	fillTriangle(12, 107, 24, 95, 24, 118, ST7735_RED);
	fillTriangle(19, 107, 31, 95, 31, 118, ST7735_RED);
	//FORWARD
	fillTriangle(114, 107, 103, 95, 103, 118, ST7735_RED);
	fillTriangle(107, 107, 96, 95, 96, 118, ST7735_RED);
	//PLAY
	if (BSY) {
		fillRect(55, 96, 4, 21, ST7735_RED);
		fillRect(68, 96, 4, 21, ST7735_RED);
	} else {
		fillTriangle(56, 107, 68, 95, 68, 118, ST7735_RED);
	}

	//MENU
	fillRect(130, 94, 15, 4, ST7735_RED);
	fillRect(130, 105, 15, 5, ST7735_RED);
	fillRect(130, 116, 15, 4, ST7735_RED);
	//FIRST SELECTION
	drawRect(10, 92, 25, 29, ST7735_GREEN);
	//TRACK NAME
	ST7735_WriteString(9, 25, getTrackName(Track_Counter), Font_11x18,
	ST7735_RED, ST7735_BLACK);
	//PROGRESS
	drawRect(30, 85, 102, 4, ST7735_RED);

	//INDICATOR BAR
	drawFastHLine(1, 23, 159, ST7735_RED);
	ST7735_WriteString(97, 5, "VOL", Font_11x18, ST7735_RED, ST7735_BLACK);

	char str[5];
	snprintf(str, sizeof(str), "%d", Vol_Counter);
	ST7735_WriteString(130, 5, str, Font_11x18, ST7735_RED, ST7735_BLACK);

	//Brightness bar
	drawRect(5, 8, 52, 9, ST7735_RED);

	Brightness_Counter = MCAL_ADC_Read(ADC1, GPIOA, GPIO_PIN_0);
	if (Brightness_Counter > 3860)
		Brightness_Counter = 3860;
	Brightness_Counter = (Brightness_Counter - 0) * (50 - 10) / (3860 - 0) + 10;

	ST7735_FillRectangle(6, 9, Brightness_Counter, 7, ST7735_WHITE);

}

uint8_t Erase_Prev_Tracks(uint8_t track) {

	int i;
	for (i = track - 4; i < track + 1; i++) {
		ST7735_WriteString(5, 5 + ((i - track) * 20), getTrackName(i),
				Font_11x18,
				ST7735_BLACK, ST7735_BLACK);
	}
	return 4;

}

uint8_t Draw_Next_Tracks(uint8_t track) {

	if (track == 0) // First 5
			{
		int i;
		for (i = 0; i < 5; i++) {
			if ((i + 1) > MAX_TRACK_NUM) // Check if we overflowed
			{
				return i;
			}
			ST7735_WriteString(5, 5 + i * 20, getTrackName(i), Font_7x10,
			ST7735_BLUE, ST7735_BLACK);
		}
		return 5;
	}

	else if (track % 5 == 0) // Next n page
			{
		int i;
		for (i = track; i < track + 5; i++) {
			if ((i + 1) > MAX_TRACK_NUM) // Check if we overflowed
			{
				return i;
			}
			ST7735_WriteString(5, 5 + ((i - track) * 20), getTrackName(i),
					Font_7x10,
					ST7735_BLUE, ST7735_BLACK);
		}
		return 4;
	}

	else {
		return 0;
	}
}

void Draw_Selector(uint8_t pos) {

	if (pos == 0 || (pos % 5 == 0))
		pos = 0;
	else if (pos == 1 || ((pos - 1) % 5 == 0))
		pos = 1;
	else if (pos == 2 || ((pos - 2) % 5 == 0))
		pos = 2;
	else if (pos == 3 || ((pos - 3) % 5 == 0))
		pos = 3;
	else if (pos == 4 || ((pos - 4) % 5 == 0))
		pos = 4;
	drawFastHLine(5, 20 + pos * 20, 100, ST7735_YELLOW);
}
void Erase_Selector(uint8_t pos) {

	if (pos == 0 || (pos % 5 == 0))
		pos = 0;
	else if (pos == 1 || ((pos - 1) % 5 == 0))
		pos = 1;
	else if (pos == 2 || ((pos - 2) % 5 == 0))
		pos = 2;
	else if (pos == 3 || ((pos - 3) % 5 == 0))
		pos = 3;
	else if (pos == 4 || ((pos - 4) % 5 == 0))
		pos = 4;
	drawFastHLine(5, 20 + pos * 20, 100, ST7735_BLACK);
}
