
#include "system.h"
#include "buttons.h"
#include "menu.h"
#include "encoder.h"
//#include "uprot.h"
#include <stdlib.h>
#include <stdint.h>
#include "lampdisplay.h"



ConfigureMenu::ConfigureMenu(uint8_t countValues, Encoder* encoder, volatile Button* button, GlobalTime* time)
{
	count = countValues;
	fptr = new func_t[countValues];
	maxVals = new uint32_t[countValues];
	values = new uint32_t[countValues];
	enco = encoder;
	butt = button;
	isInConfigurationMode = false;
	configurationTimeout = 0;

	timePtr = time;
}

bool ConfigureMenu::setFunction(uint8_t index, func_t ptr, uint32_t maxValue, uint32_t currentValue)
{
	if(index>=count) return false;
	fptr[index] = ptr;
	maxVals[index] = maxValue;
	values[index] = currentValue;
	return true;
}
//Обработка пользовательского интерфейса ввода
bool ConfigureMenu::handleUI()
{
	signed char es = 0;
	unsigned short int ev = 0;
	char bs = 0;
	//if(configurationTimeout>CONFIG_MODE_LIFETIME)isInConfigurationMode = false;
	bs = handleButtInt(butt);
	es = enco->handleEncoder(&ev);

	if(es||bs){ return configure(bs,ev,es); }
	return isInConfigurationMode;
}
bool ConfigureMenu::configure(char bv, uint16_t ev, signed char sign)
{

	static unsigned short menuItem = 0;

	if(!isInConfigurationMode)
	{

		//Обработка вращения энкодера вне режима меню
		if(sign!=0)//Если было вращение энкодера
		{
			if(sign>0){ }
			else if(sign<0){ }
			return false;
		}

		//Обработка кнопок вне режима меню
		switch (bv)
		{
		//	ledRedTuggle();
		case BUTT_SHORTCLICK:
		{

		}
		case BUTT_LONGCLICK:
		{
			isInConfigurationMode = true;
			menuItem = 3;
			enco->setEncVal(0);
			enco->setMaxEncVal(23);
			break;
		}
		case BUTT_DOUBLECLICK:
		{
			isInConfigurationMode = true;
			menuItem = 0;
						enco->setEncVal(values[menuItem]);
						enco->setMaxEncVal(maxVals[menuItem]);
			break;
		}
		default:break;
		}
	}

	if(isInConfigurationMode)
	{

		//lampConfigure 8 lamps, 24 hours on each
		if(menuItem > 2)
		{
			uint32_t mask;

			mask = 0x00000001<<(uint32_t)ev;//lampSubValue;
			if(bv == BUTT_SHORTCLICK)
			{
				if(values[menuItem] & mask) values[menuItem] &= ~mask; else values[menuItem] |= mask;
			}
			else
			if(bv == BUTT_DOUBLECLICK)
			{
					menuItem++;
					//menuItem++;
					if(menuItem>=count)
					{
						menuItem = 0;
						setEncVal(0);
						setMaxEncVal(23);
						isInConfigurationMode = false;
						return false;
					}

							//	setEncVal(ev = values[menuItem]);
							//	setMaxEncVal(maxVals[menuItem]);
			}

		//	if(sign!=0)//Если было вращение энкодера
		//	{
		//			if(sign>0){ lampSubValue++; }
		//			else if(sign<0){ lampSubValue--; }

		//	}
			//disp->drawDebug2(menuItem, ev, values[menuItem]&mask);
			uint8_t lampNo = (menuItem - 1)/2 - 1;
			uint8_t colorIndex = menuItem%2;

			disp->drawLampChannelsConfig(lampNo, colorIndex, ev, values[menuItem]&mask);
			switchMenu(menuItem, values[menuItem]);
			//values[menuItem] = mask;
		}
		else
		{





		configurationTimeout = 0;
		if(bv == BUTT_SHORTCLICK)
		{
			menuItem++;
			//menuItem++;
			if(menuItem>=3)
			{
				menuItem = 0;
				setEncVal(values[0]);
				setMaxEncVal(maxVals[0]);
				isInConfigurationMode = false;
				return false;
			}

			setEncVal(ev = values[menuItem]);
			setMaxEncVal(maxVals[menuItem]);
		}
		if(bv||sign)
		{

			switchMenu(menuItem,ev);
			disp->drawTimeConfig(menuItem , timePtr->h, timePtr->m, timePtr->s);
		}
		values[menuItem] = ev;
		}


		return true;
	}
	return false;

}

void ConfigureMenu::switchMenu(char punkt, uint32_t val)
{

		(*fptr[punkt])(val);

}
/*
#define CONF_MODE_TIME 0x01
#define CONF_MODE_INTERV 0x02
#define CONF_MODE_OFF 0x00

#define CONF_LIFETIME 25000
const char MENU_MODE_COUNT = 2;
extern char showMode;
extern char displayBright;
extern char timeHour, timeMinute, timeSec;
extern char offHour, offMinute, onHour, onMinute;

char onOffHoursArray[24] = {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0};

//количества пунктов меню
enum configCounts
{
	 MENU_COUNT_TIME = 0x02, MENU_COUNT_INTERV = 24 
};


enum configMenuValues
{
	ITEM_TIME_HOUR = 0x00, ITEM_TIME_MINUTES = 0x01,
	ITEM_INTERVALON_H = 0x00, ITEM_INTERVALON_M = 0x01,
	ITEM_INTERVALOFF_H = 0x02, ITEM_INTERVALOFF_M = 0x03
};

enum maxMenuValues
{
		MAX_HOUR = 23, MAX_MIN = 59
};

unsigned char menuCounts[MENU_MODE_COUNT] = {MENU_COUNT_TIME,MENU_COUNT_INTERV};



const unsigned short int configMaxValuesTime[MENU_COUNT_TIME] = {MAX_HOUR,MAX_MIN};
const unsigned short int configMaxValuesInterval[MENU_COUNT_INTERV] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
const unsigned short int* configMaxValues[MENU_MODE_COUNT] = {configMaxValuesTime,configMaxValuesInterval}; 


unsigned short int configCurrentValuesTime[MENU_COUNT_TIME];
unsigned short int configCurrentValuesInterval[MENU_COUNT_INTERV];
unsigned short int* configCurrentValues[MENU_MODE_COUNT] = {configCurrentValuesTime, configCurrentValuesInterval};

volatile unsigned char isInConfigurationMode = CONF_MODE_OFF;
unsigned short int configurationTimeout = 0;
//Включает режим конфигурации
//extern volatile char flgLongButt;

extern volatile unsigned short int flgC;

extern unsigned char ledMode;
extern volatile unsigned short int flgD;
extern void clearButtState(volatile struct Button *bt);
extern volatile struct Button bt1, bt2, bt0;
extern volatile struct Button* be;


extern volatile unsigned int ctmr;
unsigned char ledEffType= 0;
extern volatile unsigned char gdiVal[6];	
//extern unsigned short int colors[WS_ENCO_VAL];
//Количество значений

extern unsigned short int arr[];
extern unsigned short int arr[];

void confClock(char punkt, unsigned short int val)
{
	//if(!punkt)timeHour = val; else { timeMinute = val; setTimeRTC(timeHour,timeMinute,0);}
}

void confOffHour(unsigned short int value)
{
	offHour = value;
}

void confOffMinute(unsigned short int value)
{
	offMinute = value;
}

void confOnHour(unsigned short int value)
{
	onHour = value;
}

void confOnMinute(unsigned short int value)
{
	onMinute = value;
}

__inline void swMenu(char punkt, unsigned short int val)
{
	if(isInConfigurationMode == CONF_MODE_TIME){
	configCurrentValuesTime[punkt] = val;
	confClock(punkt,val);	lcdMax7219ShowTime4Dig(1,timeHour,timeMinute,timeSec);}
	else if(isInConfigurationMode == CONF_MODE_INTERV)
	{
		
		onOffHoursArray[punkt] = val;
		showOnOffConf(punkt,val);
		configCurrentValuesInterval[punkt] = val;
		setOnOffHourToBKP(punkt,val);

	}
	//uSendMsgNum("menu punkt =",(unsigned short int)punkt);
	//uSendMsgNum("val =",(unsigned short int)val); uSendMsg("\n");

	//setTlc5940LedBright(punkt, brightCoefficents[val]); tlc5940Refresh();
//show2Numbers(punkt,val);
}

void initConfVals(void)
{
	int i = 0;
//	while(i<MENU_COUNT_TIME)
  configCurrentValuesTime[0] = timeHour;
	configCurrentValuesTime[1] = timeMinute;
  while(i<MENU_COUNT_INTERV){ configCurrentValuesInterval[i] = onOffHoursArray[i]; i++;}
	
	
	
	RG_ENCODER_MAX_VAL = 23*2;
	
}
																										
void initConfig(void)
{
	RG_ENCODER_MAX_VAL = 5;
	RG_ENCODER_VAL = 0;
	initConfVals();
	
	#ifdef ENC_BT0
	be = &bt0;
	#endif
	#ifdef ENC_BT1
	be = &bt1;
	#endif
	#ifdef ENC_BT2
	be = &bt2;
	#endif
}	

void confByEnc(unsigned char bv, unsigned short int ev, signed char sign)
{
	static unsigned short menuItem = 0;
	
	if(isInConfigurationMode == CONF_MODE_OFF)
	{
		//Обработка вращения энкодера вне режима меню
		if(sign!=0)//Если было вращение энкодера
		{
			if(!(RG_BUTT_INPREG&be->buttBit))//Если зажата кнопка
			{
				clearButtState(be);
			}
			else 
			{
				
			}
			
			if(sign>0){ displayPrint(0, "ENCO_L"); displayBright++; if(displayBright >0x0f) displayBright = 0x0f; lcdMax7219SetBright(displayBright);}
			else if(sign<0){ displayPrint(0, "enco_r"); displayBright--; if(displayBright<0x01) displayBright = 0x01; lcdMax7219SetBright(displayBright);}
			
			//swMenu(menuItem,menuVal);
			//configCurrentValues[menuItem] = menuVal;
			return;
		}
		
		//Обработка кнопок вне режима меню
		switch (bv)
		{
		//	ledRedTuggle();
			case BUTT_SHORTCLICK:{ displayPrint(1, "butt_short"); showMode++; if(showMode>0x03)showMode = 0; return;}
			case BUTT_DOUBLECLICK:
			{ 
				isInConfigurationMode = CONF_MODE_INTERV; 
				setEncVal(ev = configCurrentValues[isInConfigurationMode-1][menuItem]);	
				setMaxEncVal(configMaxValues[isInConfigurationMode-1][menuItem]);
				break;
			}
			case BUTT_LONGCLICK:
			{ 
				isInConfigurationMode = CONF_MODE_TIME; 
				configCurrentValuesTime[0] = timeHour;
				configCurrentValuesTime[1] = timeMinute;
				setEncVal(ev = configCurrentValues[isInConfigurationMode-1][menuItem]);	
				setMaxEncVal(configMaxValues[isInConfigurationMode-1][menuItem]);
				break;
			}
			default:break;
		}
	}
	
	if(isInConfigurationMode)
	{
		configurationTimeout = 0;
		if(bv == BUTT_SHORTCLICK)
		{
			menuItem++;
		//menuItem++;	
			if(menuItem>=menuCounts[isInConfigurationMode-1])
			{
				menuItem = 0;
				setEncVal(displayBright);
				setMaxEncVal(0x0f);
				//setEncVal(ev = configCurrentValues[isInConfigurationMode-1][menuItem]);	
				//setMaxEncVal(configMaxValues[isInConfigurationMode-1][menuItem]);
				isInConfigurationMode = CONF_MODE_OFF;
				return;
			}
			setEncVal(ev = configCurrentValues[isInConfigurationMode-1][menuItem]);	
		  setMaxEncVal(configMaxValues[isInConfigurationMode-1][menuItem]);
		}	
		if(bv||sign) swMenu(menuItem,ev);
	}
	}
*/

