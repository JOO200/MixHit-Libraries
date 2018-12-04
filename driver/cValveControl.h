#ifndef _CVENTILSTEUERUNG_H_
#define _CVENTILSTEUERUNG_H_

#include "cReservoir.h"
#include "SX1509.h"

#define MAX_OPENED_VALVES 3
#define MIN_TIME_VENTILE_OPEN 100

class cValveControl
{
public:
	cValveControl();										// Standartkonstruktor
	void init(int PinSX1509Valve[MAX_NUMBER_RESERVOIR], uint8_t addr);
	void setFastMode(bool pMode);							// Setzt den Modus (eines / mehrere Vebtiele gleichzeitig offen).
	void setValveState(int pValveIndex, bool pState);		// Oeffnet / Schliesst das ngegebene Ventiel.
	void setValveState(int pValveIndices[], long pTime[], int pNumberOfIngredients);	// Offner / Schliesst die angegebenen Ventiele.
private:
	SX1509 * io;
	int mValvePinNumbers[MAX_NUMBER_RESERVOIR];				// Pinnummern der Ventiele
	bool mValveStates[MAX_NUMBER_RESERVOIR];				// Zustaende der Ventiele
	bool mFastMode;											// Modus (eines / mehrere Vebtiele gleichzeitig offen)
};

#endif
