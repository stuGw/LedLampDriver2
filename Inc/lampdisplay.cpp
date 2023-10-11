/*++
 * lampdisplay.cpp
 *
 *  Created on: 6 окт. 2023 г.
 *      Author: Виталий
 */

#include <lampdisplay.h>

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
	buffer[TIME_YPOS*cols + TIME_LABEL_XPOS] = 'h';
	buffer[TIME_YPOS*cols + TIME_LABEL_XPOS + 1] = 'A';
	buffer[TIME_YPOS*cols + TIME_LABEL_XPOS + 2] = 'C';
	buffer[TIME_YPOS*cols + TIME_LABEL_XPOS + 3] = 'P';
	buffer[TIME_YPOS*cols + TIME_LABEL_XPOS + 4] = ' ';

	fillBufferTime(TIME_YPOS*cols + TIME_LABEL_XPOS + 5, h,m,s);
	refreshDisplay();
}

void LampDisplay::drawLampConfigTime(uint8_t lampNo, uint8_t lampColorm, uint8_t hour)
{
	char colors[2] = { 'R', 'W' };
	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_XPOS] = lampNo+0x30;
	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_XPOS + 1]  = ' ';

	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS]  = colors[lampColorm];
	buffer[LAMP_CONFIG_YPOS*cols + LAMP_CONFIG_COLOR_XPOS + 1]  = ' ';

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

void LampDisplay::drawLampStatus(uint8_t l1, uint8_t l2, uint8_t l3, uint8_t l4)
{
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
