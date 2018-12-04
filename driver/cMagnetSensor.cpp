#include "cMagnetSensor.h"
#include "driver/gpio.h"

cMagnetSensor::cMagnetSensor(gpio_num_t pPinNumber)
{
	mPinNumber = pPinNumber;
	gpio_set_direction(pPinNumber, GPIO_MODE_INPUT);
}
int cMagnetSensor::getSignal()
{
	return gpio_get_level(mPinNumber) != 0 ? 1 : 0;
	//return digitalRead(mPinNumber) != 0 ? 1 : 0; // Invertieren des Signals (1=Magnet vorhanden, 0=kein Magnet vorhanden)
}
