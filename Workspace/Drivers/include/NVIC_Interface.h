#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

typedef u8 IRQn_Type;

#define NONE ((INVALID_VALUE)-1)

#define NVIC_WWDG_IRQn              0
#define NVIC_PVD_IRQn               1
#define NVIC_TAMPER_IRQn            2
#define NVIC_RTC_IRQn               3
#define NVIC_FLASH_IRQn             4
#define NVIC_RCC_IRQn               5
#define NVIC_EXTI0_IRQn             6
#define NVIC_EXTI1_IRQn             7
#define NVIC_EXTI2_IRQn             8
#define NVIC_EXTI3_IRQn             9
#define NVIC_EXTI4_IRQn             10
#define NVIC_DMA1_Channel1_IRQn     11
#define NVIC_DMA1_Channel2_IRQn     12
#define NVIC_DMA1_Channel3_IRQn     13
#define NVIC_DMA1_Channel4_IRQn     14
#define NVIC_DMA1_Channel5_IRQn     15
#define NVIC_DMA1_Channel6_IRQn     16
#define NVIC_DMA1_Channel7_IRQn     17
#define NVIC_ADC1_2_IRQn            18
#define NVIC_USB_HP_CAN_TX_IRQn     19
#define NVIC_USB_LP_CAN_RX0_IRQn    20
#define NVIC_CAN_RX1_IRQn           21
#define NVIC_CAN_SCE_IRQn           22
#define NVIC_EXTI9_5_IRQn           23
#define NVIC_TIM1_BRK_IRQn          24
#define NVIC_TIM1_UP_IRQn           25
#define NVIC_TIM1_TRG_COM_IRQn      26
#define NVIC_TIM1_CC_IRQn           27

#define NVIC_TIM2_IRQn              28
#define NVIC_TIM3_IRQn              29
#define NVIC_TIM4_IRQn              30
#define NVIC_I2C1_EV_IRQn           31
#define NVIC_I2C1_ER_IRQn           32
#define NVIC_I2C2_EV_IRQn           33
#define NVIC_I2C2_ER_IRQn           34
#define NVIC_SPI1_IRQn              35
#define NVIC_SPI2_IRQn              36
#define NVIC_USART1_IRQn            37
#define NVIC_USART2_IRQn            38
#define NVIC_USART3_IRQn            39
#define NVIC_EXTI15_10_IRQn         40
#define NVIC_RTCAlarm_IRQn          41
#define NVIC_USBWakeup_IRQn         42
#define NVIC_TIM8_BRK_IRQn          43
#define NVIC_TIM8_UP_IRQn           44
#define NVIC_TIM8_TRG_COM_IRQn      45
#define NVIC_TIM8_CC_IRQn           46
#define NVIC_ADC3_IRQn              47
#define NVIC_FSMC_IRQn              48
#define NVIC_SDIO_IRQn              49
#define NVIC_TIM5_IRQn              50
#define NVIC_SPI3_IRQn              51
#define NVIC_UART4_IRQn             52
#define NVIC_UART5_IRQn             53
#define NVIC_TIM6_IRQn              54
#define NVIC_TIM7_IRQn              55
#define NVIC_DMA2_Channel1_IRQn     56
#define NVIC_DMA2_Channel2_IRQn     57
#define NVIC_DMA2_Channel3_IRQn     58
#define NVIC_DMA2_Channel4_5_IRQn   59

Std_ReturnType MCAL_NVIC_EnableIRQ(IRQn_Type Copy_IRQn);
Std_ReturnType MCAL_NVIC_DisableIRQ(IRQn_Type Copy_IRQn);
Std_ReturnType MCAL_NVIC_SetPendingIRQ(IRQn_Type Copy_IRQn);
Std_ReturnType MCAL_NVIC_ClearPendingIRQ(IRQn_Type Copy_IRQn);
Std_ReturnType MCAL_NVIC_GetPendingIRQ(IRQn_Type Copy_IRQn, u8 *Copy_ReturnPendingFlag);
Std_ReturnType MCAL_NVIC_xSetPriority(IRQn_Type Copy_IRQn, u8 Copy_Priority);
Std_ReturnType MCAL_NVIC_vSetPriority(IRQn_Type Copy_IRQn, u8 Copy_GroupPriority, u8 Copy_SubPriority);
Std_ReturnType MCAL_NVIC_xGetPriority(IRQn_Type IRQn, u8 *Copy_Priority);

#endif /* NVIC_INTERFACE_H_ */
