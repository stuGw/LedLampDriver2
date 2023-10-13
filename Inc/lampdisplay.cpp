/*++
 * lampdisplay.cpp
 *
 *  Created on: 6 окт. 2023 г.
 *      Author: Виталий
 */

#include <lampdisplay.h>
#include "led.h"
LampDisplay::LampDisplay() {
	// TODO Auto-generated constructor stub

}

LampDisplay::~LampDisplay() {
	// TODO Auto-generated destructor stub
}

void LampDisplay::fillBufferTime(uint8_t pos, uint8_t h, uint8_t m, uint8_t s)
{

	buffer[pos++] = h/10 + 0x30;
	buffer[pos++] = h%10 + 0x30;
	buffer[pos++] = ':';//h/10 + 0x30;

	buffer[pos++] = m/10 + 0x30;
	buffer[pos++] = m%10 + 0x30;
	buffer[pos++] = ':';

	buffer[pos++] = s/10 + 0x30;
	buffer[pos] =s%10 + 0x30;

}

void LampDisplay::drawTime(uint8_t h, uint8_t m, uint8_t s)
{
	clearBuff1();
	buffer[TIME_YPOS*cols + TIME_LABEL_XPOS] = 3;
	buffer[TIME_YPOS*cols + TIME_LABEL_XPOS + 1] = 'A';
	buffer[TIME_YPOS*cols + TIME_LABEL_XPOS + 2] = 'C';
	buffer[TIME_YPOS*cols + TIME_LABEL_XPOS + 3] = 4;
	buffer[TIME_YPOS*cols + TIME_LABEL_XPOS + 4] = ' ';

	fillBufferTime(TIME_YPOS*cols + TIME_LABEL_XPOS + 5, h,m,s);
	//refreshDisplay();
}

void LampDisplay::drawLampChannelsConfig(uint8_t lampNo, uint8_t lampColorm, uint8_t hour, bool on)
{
	drawLampConfigTime(lampNo, lampColorm, hour);
	drawLampConfigStatuc(on);
}

void LampDisplay::drawLampConfigTime(uint8_t lampNo, uint8_t lampColorm, uint8_t hour)
{
	char colors[2] = { 'R', 'W' };
	clearBuff0();
	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_XPOS] = lampNo+0x30;
	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_XPOS + 1]  = ' ';

	if(lampColorm)
	{
		buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS]  = 'K';
		buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS + 1]  = 'P';
		buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS + 2]  = 'A';
		buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS + 3]  = 'C';
		buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS + 4]  = 'H';
		buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS + 5]  = '.';
	}
	else
	{
		buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS]  = 2;
		buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS + 1]  = 'E';
		buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS + 2]  = 1;
		buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS + 3]  = '.';

	}

	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_HOUR_XPOS]  = 'B';// colors[lampColorm];
	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_HOUR_XPOS + 1]  = 'P';// colors[lampColorm];
	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_HOUR_XPOS + 2]  = 'E';// colors[lampColorm];
	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_HOUR_XPOS + 3]  = 'M';// colors[lampColorm];
	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_HOUR_XPOS + 4]  = ' ';// colors[lampColorm];

	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_HOUR_XPOS + 5]  = hour/10 + 0x30;// colors[lampColorm];
	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_HOUR_XPOS + 6]  = hour%10 + 0x30;// colors[lampColorm];
}

void LampDisplay::drawLampConfigStatuc(bool on)
{
	clearBuff1();
	if(on)
	{
		buffer[LAMP_CONFIG_STATE_YPOS*cols + LAMP_CONFIG_STATE_XPOS] = 'B';
		buffer[LAMP_CONFIG_STATE_YPOS*cols + LAMP_CONFIG_STATE_XPOS + 1] = 'K';
		buffer[LAMP_CONFIG_STATE_YPOS*cols + LAMP_CONFIG_STATE_XPOS + 2] = 1;//rus L
		buffer[LAMP_CONFIG_STATE_YPOS*cols + LAMP_CONFIG_STATE_XPOS + 3] = '.';
	}
	else
	{
		buffer[LAMP_CONFIG_STATE_YPOS*cols + LAMP_CONFIG_STATE_XPOS] = 'O';
		buffer[LAMP_CONFIG_STATE_YPOS*cols + LAMP_CONFIG_STATE_XPOS + 1] = 'T';
		buffer[LAMP_CONFIG_STATE_YPOS*cols + LAMP_CONFIG_STATE_XPOS + 2] = 'K';//rus L
		buffer[LAMP_CONFIG_STATE_YPOS*cols + LAMP_CONFIG_STATE_XPOS + 3] = 1;
		buffer[LAMP_CONFIG_STATE_YPOS*cols + LAMP_CONFIG_STATE_XPOS + 4] = '.';
	}
}

void LampDisplay::fillLampStatus(uint8_t pos, uint8_t status)
{
	switch (status)
	{
	case 3: { buffer[pos] = 'A'; break; }
	case 2: { buffer[pos] = 'R'; break; }
	case 1: { buffer[pos] = 'W'; break; }
	case 0: { buffer[pos] = 'X'; break; }
	default : break;
	}

}

void LampDisplay::drawLampStatus(Led** lamps)
{
	clearBuff0();
	if(lamps[0]->onState()){ buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS] = 'K'; }
	else { buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS] = 'X'; }

	if(lamps[1]->onState()){ buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 3] = 'K'; }
		else { buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 3] = 'X'; }

	if(lamps[2]->onState()){ buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 6] = 'K'; }
		else { buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 6] = 'X'; }

	if(lamps[3]->onState()){ buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 9] = 'K'; }
		else { buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 9] = 'X'; }

	if(lamps[4]->onState()){ buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 1] = 2; }
	else { buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 1] = 'X'; }

	if(lamps[5]->onState()){ buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 4] = 2; }
		else { buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 4] = 'X'; }

	if(lamps[6]->onState()){ buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 7] = 2; }
		else { buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 7] = 'X'; }

	if(lamps[7]->onState()){ buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 10] = 2; }
		else { buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 10] = 'X'; }
}


void LampDisplay::drawLampStatus(uint8_t l1, uint8_t l2, uint8_t l3, uint8_t l4)
{
	clearBuff0();
	buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS] = '1';
	fillLampStatus(LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 1, l1);
	buffer[LAMP_STATUS_YPOS*cols + LAMP1_STATUS_XPOS + 2] = ' ';

	buffer[LAMP_STATUS_YPOS*cols + LAMP2_STATUS_XPOS] = '2';
	fillLampStatus(LAMP_STATUS_YPOS*cols + LAMP2_STATUS_XPOS + 1, l2);
	buffer[LAMP_STATUS_YPOS*cols + LAMP2_STATUS_XPOS + 2] = ' ';

			buffer[LAMP_STATUS_YPOS*cols + LAMP3_STATUS_XPOS] = '3';
	fillLampStatus(LAMP_STATUS_YPOS*cols + LAMP3_STATUS_XPOS + 1, l3);
	buffer[LAMP_STATUS_YPOS*cols + LAMP3_STATUS_XPOS + 2] = ' ';

			buffer[LAMP_STATUS_YPOS*cols + LAMP4_STATUS_XPOS] = '4';
	fillLampStatus(LAMP_STATUS_YPOS*cols + LAMP4_STATUS_XPOS + 1, l4);
	buffer[LAMP_STATUS_YPOS*cols + LAMP4_STATUS_XPOS + 2] = ' ';
}

void LampDisplay::drawTimeConfig(uint8_t menuItem, uint8_t hour, uint8_t min, uint8_t sec)
{

}

void LampDisplay::drawDebug(uint8_t punkt, uint8_t value)
{
	clearBuff0();

	buffer[0*16 + 0] = 'P';
	buffer[0*16 + 1] = '-';
	buffer[0*16 + 2] = ' ';
	buffer[0*16 + 3] = punkt/10 + 0x30;
	buffer[0*16 + 4] = punkt%10 + 0x30;
	buffer[0*16 + 5] = ' ';
	buffer[0*16 + 6] = 'V';
	buffer[0*16 + 7] = '-';
	buffer[0*16 + 8] = ' ';
	buffer[0*16 + 9] = value/10 + 0x30;
	buffer[0*16 + 10] = value%10 + 0x30;
}

void LampDisplay::drawDebug2(uint8_t punkt, uint8_t value, uint32_t state)
{
	clearBuff0();

	buffer[0*16 + 0] = 'P';
	buffer[0*16 + 1] = '-';
	buffer[0*16 + 2] = ' ';
	buffer[0*16 + 3] = punkt/10 + 0x30;
	buffer[0*16 + 4] = punkt%10 + 0x30;
	buffer[0*16 + 5] = ' ';
	buffer[0*16 + 6] = 'V';
	buffer[0*16 + 7] = '-';
	buffer[0*16 + 8] = ' ';
	buffer[0*16 + 9] = value/10 + 0x30;
	buffer[0*16 + 10] = value%10 + 0x30;
	if(state)
	{
		buffer[0*16 + 11] = ' ';
		buffer[0*16 + 12] = 'O';
		buffer[0*16 + 13] = 'N';
	}
	else
	{
		buffer[0*16 + 11] = ' ';
				buffer[0*16 + 12] = 'O';
				buffer[0*16 + 13] = 'F';
	}
}
