#ifndef _CDREHTELLER_H_
#define _CDREHTELLER_H_

#include "cMagnetSensor.h"
#include "cMotor.h"
#include "cOLED.h"

#define NUMBER_OF_SLOTS 5

class cRotateTable
{
public:
	cRotateTable(cMagnetSensor * sensor, cMotor * motor);
	bool goToFirstPosition();							// Sucht die Position 0. (AN der Position 0 sind zwei Magnete hintereinander angebracht).
	bool goToPosition(int pPosition);					// Geht an die angegebene Position.
	bool goToNextPosition();							// Dreht den Drehteller an die naechste Position.
	int getPosition();									// Gibt die aktuelle Position des Drehtellers zurueck.
	//bool risingEdge(bool pSignal, bool* pOldSignal);	// Gibt true bei einem Wechsel von false nach true zurück.
	//bool fallingEdge(bool pSignal, bool* pOldSignal);	// Gibt true bei einem Wechsel von false nach true zurück.
private:
	bool getMagnetSensorSignal();						// Gibt das Signal des Magnetsensors aus.
	int mCurrentPosition;								// Aktuelle Position des Drehtellers.	
	unsigned long mTimeToNextSlot;						// Zeit in ms welche der Drehteller fuer eine ganze runde braeuchte (im Dauerlauf ohne Unterbrechung)

	cMotor * mMotor;										// Motor welcher den Drehteller bewegt.
	cMagnetSensor * mMagnetSensor;						// Magnetsensor welcher zur Positionserkennung verwendet wird.

};
bool risingEdge(bool pSignal, bool* pOldSignal);	// Gibt true bei einem Wechsel von false nach true zurück.
bool fallingEdge(bool pSignal, bool* pOldSignal);	// Gibt true bei einem Wechsel von false nach true zurück.

#endif
