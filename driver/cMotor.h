#ifndef _CMOTOR_H_
#define _CMOTOR_H_

#include "gpio.h"


class cMotor
{
public:
	cMotor();											// Standartkonstruktor mit default_Pinnummer
	cMotor(gpio_num_t pPinNumberMotor, gpio_num_t pPinNumberRPM);		// Konstruktor mit Pinnummer angabe
	void MotorStartR();									// Startet den Motor (konstante Drehzahl und konstante Drehrichtung)
	void MotorStartL();									// Startet den Motor (konstante Drehzahl und konstante Drehrichtung)
	void MotorStop();									// Stoppt den Motor.
private:
	gpio_num_t mPinNumberMotor;								// Pinnummer des Motors ???
	gpio_num_t mPinNumberRPM;									// Pinnummer zur auswahl der Drehrichtung???
};

#endif
