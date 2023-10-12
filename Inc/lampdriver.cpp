/*
 * lampdriver.cpp
 *
 *  Created on: Oct 12, 2023
 *      Author: vit
 */

#include <lampdriver.h>
#include "led.h"

LampDriver::LampDriver(uint8_t count, Led** ptrToLamps) {
	// TODO Auto-generated constructor stub

	countChannels = count;
	ledsPtr = new Led*[count];
	timesPtr = new uint8_t*[count];

	int i = 0;
	while(i<count)
	{
		timesPtr[i] = new uint8_t[24];
		int j = 0;
		while(j < 24)
		{
			timesPtr[i][j] = 0;
			j++;
		}
		ledsPtr[i] = ptrToLamps[i];
		i++;
	}
}

void LampDriver::setTimeOnOff(uint8_t lampIndex, uint8_t timeIndex, uint8_t on)
{
	timesPtr[lampIndex][timeIndex] = on;
}

void LampDriver::driveLamps( uint8_t currentHour )
{
	for(int i = 0; i < countChannels; i++)
	{
		if(timesPtr[i][currentHour])ledsPtr[countChannels]->on();
		else ledsPtr[countChannels]->off();
	}
}

LampDriver::~LampDriver() {
	// TODO Auto-generated destructor stub
}

