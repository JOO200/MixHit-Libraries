#include "cOLED.h"

#if 0
cOLED::cOLED()
{
	u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
	u8g2_esp32_hal.sda = 21;		// TODO Configurierbar halten
	u8g2_esp32_hal.scl = 22;
	u8g2_esp32_hal_init(u8g2_esp32_hal);

	u8x8_SetupDefaults(&u8g2_esp32_hal);

	u8g2_t u8g2;
	u8x8_d_ssd1306_128x32_univision()
	u8g2_Setup_ssd1306_i2c_128x32_univision_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_i2c_byte_cb,
			u8g2_esp32_gpio_and_delay_cb);
	mdisplay.begin(SSD1306_SWITCHCAPVCC, I2C_OLEDaddress);
	mdisplay.display();
	delay(2000);
	mdisplay.clearDisplay();
	mdisplay.setTextSize(1);
	mdisplay.setTextColor(INVERSE);

	//OLED GEHT senden
	mdisplay.clearDisplay();
	mdisplay.setCursor(0, 0);
	mdisplay.println("Booting...");
	mdisplay.display();
	mNewValue = false;
}
void cOLED::DisplayLines()
{
	MyMutex_mLinesToShow_lock(); // Bereich fuer andere Threads sperren
	if (mNewValue) // Pruefen ob neue Werte vorhanden sind
	{
		for (int i = 0; i < OLED_MAX_ZEILEN; i++) // Alle Werte in das "Save" Array uebernehmen um den Bereich moeglichst schnell wieder freizugeben.
		{
			mLinesToShow_Save[i] = mLinesToShow[i];
		}
		mNewValue = false; // Flag fuer neue Werte zuruecksetzen.
		MyMutex_mLinesToShow_unlock(); // Bereich wieder freigeben

		MyMutex_I2C_lock(); // I2C Bus sperren (der IO-Expander verwendet ebenfalls I2C).
		mdisplay.clearDisplay(); // Display leeren.
		mdisplay.setCursor(0, 0); // Cursor an die erste Stelle setzen.
		for (int i = 0; i < OLED_MAX_ZEILEN; i++)
		{
			mdisplay.println(mLinesToShow_Save[i]); // Zeilen auf das Display schreiben
		}
		mdisplay.display(); // Werte anzeigen.
		MyMutex_I2C_unlock(); // I2C freigeben
	}
	else
	{
		MyMutex_mLinesToShow_unlock(); // Bereich freigeben.
	}
}
bool cOLED::ChangeLine(String pText, int pIndex)
{
	MyMutex_mLinesToShow_lock(); // Bereich fuer andere Threads sperren
	if (pIndex < OLED_MAX_ZEILEN)
	{
		if (pText.length() <= OLED_MAX_SPALTEN) // Pruefen ob der Inhalt des neuen Textes in eine Zeile des Displays passt.
		{ // Passt in eine Zeile
			if (mLinesToShow[pIndex] != pText) // Pruefen ob der neue Text dem alten entspricht
			{ // Entspricht nicht dem alten
				mNewValue = true; // Flag fuer neue Werte setzen.
			}
			mLinesToShow[pIndex] = pText; // Text in die entspraechende Zeile schreiben.
		}
		else
		{ // passt nicht in eine Zeile
			String lText = pText.substring(0, OLED_MAX_SPALTEN - 1); // Abschneiden des neuen Textes
			if (mLinesToShow[pIndex] != lText) // Pruefen ob der neue Text dem alten entspricht
			{ // Entspricht nicht dem alten
				mNewValue = true; // Flag fuer neue Werte setzen.
			}
			mLinesToShow[pIndex] = lText; // Text in die entspraechende Zeile schreiben.
		}
		MyMutex_mLinesToShow_unlock(); // Bereich wieder freigeben
		return true;
	}
	else
	{
		MyMutex_mLinesToShow_unlock(); // Bereich wieder freigeben
		return false;
	}
}
void cOLED::PrintFirstLine(String pString)
{
	ChangeLine(pString, 0);
}

#endif
