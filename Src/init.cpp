#include <stdint.h>
#include "stm32f1xx.h"

void init(void);
void Default_Handler(void);
void USART2_Handler(void);
void USART1_Handler(void);
void HardFault_Handler(void);
void EXTI0_IRQHandler(void);
void EXTI2_IRQHandler(void);
void SysTick_Handler(void);
void RTC_IRQHandler(void);
int main(void);
// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;

extern unsigned char  _sidata;//INIT_DATA_VALUES;
extern unsigned char  _sdata;//INIT_DATA_START;
extern unsigned char  _edata;//INIT_DATA_END;
extern unsigned char  _sbss;//BSS_START;
extern unsigned char  _ebss;//BSS_END;
//#define __bss_start__ BSS_START
//#define __bss_end__ BSS_END

extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));

typedef void (*fptr)(void);
// the section "vectors" is placed at the beginning of flash 
// by the linker script
#pragma GCC push_options
#pragma GCC optimize ("O0")



const fptr Vectors[] __attribute__((section(".vectors"))) ={


			(fptr)0x20002000, 	/* Top of stack (8k) */
			init,
		  Default_Handler,//NMI_Handler,
		   HardFault_Handler,
		   Default_Handler,//MemManage_Handler,
		   Default_Handler,//BusFault_Handler,
		   Default_Handler,//UsageFault_Handler,
		  	0,
		  0,
		  	0,
		  	0,
			Default_Handler,//SVC_Handler,
			Default_Handler,//DebugMon_Handler,
		  	0,
			Default_Handler,//PendSV_Handler,
		  	SysTick_Handler,
			Default_Handler,//WWDG_IRQHandler,          			/* Window Watchdog interrupt                        */
			Default_Handler,//PVD_IRQHandler,           			/* PVD through EXTI line detection interrupt        */
			Default_Handler,//TAMPER_IRQHandler,         			/* Tamper interrupt                                 */
		  	RTC_IRQHandler,            			/* RTC global interrupt                             */
			Default_Handler,//FLASH_IRQHandler,          			/* Flash global interrupt                           */
			Default_Handler,//RCC_IRQHandler,            			/* RCC global interrupt                             */
		  	EXTI0_IRQHandler,          			/* EXTI Line0 interrupt                             */
			Default_Handler,//EXTI1_IRQHandler,         			/* EXTI Line1 interrupt                             */
			Default_Handler,//EXTI2_IRQHandler,          			/* EXTI Line2 interrupt                             */
			Default_Handler,//EXTI3_IRQHandler,          			/* EXTI Line3 interrupt                             */
			Default_Handler,//EXTI4_IRQHandler,          			/* EXTI Line4 interrupt                             */
			Default_Handler,//DMA1_Channel1_IRQHandler,  			/* DMA1 Channel1 global interrupt                   */
			Default_Handler,//DMA1_Channel2_IRQHandler,  			/* DMA1 Channel2 global interrupt                   */
			Default_Handler,//DMA1_Channel3_IRQHandler,  			/* DMA1 Channel3 global interrupt                   */
			Default_Handler,//DMA1_Channel4_IRQHandler,  			/* DMA1 Channel4 global interrupt                   */
			Default_Handler,//DMA1_Channel5_IRQHandler,  			/* DMA1 Channel5 global interrupt                   */
			Default_Handler,//DMA1_Channel6_IRQHandler,  			/* DMA1 Channel6 global interrupt                   */
			Default_Handler,//DMA1_Channel7_IRQHandler,  			/* DMA1 Channel7 global interrupt                   */
			Default_Handler,//ADC1_2_IRQHandler,         			/* ADC1 and ADC2 global interrupt                   */
			Default_Handler,//USB_HP_CAN_TX_IRQHandler,  			/* USB High Priority or CAN TX interrupts           */
			Default_Handler,//USB_LP_CAN_RX0_IRQHandler, 			/* USB Low Priority or CAN RX0 interrupts           */
			Default_Handler,//CAN_RX1_IRQHandler,        			/* CAN RX1 interrupt                                */
			Default_Handler,//CAN_SCE_IRQHandler,        			/* CAN SCE interrupt                                */
			Default_Handler,//EXTI9_5_IRQHandler,        			/* EXTI Line[9:5] interrupts                        */
			Default_Handler,//TIM1_BRK_IRQHandler,       			/* TIM1 Break interrupt                             */
			Default_Handler,//TIM1_UP_IRQHandler,        			/* TIM1 Update interrupt                            */
			Default_Handler,//TIM1_TRG_COM_IRQHandler,   			/* TIM1 Trigger and Commutation interrupts          */
			Default_Handler,//TIM1_CC_IRQHandler,        			/* TIM1 Capture Compare interrupt                   */
			Default_Handler,//TIM2_IRQHandler,           			/* TIM2 global interrupt                            */
			Default_Handler,//TIM3_IRQHandler,           			/* TIM3 global interrupt                            */
			Default_Handler,//TIM4_IRQHandler,           			/* TIM4 global interrupt                            */
			Default_Handler,//I2C1_EV_IRQHandler,        			/* I2C1 event interrupt                             */
			Default_Handler,//I2C1_ER_IRQHandler,        			/* I2C1 error interrupt                             */
			Default_Handler,//I2C2_EV_IRQHandler,       			/* I2C2 event interrupt                             */
			Default_Handler,//I2C2_ER_IRQHandler,        			/* I2C2 error interrupt                             */
			Default_Handler,//SPI1_IRQHandler,           			/* SPI1 global interrupt                            */
			Default_Handler,//SPI2_IRQHandler,          			/* SPI2 global interrupt                            */
			Default_Handler,//USART1_IRQHandler,         			/* USART1 global interrupt                          */
			Default_Handler,//USART2_IRQHandler,         			/* USART2 global interrupt                          */
			Default_Handler,//USART3_IRQHandler,         			/* USART3 global interrupt                          */
			Default_Handler,//EXTI15_10_IRQHandler,      			/* EXTI Line[15:10] interrupts                      */
			Default_Handler,//RTCAlarm_IRQHandler,       			/* RTC Alarms through EXTI line interrupt           */
		  	0,                         			/* Reserved                                         */
			Default_Handler,//TIM8_BRK_IRQHandler,       			/* TIM8 Break interrupt                             */
			Default_Handler,//TIM8_UP_IRQHandler,        			/* TIM8 Update interrupt                            */
			Default_Handler,//TIM8_TRG_COM_IRQHandler,   			/* TIM8 Trigger and Commutation interrupts          */
			Default_Handler,//TIM8_CC_IRQHandler,        			/* TIM8 Capture Compare interrupt                   */
			Default_Handler,//ADC3_IRQHandler,           			/* ADC3 global interrupt                            */
			Default_Handler,//FSMC_IRQHandler,           			/* FSMC global interrupt                            */
			Default_Handler,//SDIO_IRQHandler,           			/* SDIO global interrupt                            */
			Default_Handler,//TIM5_IRQHandler,           			/* TIM5 global interrupt                            */
			Default_Handler,//SPI3_IRQHandler,           			/* SPI3 global interrupt                            */
			Default_Handler,//UART4_IRQHandler,          			/* UART4 global interrupt                           */
			Default_Handler,//UART5_IRQHandler,          			/* UART5 global interrupt                           */
			Default_Handler,//TIM6_IRQHandler,           			/* TIM6 global interrupt                            */
			Default_Handler,//TIM7_IRQHandler,           			/* TIM7 global interrupt                            */
			Default_Handler,//DMA2_Channel1_IRQHandler,  			/* DMA2 Channel1 global interrupt                   */
			Default_Handler,//DMA2_Channel2_IRQHandler,  			/* DMA2 Channel2 global interrupt                   */
			Default_Handler,//DMA2_Channel3_IRQHandler,  			/* DMA2 Channel3 global interrupt                   */
			Default_Handler,//DMA2_Channel4_5_IRQHandler		/* DMA2 Channel4 and DMA2 Channel5 global interrupt */
};

void init_array()
{
    // This function calls constructors for global and static objects
    uint32_t count;
    uint32_t i;
    
    count = __preinit_array_end - __preinit_array_start;
    for (i = 0; i < count; i++)
        __preinit_array_start[i] ();
    count = __init_array_end - __init_array_start;
    for (i = 0; i < count; i++)
        __init_array_start[i] (); 
}


void init()
{
// do global/static data initialization
	unsigned char *src;
	unsigned char *dest;
	unsigned len;
  //  initClock();
	src= &_sidata;//INIT_DATA_VALUES;
	dest= &_sdata;//INIT_DATA_START;
	len= &_edata-&_sdata;
	while (len--)
		*dest++ = *src++;
// zero out the uninitialized global/static variables
	dest = &_sbss;
	len = &_ebss - &_sbss;
	while (len--)
		*dest++=0;
    init_array();

	main();
}

void Default_Handler()
{
	while(1);
}
void HardFault_Handler()
{
	while(1);
}

#pragma GCC pop_options
