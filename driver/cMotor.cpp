#include "cMotor.h"

#define OUTPUT_LOW 0
#define OUTPUT_HIGH 1

cMotor::cMotor(gpio_num_t pPinNumberMotor, gpio_num_t pPinNumberRPM)
{
	mPinNumberMotor = pPinNumberMotor;
	mPinNumberRPM = pPinNumberRPM;
	gpio_set_direction(mPinNumberMotor, GPIO_MODE_OUTPUT);
	gpio_set_direction(mPinNumberRPM, GPIO_MODE_OUTPUT);
	
	MotorStop();
}

void cMotor::MotorStartR()
{
	gpio_set_level(mPinNumberRPM, OUTPUT_LOW);
	gpio_set_level(mPinNumberMotor, OUTPUT_HIGH);
}

void cMotor::MotorStartL()
{
	gpio_set_level(mPinNumberRPM, OUTPUT_HIGH);
	gpio_set_level(mPinNumberMotor, OUTPUT_HIGH);
}

void cMotor::MotorStop()
{
	gpio_set_level(mPinNumberRPM, OUTPUT_LOW);
	gpio_set_level(mPinNumberMotor, OUTPUT_LOW);
}
