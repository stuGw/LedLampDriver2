#ifndef BUTTONS_H
#define BUTTONS_H
#include "system.h"



#define RG_ENCODER_VAL TIM4->CNT
#define RG_ENCODER_MAX_VAL TIM4->ARR

#define RG_BUTT_INPREG GPIOB->IDR
#define BUTT_NEXT_PB0 0x00000001
#define BUTT_ENTER_PB1 0x00000002
#define BUTT_PREV_PB2 0x00000004

#define BUTT_CHECK_TIME 100
#define BUTT_COUNT_CLD_ONE 1
#define BUTT_LONG 3
#define BUTT_SHORT 1
#define BUTT_COUNT_CLD_TWO 2
#define BUTT_DOUBLE 2
#define BUTT_ON 1
#define BUTT_OFF 0
#define BUTT_CNT_LONG 800
#define BUTT_CNT_SHORT 70
#define BUTT_CLK_LONG 3
#define BUTT_CLK_DOUBLE 2
#define BUTT_CLK_SHORT 1

#define BUTT_DOUBLECLICK 2
#define BUTT_SHORTCLICK 1
#define BUTT_LONGCLICK 3
#define BUTT_DOUBLECLICK_P 12
#define BUTT_SHORTCLICK_P 11
#define BUTT_LONGCLICK_P 13
#define BUTT_LIFETIME 500
#define BUTT_DELAY 30

#define ENC_DEV_COEF 2
#define ENC_BT0
 struct Button
{
	volatile char st;
		volatile char dn;
		volatile char up;
		volatile unsigned int tm;
		volatile unsigned int tmd;
		volatile char ipt;
		volatile char flagPare;
		volatile short int buttBit;
};

void clearButtState(volatile struct Button* bt);
char checkButtState(volatile struct Button* bt);
//Обработка прерывания по нажатию кнопки
char handleButtInt(volatile struct Button* bt);
signed char handleEncoder(unsigned short int *val);
void initButtons(volatile struct Button* bt0);
unsigned short int getEncVal(void);
void setEncVal(unsigned short int val);
void setMaxEncVal(unsigned short int mval);
#endif//BUTTONS_H
