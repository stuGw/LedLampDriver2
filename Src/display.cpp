/*
 * heatgendisplay.cpp
 *
 *  Created on: May 26, 2022
 *      Author: vit
 */

#include <display.h>
#include "hd44780display.h"


Display::Display() {
	// TODO Auto-generated constructor stub

}

Display::~Display() {
	// TODO Auto-generated destructor stub
}


void Display::setDisplay(HD44780Display* pLCD)
{
	lcd = pLCD;
	buffer = lcd->getBuffPtr();
}


void Display::clearBuff0()
{
	for(int i = 0; i<cols; i++)buffer[i] = ' ';
}
void Display::clearBuff1()
{
	for(int i = cols; i<cols*2; i++)buffer[i] = ' ';
}
void Display::refreshDisplay()
{
		lcd->refresh();
	//	clearBuff0();
	//	clearBuff1();
}



