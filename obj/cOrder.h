#ifndef _CBESTELLUNG_H_
#define _CBESTELLUNG_H_

#include "cCocktail.h"

class cOrder
{
public:
	cOrder(cCocktail * pCocktail, int pOrderedAmount, int pPrio);	// Konstruktor mit Informationen
	cCocktail* getCocktail();	// Gibt den Cocktail zurueck.
	int getOrderNumber();		// Gibt die Bestellnummer zurück.
	void setOrderNumber(int pOrderNumber);		// Setzt die Bestellnummer.
	int getOrderedAmount();		// Gibt die Bestellte Menge zurueck (1 HalbVoll, 2 Voll).
	int getPrio();				// Gibt die Prioritaet der Bestellung aus.
private:
	cCocktail * mCocktail;	// Enthaelt die Informationen des Cocktails.
	int mOrderNumber;		// Bestellnummer - ggf. Bei einer Bestellung per Browser an den User zurueckgeben.
	int mOrderedAmount;		// estellte Menge zurueck (1 HalbVoll, 2 Voll).
	int mPrio;				// Prioritaet der Bestellung.
};

#endif
