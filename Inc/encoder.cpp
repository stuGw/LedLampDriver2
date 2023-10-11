/*
 * encoder.cpp
 *
 *  Created on: 5 окт. 2023 г.
 *      Author: Виталий
 */

#include "encoder.h"

Encoder::Encoder(volatile uint32_t* valueRegister, volatile uint32_t* maxValueRegister, uint32_t maxValue, uint32_t devideCoef) {
	// TODO Auto-generated constructor stub
	valuePtr = valueRegister;
	maxValuePtr = maxValueRegister;
	*maxValuePtr = maxValue;
	encoderDevideCoefficient = devideCoef;
}

Encoder::~Encoder() {
	// TODO Auto-generated destructor stub
}


signed char Encoder::handleEncoder(unsigned short int *val)
{
	static	unsigned short int res = 0;
	signed char s = 0;
	*val = getEncVal();
	if(((*val>res)&&((*val-res)==1))||((res-*val)==(*maxValuePtr/encoderDevideCoefficient)))s = 1;
	else if(((*val<res)&&((res-*val)==1))||((*val-res)==(*maxValuePtr/encoderDevideCoefficient)))s = -1;
	res = *val;
	return s;
}
