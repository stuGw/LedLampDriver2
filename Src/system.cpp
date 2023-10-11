/*
 * system.cpp
 *
 *  Created on: Oct 5, 2023
 *      Author: Виталий
 */
#include "system.h"

void systemClockInit()
{
	//HSE on
	RCC->CR|=RCC_CR_HSEON;
	//Wait HSE
	while (!(RCC->CR & RCC_CR_HSERDY)) {};

    //Set HSE As system clock
	RCC->CFGR &=~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSE;

	//Enable clock security system
	RCC->CR|=RCC_CR_CSSON;

	//PLL

	RCC->CFGR &=~((RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE|RCC_CFGR_PLLMULL)); // predochistka
	RCC->CFGR|=RCC_CFGR_PLLSRC;//RCC_CFGR_PLLSRC_HSE; //vibyraem istochnik HSE
	RCC->CFGR|=RCC_CFGR_PLLMULL5; // koefficient umnojenia - 2
	RCC->CR |= RCC_CR_PLLON; // vklychaem PLL
	while ((RCC->CR & RCC_CR_PLLRDY)==0) {} //jdem gotovnosti  PLL.
	RCC->CFGR &=~RCC_CFGR_SW; // vklychaem HSI pered zadaniem PLL.
	RCC->CFGR |= RCC_CFGR_SW_PLL; //vklychaem PLL kak osnovnoy istochnikPLL.
	while ((RCC->CFGR&RCC_CFGR_SWS)!=0x08) {} // jdem gotovnosti PLL.

}

volatile  void delay_us(volatile uint32_t val)
{
	volatile uint32_t delay = val*CORE_CLOCK_MHZ;
	uint32_t tmp = val;//*10;
	tmp = tmp - 1;
	while(delay--);
	//	{
	//		delay = delay - 1;
	//	}
}

volatile  void delay_ms(volatile uint32_t val)
{
	delay_us(val*100);
}


