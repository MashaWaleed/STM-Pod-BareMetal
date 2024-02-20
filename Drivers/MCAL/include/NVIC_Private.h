#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

#define NVIC_ISER0     (*((volatile u32 *)0xE000E100))
#define NVIC_ISER1     (*((volatile u32 *)0xE000E104))
#define NVIC_ISER2     (*((volatile u32 *)0xE000E108))

#define NVIC_ICER0     (*((volatile u32 *)0xE000E180))
#define NVIC_ICER1     (*((volatile u32 *)0xE000E184))
#define NVIC_ICER2     (*((volatile u32 *)0xE000E188))

#define NVIC_ISPR0     (*((volatile u32 *)0xE000E200))
#define NVIC_ISPR1     (*((volatile u32 *)0xE000E204))
#define NVIC_ISPR2     (*((volatile u32 *)0xE000E208))

#define NVIC_ICPR0     (*((volatile u32 *)0xE000E280))
#define NVIC_ICPR1     (*((volatile u32 *)0xE000E284))
#define NVIC_ICPR2     (*((volatile u32 *)0xE000E288))

#define NVIC_IABR0     (*((volatile u32 *)0xE000E300))
#define NVIC_IABR1     (*((volatile u32 *)0xE000E304))
#define NVIC_IABR2     (*((volatile u32 *)0xE000E308))

#define NVIC_IPR_BASE_ADDRESS    (((volatile u32 *)0xE000E400))

#define NVIC_16GROUP_0SUB   0x05FA0300U
#define NVIC_8GROUP_2SUB    0x05FA0400U
#define NVIC_4GROUP_4SUB    0x05FA0500U
#define NVIC_2GROUP_8SUB    0x05FA0600U
#define NVIC_0GROUP_16SUB   0x05FA0700U

#define SCB_BASE_ADDRESS    0xE000ED00U
#define SCB_AIRCR           (*((volatile u32 *)(SCB_BASE_ADDRESS + 0x0C)))

#endif /* NVIC_PRIVATE_H_ */
