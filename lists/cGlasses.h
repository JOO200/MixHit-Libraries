#ifndef _CGLAESER_H_
#define _CGLAESER_H_
#include "../Configuration.h"
#include "../../libs/MyString.h"
#include "../obj/cGlass.h"

#define ERROR_checkGlasses_KeinGlas -1
#define ERROR_checkGlasses_UnpassendeGlasses -2

class cGlasses
{
public:
	cGlasses();							// Standartkonstruktor
	int checkGlasses(int pWeight);		// Pruft welches Glas zu dem uebergebenen Gewicht passt.
	cGlass getGlas(int pIndex);			// Gibt das Glas an der angegebenen Stelle aus.
	bool addGlas(cGlass* pGlas);		// Fuegt ein Glas zu der Liste an bekanntn Glaesern hinzu.
	int getNumberOfGlasses();			// Gibt die Anzahl an bekannten Glaesern aus.
	int getBigAmount();
	int getSmallAmount();
	void setBigAmount(int pBigAmount);
	void setSmallAmount(int pSmallAmount);
private:
	int mMaxNumberOfGlasses;			// Maximale anzahl an erlaubten verschiedenen Glaesern
	int mBigAmount;						// Fuellmenge eines grossen Glases
	int mSmallAmount;					// Fuelmenge eines kleinen Glases
	vector<cGlass> mGlasses;			// Liste an bekannten Glaeser.
};

#endif