/*
 * system.h
 *
 *  Created on: Apr 7, 2022
 *      Author: vit
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "stm32f1xx.h"

#define QUARZ_FREQ (8000000)
#define MUL_CLOCK_COEF (5)
#define SYS_CORE_CLOCK (QUARZ_FREQ*MUL_CLOCK_COEF)
#define CORE_CLOCK_MHZ (SYS_CORE_CLOCK/1000000)
#define SYSTMR_FREQ 1000
#define SYS_TIMER_FREQ SYS_CORE_CLOCK/SYSTMR_FREQ-1
//#define FREQ_HZ 72000000
//#define FREQ_MHZ FREQ_HZ/1000000

#define GPIOPIN_0  (0x00000001)
#define GPIOPIN_1  (0x00000002)
#define GPIOPIN_2  (0x00000004)
#define GPIOPIN_3  (0x00000008)
#define GPIOPIN_4  (0x00000010)
#define GPIOPIN_5  (0x00000020)
#define GPIOPIN_6  (0x00000040)
#define GPIOPIN_7  (0x00000080)
#define GPIOPIN_8  (0x00000100)
#define GPIOPIN_9  (0x00000200)
#define GPIOPIN_10 (0x00000400)
#define GPIOPIN_11 (0x00000800)
#define GPIOPIN_12 (0x00001000)
#define GPIOPIN_13 (0x00002000)
#define GPIOPIN_14 (0x00004000)
#define GPIOPIN_15 (0x00008000)


void systemClockInit();

volatile  void delay_us(volatile uint32_t val);

volatile  void delay_ms(volatile uint32_t val);

#endif /* SYSTEM_H_ */
