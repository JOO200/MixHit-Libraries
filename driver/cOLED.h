#ifndef _OLED_H_
#define _OLED_H_
#if 0

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <string>
#include <u8g2.h>

#include "sdkconfig.h"
#include "u8g2_esp32_hal.h"

#define OLED_MAX_LINES 8

class cOLED
{
public:
	cOLED();									// Standartkonstruktor
	bool ChangeLine(std::string pText, int pIndex);	// Aendert den Inhalt der angegebenen Zeile (zeigt diese aber noch nicht auf dem Display an).
	void DisplayLines();						// Zeigt die hinterlegten Zeilen auf dem Display an.
	void PrintFirstLine(std::string pString);		// Aendert den Inhalt der ersten Zeile (zeigt diese aber noch nicht auf dem Display an).
private:
	Adafruit_SSD1306 mdisplay;					// Display
	std::string mLinesToShow[OLED_MAX_LINES];		// Zeilen welche angezeigt werden sollen.
	std::string mLinesToShow_Save[OLED_MAX_LINES];	// Zeilen welche angezeigt werden (naehre Informationen in der .cpp).
	bool mNewValue;								// Gibt an, ob es neue Informatonen gibt welche angezeigt werden muessen.
};
#endif
#endif
