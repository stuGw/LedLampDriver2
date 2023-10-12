#ifndef MENU_H
#define MENU_H
#include "buttons.h"

#define CONFIG_MODE_ON 0x01
#define CONFIG_MODE_OFF 0x00
#define CONFIG_MODE_LIFETIME 15000

#define CONF_GDI_YARK  0x01
#define CONF_TIME_VALUE 0x02
#define CONF_DATE_VALUE 0x03
#define CONF_NO_VALUE 0x00

#define MENU_COUNT_VAL 15

#define CONF_GD_Y   0x00
#define CONF_GD_EFF 0x01
#define CONF_TM_H 	0x02
#define CONF_TM_M 	0x03
#define CONF_TM_S 	0x04
#define CONF_DT_D 	0x05
#define CONF_DT_M 	0x06
#define CONF_DT_Y 	0x07
#define CONF_LC_ALL 0x08
#define CONF_LC_1 	0x09
#define CONF_LC_2 	0x0A
#define CONF_LC_3 	0x0B
#define CONF_LC_4 	0x0C
#define CONF_LC_5 	0x0D
#define CONF_LC_6 	0x0E
#define CONF_LB_ALL 0x0F
#define CONF_LB_1 	0x10
#define CONF_LB_2 	0x11
#define CONF_LB_3 	0x12
#define CONF_LB_4 	0x13
#define CONF_LB_5 	0x14
#define CONF_LB_6 	0x15
#define CONF_SEC_TYPE 0x16
#define CONF_GD_FE  0x17
#define CONF_GD_RUE 0x18
#define CONF_GD_COMMA 0x19
#define CONF_DATA_INTERV 0x1A
//#define CONF_GD_RVE 0x19


#define COUNT_LED_EFF 8
#define SEC_TYPE_MAX 0x01


#define CONF_DT_TIME_MAX 5
#define FLG_SHOW_NO 0x00
#define FLG_SHOW_TM 0x01
#define FLG_SHOW_DT 0x02
#define LC_RNB_MAX 0x03
#define RUE_EFF_MAX 0x05
#define COMMA_EFF_MAX 0x01
#define DATA_INTERV_MAX 0x03


																							
__inline void confSetYark(unsigned short int currValue);
__inline void confSetHour(unsigned short int currValue);
__inline void confSetMinute(unsigned short int currValue);
__inline void confSetSec(unsigned short int currValue);
__inline void confSetDay(unsigned short int currValue);
__inline void confSetMonth(unsigned short int currValue);
__inline void confSetYear(unsigned short int currValue);
//Config all leds color
__inline void confAllLedsColor(unsigned short int currValue);
void confAllLedsBright(unsigned short int currValue);
__inline void confLedColor(unsigned short int currValue, unsigned char ledInd);
__inline void confLedBright(unsigned short int currValue,unsigned char led);
__inline void confSecType(unsigned short int currValue);
__inline void confSetGdiEff(unsigned short int currValue);
__inline void confSetGdiFire(unsigned short int currValue);
__inline void confRueEff(unsigned short int currValue);
__inline void confCommaEff(unsigned short int currValue);
__inline void confDataInterv(unsigned short int currValue);
__inline void confGdiRve(unsigned short int currValue);
__inline void swMenu(char punkt, unsigned short int val);
void initConfVals(void);							
void initConfig(void);
__inline void confBButt(char bLeft, char bRight);
void confByEnc(unsigned char bv, unsigned short int ev, signed char sign);
void confByEncM(unsigned char bv, unsigned short int ev, signed char sign);
//Обработка пользовательского интерфейса ввода
void handleUI(volatile struct Button* bt);


#endif//MENU_H
