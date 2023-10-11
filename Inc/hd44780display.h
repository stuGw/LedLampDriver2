/*
 * hd44780display.h
 *
 *  Created on: Apr 7, 2022
 *      Author: vit
 */

#ifndef HD44780DISPLAY_H_
#define HD44780DISPLAY_H_

#include <stdint.h>
#include <stdlib.h>
#include "system.h"
struct PinsMask
	{
		uint32_t E;
		uint32_t RS;

		uint32_t DB0;
		uint32_t DB1;
		uint32_t DB2;
		uint32_t DB3;
		uint32_t DB4;
		uint32_t DB5;
		uint32_t DB6;
		uint32_t DB7;


	};

/*
 *  initHD44780GPIOMode8();//init gpio
    PinsMask lcdpm;//for gpio
    lcdpm.E = 0x00000800;
    lcdpm.RS = 0x00001000;
   // lcdpm.DB0 = 0x00000001;
   // lcdpm.DB1 = 0x00000002;
   // lcdpm.DB2 = 0x00000004;
   // lcdpm.DB3 = 0x00000008;
    lcdpm.DB4 = 0x00000010;
    lcdpm.DB5 = 0x00000020;
    lcdpm.DB6 = 0x00000040;
    lcdpm.DB7 = 0x00000080;
    lcd.setInterface(HD44780Display::IFACE_PARRALEL4, &(GPIOA->ODR), lcdpm);
    lcd.init(2, 16);
    lcd.print(0, " 50C; gen=57.0B");
    lcd.print(1, " 32C; out=12.1B");
 */

class HD44780Display {


	volatile uint32_t* ioport { NULL };

	uint8_t lcdAddress { 0x37 };

	uint8_t cols { 0 };
	uint8_t rows { 0 };
    char buffer[2][16] {{'E','M','P','T','Y',' ','B','U','F','F',' ','0',' ',' ',' ',' '},
    					{' ',' ',' ',' ','E','M','P','T','Y',' ','B','U','F','F',' ','1'}};
	void setByte(uint8_t byte, bool isFull);
	void sendByte(uint8_t byte, bool isData);
	void sendHalfByte(uint8_t byte, bool isData);
	void sendHalfByteCmd(uint8_t byte, bool isData);
	PinsMask pinsMask;
	void I2CSend(uint8_t* data, uint8_t count);

	void (*i2cSend)(uint8_t, uint16_t, uint8_t, uint8_t*);
public:
	HD44780Display();
	//virtual ~HD44780Display();

	enum Interface  {IFACE_PARRALEL8 = 0, IFACE_PARRALEL4 = 1, IFACE_I2C = 2} iotype;
	enum I2CMasks {RS = 0x01, RW = 0x02, E = 0x04, BACKL = 0x08, DB4 = 0x10, DB5 = 0x20, DB6 = 0x40, DB7 = 0x80}i2cMask;
	void setInterface(HD44780Display::Interface iface, volatile uint32_t* port, PinsMask pMask);
	void setInterface(HD44780Display::Interface iface, uint8_t i2cDevAddress, void (*i2cf)(uint8_t, uint16_t, uint8_t, uint8_t*));
	void init(uint8_t countLines, uint8_t countSymbols);
	void initByI2C(uint8_t countLines, uint8_t countSymbols);
	void setCursor(uint8_t row, uint8_t col);
	void print(uint8_t row,char *text);
	void refresh();
	char *getBuffPtr(){return reinterpret_cast<char*>(buffer);}
	void createCustomCharacter (unsigned char *Pattern, const char Location);

};

/*
void initHD44780GPIOMode4()
{
	//A12 - RS, A11 - E, A4 - DB4, A5- DB5

	 RCC->IOPENR |= (1 << 0); // enable Port A

	GPIOA->MODER &= ~0x0280aa00;//reset MODE11[1] & MODE12[1] MODE4[1] MODE5[1] MODE6[1] MODE7[1]
	GPIOA->MODER |= 0x01405500; //set MODE11[0] & MODE12[0] MODE4[0] MODE5[0] MODE6[0] MODE7[0]

	//GPIOA->OTYPER |= 0x000018f0; //opendrain if use pull up to 5v
	//GPIOA->OSPEEDR |= 0x02800000; //maxspeed
}

void initHD44780GPIOMode8()
{

	//A12 - RS, A11 - E, A4 - DB4, A5- DB5

	 RCC->IOPENR |= (1 << 0); // enable Port A

	GPIOA->MODER &= ~0x0280aaaa;//reset MODE11[1] & MODE12[1] MODE4[1] MODE5[1] MODE6[1] MODE7[1]
	GPIOA->MODER |= 0x01405555; //set MODE11[0] & MODE12[0] MODE4[0] MODE5[0] MODE6[0] MODE7[0]

	//	GPIOA->OTYPER |= 0x000018f0; //opendrain if use pull up to 5v
	//	GPIOA->OSPEEDR |= 0x02800000; //maxspeed

}

void lcdEnUp(void)
{
	GPIOA->BSRR |= 0x00000800;//A11
}
void lcdEnDwn()
{
	GPIOA->BSRR |= 0x08000000; //A11
}

//RS 1 - data, 0 -command
void lcdDataMode(bool isDt)
{
	if(isDt)GPIOA->BSRR|= 0x00001000; else GPIOA->BSRR |= 0x10000000;
}

void sendDataHD44780GPIO8(uint8_t byte, bool isData)
{
	GPIOA->ODR &= ~0x000000ff;
	lcdDataMode(isData);

	lcdEnUp();
	GPIOA->ODR |= byte;
	delay_ms(1);
	lcdEnDwn();
	//delay_ms(1);
}

void sendDataHD44780GPIO4Half(uint8_t byte, bool isData)
{
	GPIOA->ODR &= ~0x000000f0;
	lcdDataMode(isData);

	lcdEnUp();
	GPIOA->ODR |= (byte&0x0f)<<4;
	delay(5048);
	lcdEnDwn();
	delay(1000);
}

void sendDataHD44780GPIO4(uint8_t byte, bool isData)
{

	GPIOA->ODR &= ~0x000000f0;
	lcdDataMode(isData);

	lcdEnUp();
	GPIOA->ODR |= (byte&0xf0);
	delay(5048);
	lcdEnDwn();
	delay(1000);

	GPIOA->ODR &= ~0x000000f0;
	lcdEnUp();
	GPIOA->ODR |= (byte&0x0f)<<4;
	delay(5048);
	lcdEnDwn();
	delay(1000);

}
void initHD44780()
{
	sendDataHD44780GPIO8(0x38,0);delay_ms(20);
	sendDataHD44780GPIO8(0x01,0);delay_ms(1);
	sendDataHD44780GPIO8(0x06,0);delay(1);
	sendDataHD44780GPIO8(0x0f,0);delay(1);
	sendDataHD44780GPIO8(0x01,0);delay(1);
	sendDataHD44780GPIO8(0x14,0);delay(1);




}

//---Установка позиции курсора---//
void cursor(char row, char col)
{
   char address;
   if (row == 0)
   address = 0;
   else
   address = 0x40;
   address |= col;
  // sendDataHD44780GPIO4Half(0x80 | address, 0);
   sendDataHD44780GPIO8(0x80 | address, 0);
}

void print(char row,char *text)
{
    char *c;
		cursor(row,0);
    c = text;
    while ((c != 0) && (*c != 0))
    {
    	sendDataHD44780GPIO8(*c, 1);
        c++;
    }
}
*/
#endif /* HD44780DISPLAY_H_ */
