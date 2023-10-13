/*
 * hd4780display.cpp
 *
 *  Created on: Apr 7, 2022
 *      Author: vit
 */

#include "hd44780display.h"
//#include "system.h"


HD44780Display::HD44780Display() {
	// TODO Auto-generated constructor stub

}
/*
HD44780Display::~HD44780Display() {
	// TODO Auto-generated destructor stub
}
*/
void HD44780Display::setInterface(HD44780Display::Interface iface, volatile uint32_t* port, PinsMask pMask)
{
	iotype = iface;
	ioport = port;
	pinsMask = pMask;
}
void HD44780Display::setInterface(HD44780Display::Interface iface, uint8_t i2cDevAddress, void (*i2cf)(uint8_t, uint16_t, uint8_t, uint8_t*))
{
	iotype = iface;
	i2cSend = i2cf;
	lcdAddress = i2cDevAddress;
}

void HD44780Display::setByte(uint8_t byte, bool isFull)
{
	if(isFull)
	{
		if(byte&0x01)*ioport |= pinsMask.DB0; else *ioport &= ~pinsMask.DB0;
		if(byte&0x02)*ioport |= pinsMask.DB1; else *ioport &= ~pinsMask.DB1;
		if(byte&0x04)*ioport |= pinsMask.DB2; else *ioport &= ~pinsMask.DB2;
		if(byte&0x08)*ioport |= pinsMask.DB3; else *ioport &= ~pinsMask.DB3;
		if(byte&0x10)*ioport |= pinsMask.DB4; else *ioport &= ~pinsMask.DB4;
		if(byte&0x20)*ioport |= pinsMask.DB5; else *ioport &= ~pinsMask.DB5;
		if(byte&0x40)*ioport |= pinsMask.DB6; else *ioport &= ~pinsMask.DB6;
		if(byte&0x80)*ioport |= pinsMask.DB7; else *ioport &= ~pinsMask.DB7;
	}
	else
	{
		if(byte&0x1)*ioport |= pinsMask.DB4; else *ioport &= ~pinsMask.DB4;
		if(byte&0x2)*ioport |= pinsMask.DB5; else *ioport &= ~pinsMask.DB5;
		if(byte&0x4)*ioport |= pinsMask.DB6; else *ioport &= ~pinsMask.DB6;
		if(byte&0x8)*ioport |= pinsMask.DB7; else *ioport &= ~pinsMask.DB7;
	}

}

void HD44780Display::sendHalfByte(uint8_t byte, bool isData)
{
	if(isData) *ioport |= pinsMask.RS; else *ioport &= ~pinsMask.RS; //lcdDataMode(isData);



	setByte(byte,false); //GPIOA->ODR |= byte;
	*ioport |= pinsMask.E;//lcdEnUp();
	delay_ms(10);
	*ioport &= ~pinsMask.E;//lcdEnDwn();
}

void HD44780Display::sendHalfByteCmd(uint8_t byte, bool isData)
{
	if(isData) *ioport |= pinsMask.RS; else *ioport &= ~pinsMask.RS; //lcdDataMode(isData);



	setByte(byte,false); //GPIOA->ODR |= byte;
	*ioport |= pinsMask.E;//lcdEnUp();
	delay_ms(1);
	*ioport &= ~pinsMask.E;//lcdEnDwn();
}


void HD44780Display::sendByte(uint8_t byte, bool isData)
{

	if(isData) *ioport |= pinsMask.RS; else *ioport &= ~pinsMask.RS; //lcdDataMode(isData);

	if(iotype == IFACE_PARRALEL8)
	{
		setByte(byte,true); //GPIOA->ODR |= byte;
		*ioport |= pinsMask.E;//lcdEnUp();
		delay_ms(1);
		*ioport &= ~pinsMask.E;//lcdEnDwn();
	}
	else if(iotype == IFACE_PARRALEL4)
	{
		setByte(byte>>4,false);//H

		*ioport |= pinsMask.E;//lcdEnUp();
		delay_us(10);
		*ioport &= ~pinsMask.E;//lcdEnDwn();

		setByte(byte,false);//L
		*ioport |= pinsMask.E;//lcdEnUp();
		delay_us(10);
		*ioport &= ~pinsMask.E;//lcdEnDwn();
	}
}
/*
void HD44780Display::sendByte(uint8_t byte, bool isData)
{

	if(isData) *ioport |= pinsMask.RS; else *ioport &= ~pinsMask.RS; //lcdDataMode(isData);

	*ioport |= pinsMask.E;//lcdEnUp();

	if(iotype == IFACE_PARRALEL8)
	{
		setByte(byte,true); //GPIOA->ODR |= byte;
		delay_ms(20);
		*ioport &= ~pinsMask.E;//lcdEnDwn();
	}
	else if(iotype == IFACE_PARRALEL4)
	{
		setByte(byte>>4,false);//H

		delay_ms(1);
		*ioport &= ~pinsMask.E;//lcdEnDwn();

		delay_ms(1);
		*ioport |= pinsMask.E;//lcdEnUp();

		setByte(byte,false);//L
		delay_ms(1);
		*ioport &= ~pinsMask.E;//lcdEnDwn();
	}
}*/
void HD44780Display::I2CSend(uint8_t* data, uint8_t count)
{
	i2cSend(0, lcdAddress, count, data);
}
void HD44780Display::initByI2C(uint8_t countLines, uint8_t countSymbols)
{
	rows = countLines; cols = countSymbols;
	//data = 0x3
	uint8_t buffer[24];

	buffer[0] = 0x30 | I2CMasks::E;//set first command data
	buffer[1] = buffer[0]&~I2CMasks::E; //falling edge E

	I2CSend(buffer,2);//send 0x3
	delay_ms(20);
	I2CSend(buffer,2);//send 0x3
	delay_ms(20);
	I2CSend(buffer,2);//send 0x3
	delay_ms(20);

	buffer[0] = 0x20 | I2CMasks::E;
	buffer[1] = buffer[0]&~I2CMasks::E; //falling edge E
	I2CSend(buffer,2);//send 0x2

	//0x28
	buffer[0] = 0x20 | I2CMasks::E; //0x02
	buffer[1] = buffer[0]&~I2CMasks::E;

	buffer[2] = 0x80 | I2CMasks::E;//0x08
	buffer[3] = buffer[2]&~I2CMasks::E;

	//0x01
	buffer[4] = 0x00 | I2CMasks::E;
	buffer[5] = buffer[4]&~I2CMasks::E;

	buffer[6] = 0x10 | I2CMasks::E;
	buffer[7] = buffer[6]&~I2CMasks::E;

	//0x06
	buffer[8] = 0x00 | I2CMasks::E;
	buffer[9] = buffer[8]&~I2CMasks::E;

	buffer[10] = 0x60 | I2CMasks::E;
	buffer[11] = buffer[10]&~I2CMasks::E;

	//0x0f
	buffer[12] = 0x00 | I2CMasks::E;
	buffer[13] = buffer[12]&~I2CMasks::E;

	buffer[14] = 0xf0 | I2CMasks::E;
	buffer[15] = buffer[14]&~I2CMasks::E;

	//0x01
	buffer[16] = 0x00 | I2CMasks::E;
	buffer[17] = buffer[16]&~I2CMasks::E;

	buffer[18] = 0x10 | I2CMasks::E;
	buffer[19] = buffer[18]&~I2CMasks::E;

	//0x14
	buffer[20] = 0x10 | I2CMasks::E;
	buffer[21] = buffer[20]&~I2CMasks::E;

	buffer[22] = 0x40 | I2CMasks::E;
	buffer[23] = buffer[22]&~I2CMasks::E;

	I2CSend(buffer,24);

}
void HD44780Display::init(uint8_t countLines, uint8_t countSymbols)
{
	rows = countLines; cols = countSymbols;

	delay_ms(20);
	if(iotype == IFACE_PARRALEL8)
	{
		sendByte(0x38,0);delay_ms(20);
		sendByte(0x01,0);delay_ms(1);
		sendByte(0x06,0);delay_ms(1);
		sendByte(0x0f,0);delay_ms(1);
		sendByte(0x01,0);delay_ms(1);
		sendByte(0x14,0);delay_ms(1);
	}
	else if(iotype == IFACE_PARRALEL4)
	{
		sendHalfByteCmd(0x03,0);delay_ms(5);
		sendHalfByteCmd(0x03,0);delay_ms(1);
		sendHalfByteCmd(0x03,0);delay_ms(1);

		sendHalfByteCmd(0x02,0);delay_ms(1);

		sendHalfByteCmd(0x02,0);delay_ms(1);
		sendHalfByteCmd(0x08,0);delay_ms(1);

		sendHalfByteCmd(0x00,0);delay_ms(1);
		sendHalfByteCmd(0x01,0);delay_ms(1);

		sendHalfByteCmd(0x00,0);delay_ms(1);
		sendHalfByteCmd(0x06,0);delay_ms(1);

		sendHalfByteCmd(0x00,0);delay_ms(1);
		sendHalfByteCmd(0x0f,0);delay_ms(1);

		sendHalfByteCmd(0x00,0);delay_ms(1);
		sendHalfByteCmd(0x01,0);delay_ms(1);

		sendHalfByteCmd(0x01,0);delay_ms(1);
		sendHalfByteCmd(0x04,0);delay_ms(1);
	}

	unsigned char pbuff[8] = {0x03,0x05,0x09,0x09,0x09,0x09,0x11,0x00};//L
	unsigned char pbuff2[8] = {0x1f,0x10,0x10,0x1e,0x11,0x11,0x1e,0x00};//B
	unsigned char pbuff3[8] = {0x11,0x11,0x11,0x11,0x0b,0x05,0x01,0x00};//Ч
	unsigned char pbuff4[8] = {0x11,0x11,0x11,0x1d,0x13,0x13,0x1d,0x00};//Ы
	createCustomCharacter(pbuff,1);
	createCustomCharacter(pbuff2,2);
	createCustomCharacter(pbuff3,3);
	createCustomCharacter(pbuff4,4);
}

void HD44780Display::createCustomCharacter (unsigned char *Pattern, const char Location)
{
	int i=0;
	sendByte(0x40+(Location*8),0);     //Send the Address of CGRAM
	for (i=0; i<8; i++)
	sendByte(Pattern [ i ],1);         //Pass the bytes of pattern on LCD
}

void HD44780Display::refresh()
{

	print(0,buffer[0]);
	print(1,buffer[1]);
}
//---Установка позиции курсора---//
void HD44780Display::setCursor(uint8_t row, uint8_t col)
{
   char address;
   if (row == 0)
   address = 0;
   else
   address = 0x40;
   address |= col;
   sendByte(0x80 | address, 0);
}

void HD44780Display::print(uint8_t row,char *text)
{
    char *c;
		setCursor(row,0);
    c = text;
    while ((c != 0) && (*c != 0))
    {
    	sendByte(*c, 1);
        c++;
    }
}


