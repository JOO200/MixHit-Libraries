#include "cOrder.h"

#ifndef FillSIZE
#define ORDER_FULL 2
#define ORDER_HALF 1
#endif

cOrder::cOrder()
{
	mOrderNumber = 0;
	mOrderedAmount = ORDER_FULL;
	mPrio = 0;
}
cOrder::cOrder(cCocktail pCocktail, int pOrderedAmount, int pPrio)
{
	mCocktail = pCocktail;
	mOrderNumber = -1; // Default auf Fehlermeldung. Die Bestellnummer wird spaeter gesetzt, sobald die Bestellung in der Liste hinugefuegt wird.
	mOrderedAmount = pOrderedAmount;
	mPrio = pPrio;
}
cCocktail cOrder::getCocktail()
{
	return mCocktail;
}
int cOrder::getOrderNumber()
{
	return mOrderNumber;
}
void cOrder::setOrderNumber(int pOrderNumber)
{
	mOrderNumber = pOrderNumber;
}
int cOrder::getOrderedAmount()
{
	return mOrderedAmount;
}
int cOrder::getPrio()
{
	return mPrio;
}
