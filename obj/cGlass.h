#ifndef _CCGLAS_H_
#define _CCGLAS_H_
#include "../Configuration.h"

class cGlass
{
public:
	cGlass(){};						// Standartkonstruktor
	cGlass(int pTare, int pTolerance);	// Konstruktor mit Informationen.
	int checkGlas(int mWeight);		// Prueft, ob dieses Glas zu dem angegebenen Gewicht passt.
	int getTare();					// Gibt das Leergewicht des Glases zurueck.
private:
	int mTare;						// Leergewicht des Glases.
	int mTolerance; 				// UG = mTare - mTolerance ; OG = mTare + mTolerance
};

#endif