#ifndef _CSERVOMOTOR_H_
#define _CSERVOMOTOR_H_

#include "driver/ledc.h"

#define SERVO_FREQ 50


class cServoMotor
{
public:
	cServoMotor(int pPinNummber);
	void goToPosition_Close();
	void goToPosition_Open();
	void changeDuty(int ms);
private:
	int mPinNumber;
	ledc_channel_config_t mCurrentConfig;
	int openMs;
	int closedMs;
};

#endif
