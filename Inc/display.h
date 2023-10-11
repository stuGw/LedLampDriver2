/*
 * heatgendisplay.h
 *
 *  Created on: May 26, 2022
 *      Author: vit
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "hd44780display.h"



/*
 * | T1   				T2 |
 * |W(t)(wh)   V12(V60)(mh)|
 *
 * Press button S1 change W to t, next to wh, and vice versa
 * Press button S2 change V12 to V60, next to mh, and vice versa
 *
 * if Emergency on T1, T1 changed to "!ПГРЕВ" and blinking
 * if Emergency on T2, T2 changed to "!ПГРЕВ" and blinking
 * if Emergency on V12, v12 must shown and blinking
 */
class Display
{





	HD44780Display* lcd { nullptr };
protected:
	static constexpr uint8_t rows { 2 };
		static constexpr uint8_t cols { 16 };
	char *buffer { nullptr };


public:
	Display();
	virtual ~Display();

	/*void drawTime(uint8_t h, uint8_t m, uint8_t s);
	void drawLampConfigTime(uint8_t lampNo, uint8_t lampColorm, uint8_t hour);
	void drawLampConfigStatuc(bool on);
	void drawLampStatus(uint8_t l1, uint8_t l2, uint8_t l3, uint8_t l4);
*/

	void refreshDisplay();
	void setDisplay(HD44780Display* pLCD);
	void clearBuff0();
	void clearBuff1();
};

#endif /* DISPLAY_H_ */
