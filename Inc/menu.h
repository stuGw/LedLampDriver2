#ifndef MENU_H
#define MENU_H
#include "buttons.h"
#include "encoder.h"
#include "lampdisplay.h"

typedef void (**funcptr_t)(uint32_t); // pointer to function with no args and void return
typedef void (*func_t)(uint32_t); // pointer to function with no args and void return

class ConfigureMenu {

	static constexpr uint32_t CONFIG_MODE_LIFETIME { 10 };
	uint32_t count { 0 };
	funcptr_t fptr; // variable of pointer to function
	uint32_t* maxVals { nullptr };
	uint32_t* values { nullptr };
	Encoder* enco { nullptr };
	volatile Button* butt { nullptr };
	bool isInConfigurationMode { false };
	uint32_t configurationTimeout { 0 };
	LampDisplay* disp{nullptr};


public:
	ConfigureMenu(uint8_t countValues, Encoder* encoder, volatile Button* button);
	virtual ~ConfigureMenu(){};

	bool setFunction(uint8_t index, func_t ptr, uint32_t maxValue, uint32_t currentValue);
	//Обработка пользовательского интерфейса ввода
	bool handleUI();
	bool configure(char bv, uint16_t ev, signed char sign);
	void switchMenu(char punkt, unsigned short int val);
	void setDebugDisplay(LampDisplay* display){ disp = display; }
};



#endif//MENU_H
