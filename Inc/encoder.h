/*
 * encoder.h
 *
 *  Created on: 5 окт. 2023 г.
 *      Author: Виталий
 */

#ifndef ENCODER_H_
#define ENCODER_H_
#include <stdint.h>

class Encoder {
	volatile uint32_t* valuePtr {nullptr};
	volatile uint32_t* maxValuePtr { nullptr };
	uint32_t encoderDevideCoefficient { 2 };
public:
	Encoder(volatile uint32_t* valueRegister, volatile uint32_t* maxValueRegister, uint32_t maxValue, uint32_t devideCoef);
	signed char handleEncoder(unsigned short int *val);

	unsigned short int getEncVal(){ return *valuePtr/encoderDevideCoefficient; }
	void setEncVal(unsigned short int val){ *valuePtr = val*encoderDevideCoefficient; }
	void setMaxEncVal(unsigned short int mval) { *maxValuePtr = (mval*encoderDevideCoefficient) + 1; }

	virtual ~Encoder();
};

#endif /* ENCODER_H_ */
