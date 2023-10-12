/*
 * lampdriver.h
 *
 *  Created on: Oct 12, 2023
 *      Author: vit
 */

#ifndef LAMPDRIVER_H_
#define LAMPDRIVER_H_
#include "led.h"

class LampDriver
{
	uint8_t countChannels { 0 };
	Led** ledsPtr { nullptr };
	uint8_t** timesPtr { nullptr };

public:
	LampDriver(uint8_t count, Led** ptrToLamps);
	virtual ~LampDriver();

	void setTimeOnOff(uint8_t lampIndex, uint8_t timeIndex, uint8_t on);
	void driveLamps( uint8_t currentHour );
};

#endif /* LAMPDRIVER_H_ */
