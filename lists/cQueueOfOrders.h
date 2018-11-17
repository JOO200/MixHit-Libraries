#ifndef _CWARTESCHLANGE_H_
#define _CWARTESCHLANGE_H_

#include "../obj/cCocktail.h"
#include "../Configuration.h"
#include "../obj/cOrder.h"

class cQueueOfOrders
{ // FiFo - First in, first out.
public:
	cQueueOfOrders();									// Standartkonstruktor
	cQueueOfOrders(int pMaxLenght);						// Konstruktor mit maximaler Anzahl an Eintraegen der Liste
	bool getOrder(cOrder *pOrder);						// Gibt die Bestellung am mFirstIndex aus und erhoeht den mFirstIndex um eins.
	bool addOrder(cOrder pOrder);						// Fuegt eine BEstellung am mEndIndex hinzu und erhoeht den mEndIndex um eins.
	bool addOrder_FirstPlace(cOrder pOrder);			// Ernidrigt den mFirstIndex um eins und fuegt dort eine Bestellung hinzu
	int getNumberOfOrders();							// Gibt die Anzahl an Bestellunen in der Liste zurueck.
	int getPlaceOfOrderNumber(int pOrderNumber);		// Gibt den Platz in der Warteschlange der Bestellung mit der angegebenen Bestellnummer zurueck.

private:
	cOrder* mQueue;										// Warteschlange (verkettete Liste).
	int mMaxLenght;										// Maximale anzahl an Eintraegen.
	int mNumberOfOrdersInQueue;							// Anzahl an Bestellungen in der Liste.
	int mFirstIndex;									// Index des aeltesten Eintrags.
	int mLastIndex;										// Index des naechsten freien Platzes in der Liste
};
#endif