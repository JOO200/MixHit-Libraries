#ifndef _CMAGNETSENSOR_H_
#define _CMAGNETSENSOR_H_

#include "gpio.h"


class cMagnetSensor
{
public:
	cMagnetSensor(gpio_num_t pPinNumber = GPIO_NUM_22);		// Konstruktor mit Pinnangabe.
	int getSignal();										// Gibt das Signal des Magnetsensors aus.
private:
	gpio_num_t mPinNumber;									// PinNummer an dem Der Magnetsensor angeschlossen ist.
};

#endif // _CMAGNETSENSOR_H_
