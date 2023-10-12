/*
 * lampdisplay.h
 *
 *  Created on: 6 окт. 2023 г.
 *      Author: Виталий
 */

#ifndef LAMPDISPLAY_H_
#define LAMPDISPLAY_H_

#include <display.h>
#include "led.h"
class LampDisplay: public Display
{
	static constexpr uint8_t TIME_XPOS { 0 };
	static constexpr uint8_t TIME_YPOS { 1 };

	static constexpr uint8_t TIME_LABEL_XPOS { 1 };

	static constexpr uint8_t LAMP_STATUS_YPOS { 0 };
	static constexpr uint8_t LAMP1_STATUS_XPOS { 3 };//1A
	static constexpr uint8_t LAMP2_STATUS_XPOS { LAMP1_STATUS_XPOS + 3 };
	static constexpr uint8_t LAMP3_STATUS_XPOS { LAMP1_STATUS_XPOS + 6 };
	static constexpr uint8_t LAMP4_STATUS_XPOS { LAMP1_STATUS_XPOS + 9 };

	static constexpr uint8_t LAMP_CONFIG_YPOS { 0 };
	static constexpr uint8_t LAMP_CONFIG_XPOS { 0 };//1A
	static constexpr uint8_t LAMP_CONFIG_COLOR_XPOS { LAMP_CONFIG_XPOS + 2 };//1A
	static constexpr uint8_t LAMP_CONFIG_HOUR_XPOS { LAMP_CONFIG_XPOS + 9 };//1A
	static constexpr uint8_t LAMP_CONFIG_STATE_YPOS { 5 };
	static constexpr uint8_t LAMP_CONFIG_STATE_XPOS { 5 };
public:
	LampDisplay();
	virtual ~LampDisplay();
	void drawTime(uint8_t h, uint8_t m, uint8_t s);
		void drawLampConfigTime(uint8_t lampNo, uint8_t lampColorm, uint8_t hour);
		void drawLampConfigStatuc(bool on);
		void drawLampStatus(uint8_t l1, uint8_t l2, uint8_t l3, uint8_t l4);
		void drawLampStatus(Led** lamps);
		void drawLampChannelsConfig(uint8_t lampNo, uint8_t lampColorm, uint8_t hour, bool on);

		void fillBufferTime(uint8_t pos, uint8_t h, uint8_t m, uint8_t s);
		void fillLampStatus(uint8_t pos, uint8_t status);
		void refresh(){ refreshDisplay(); }
};

#endif /* LAMPDISPLAY_H_ */
