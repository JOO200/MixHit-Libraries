#include "cServoMotor.h"
#include "driver/ledc.h"
#include "esp_log.h"

cServoMotor::cServoMotor(int pPinNummber)
{
	mPinNumber = pPinNummber;
	openMs = 1000;
	closedMs = 1500;
	ledc_timer_config_t timer_conf;
	timer_conf.bit_num    = LEDC_TIMER_15_BIT;
	timer_conf.freq_hz    = 50;
	timer_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
	timer_conf.timer_num  = LEDC_TIMER_0;
	ledc_timer_config(&timer_conf);

	int bitSize         = 15;
	int minValue        = 900;  // micro seconds (uS)
	int maxValue        = 2100; // micro seconds (uS)
	int sweepDuration 	= 1500; // milliseconds (ms)
	int duty = (1<<bitSize) * closedMs / 20000;

	ledc_channel_config_t ledc_conf;
	ledc_conf.channel    = LEDC_CHANNEL_0;
	ledc_conf.duty       = duty;
	ledc_conf.gpio_num   = 17;
	ledc_conf.intr_type  = LEDC_INTR_DISABLE;
	ledc_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
	ledc_conf.timer_sel  = LEDC_TIMER_0;
	ledc_conf.hpoint	 = 0xffff;
	ledc_channel_config(&ledc_conf);

	ESP_LOGI("debug", "duty %d", duty);
	mCurrentConfig = ledc_conf;
	ledc_channel_config(&mCurrentConfig);
	ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty);
	ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
}

void cServoMotor::changeDuty(int us)
{
	int bitSize         = 15;
	int duty = (1<<bitSize) * us / 20000;
	mCurrentConfig.duty = duty;
	ledc_set_duty_and_update(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty, mCurrentConfig.hpoint);
}

void cServoMotor::goToPosition_Close()
{
	changeDuty(closedMs);
	//mServo.write(49); // Eigentlich ist hier die angabe in °. Allerdings hat der verwendete Servo eine andere Uebersetzung. 10° im Programmcode entsprechen tatsaechlich nur wenige Grad (<10°).
}
void cServoMotor::goToPosition_Open()
{
	changeDuty(openMs);
	//mServo.write(45); // Eigentlich ist hier die angabe in °. Allerdings hat der verwendete Servo eine andere Uebersetzung. 10° im Programmcode entsprechen tatsaechlich nur wenige Grad (<10°).
}
