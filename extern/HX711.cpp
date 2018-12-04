#include <HX711.h>
#include "gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


HX711::HX711(uint8_t dout, uint8_t pd_sck, uint8_t gain) {
	begin(dout, pd_sck, gain);
}

HX711::HX711() {
	PD_SCK = 0;
	DOUT = 0;
	GAIN = 0;
}

HX711::~HX711() {
}

void HX711::begin(uint8_t dout, uint8_t pd_sck, uint8_t gain) {
	PD_SCK = pd_sck;
	DOUT = dout;

	gpio_set_direction((gpio_num_t)PD_SCK, GPIO_MODE_OUTPUT);
	gpio_set_direction((gpio_num_t)DOUT, GPIO_MODE_INPUT);

	set_gain(gain);
}

bool HX711::is_ready() {
	return gpio_get_level((gpio_num_t)DOUT) == 0;
}

void HX711::set_gain(uint8_t gain) {
	switch (gain) {
		case 128:		// channel A, gain factor 128
			GAIN = 1;
			break;
		case 64:		// channel A, gain factor 64
			GAIN = 3;
			break;
		case 32:		// channel B, gain factor 32
			GAIN = 2;
			break;
	}

	gpio_set_level((gpio_num_t)PD_SCK, 0);
	read();
}

long HX711::read() {
	// wait for the chip to become ready
	while (!is_ready()) {
		// Will do nothing on ESP32 but prevent resets
		vTaskDelay(1);
	}

	unsigned long value = 0;
	uint8_t data[3] = { 0 };
	uint8_t filler = 0x00;

	// pulse the clock pin 24 times to read the data
	data[2] = shiftIn(HX711_MSB_FIRST);
	data[1] = shiftIn(HX711_MSB_FIRST);
	data[0] = shiftIn(HX711_MSB_FIRST);

	// set the channel and the gain factor for the next reading using the clock pin
	for (unsigned int i = 0; i < GAIN; i++) {
		gpio_set_level((gpio_num_t)PD_SCK, 1);
		#ifdef ESP_H
		vTaskDelay(20);
		#endif
		gpio_set_level((gpio_num_t)PD_SCK, 0);
		#ifdef ESP_H
		vTaskDelay(20);
		#endif
	}

	// Replicate the most significant bit to pad out a 32-bit signed integer
	if (data[2] & 0x80) {
		filler = 0xFF;
	} else {
		filler = 0x00;
	}

	// Construct a 32-bit signed integer
	value = ( static_cast<unsigned long>(filler) << 24
			| static_cast<unsigned long>(data[2]) << 16
			| static_cast<unsigned long>(data[1]) << 8
			| static_cast<unsigned long>(data[0]) );

	return static_cast<long>(value);
}

long HX711::read_average(uint8_t times) {
	long sum = 0;
	for (uint8_t i = 0; i < times; i++) {
		sum += read();
		vTaskDelay(1);
	}
	return sum / times;
}

double HX711::get_value(uint8_t times) {
	return read_average(times) - OFFSET;
}

float HX711::get_units(uint8_t times) {
	return get_value(times) / SCALE;
}

void HX711::tare(uint8_t times) {
	double sum = read_average(times);
	set_offset(sum);
}

void HX711::set_scale(float scale) {
	SCALE = scale;
}

float HX711::get_scale() {
	return SCALE;
}

void HX711::set_offset(long offset) {
	OFFSET = offset;
}

long HX711::get_offset() {
	return OFFSET;
}

void HX711::power_down() {
	gpio_set_level((gpio_num_t)PD_SCK, 0);
	gpio_set_level((gpio_num_t)PD_SCK, 1);
}

void HX711::power_up() {
	gpio_set_level((gpio_num_t)PD_SCK, 0);
}

uint8_t HX711::shiftIn(uint8_t bitOrder) {
	uint8_t value = 0;
	uint8_t i;
	for (i = 0; i < 8; ++i) {
		gpio_set_level((gpio_num_t)PD_SCK, 1);
		if (bitOrder == HX711_LSB_FIRST)
				value |= (gpio_get_level((gpio_num_t)DOUT) == 0) << i;
		else
			value |= (gpio_get_level((gpio_num_t)DOUT) == 0) << (7 - i);
		gpio_set_level((gpio_num_t)PD_SCK, 0);
	}
	return value;
}
