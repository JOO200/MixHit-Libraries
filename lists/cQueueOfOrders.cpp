#include "cQueueOfOrders.h"

cQueueOfOrders::cQueueOfOrders()
{
	mNumberOfOrdersInQueue = 0;
	mFirstIndex = 0;
	mLastIndex = 0;
	mMaxLenght = 0;
}
cQueueOfOrders::cQueueOfOrders(int pNumberOf)
{
	mNumberOfOrdersInQueue = 0;
	mFirstIndex = 0;
	mLastIndex = 0;
	mMaxLenght = pNumberOf;
	mQueue = new cOrder[mMaxLenght];
}
bool cQueueOfOrders::getOrder(cOrder *pOrder)
{
	if(mNumberOfOrdersInQueue > 0)
	{
		DettacheInterrupts(); // Verhindern, dass waehrendessen Interrupts stattfinden
		*pOrder = mQueue[mFirstIndex]; // Cocktail aus der Liste uebergeben
		mFirstIndex = (mFirstIndex + 1)%mMaxLenght; // mFirstIndex um eins erhoehen (Falls mFirstIndex >= mMaxLenght -> mFirstIndex = 0)
		mNumberOfOrdersInQueue--; // Anzahl an Bestellungen in der Liste um eins veringern.
		AttacheInterrupts(); // Interrupts wieder aktivieren
		return true;
	}
	else
	{
		return false;
	}
}
bool cQueueOfOrders::addOrder(cOrder pOrder)
{
	if(mNumberOfOrdersInQueue < mMaxLenght) // Pruefen ob noch platz in der Liste ist.
	{
		mQueue[mLastIndex] = pOrder; // Cocktail in die Liste schreiben
		mLastIndex = (mLastIndex + 1)%mMaxLenght; // mLastIndex um eins erhoehen (Falls mLastIndex >= mMaxLenght -> mLastIndex = 0)
		mNumberOfOrdersInQueue++; // Anzahl an Bestellungen in der Liste um eins erhoehen
		return true;
	}
	else
	{
		return false;
	}
}
bool cQueueOfOrders::addOrder_FirstPlace(cOrder pOrder)
{
	if (mNumberOfOrdersInQueue < mMaxLenght)
	{
		mFirstIndex = mFirstIndex - 1 < 0 ? mMaxLenght - 1 : mFirstIndex - 1; // mFirstIndex um eins veringern (Falls mFirstIndex < 0 -> mFirstIndex = mMaxLenght - 1) 
		mQueue[mFirstIndex] = pOrder; // Bestellung hinzufuegen
		mNumberOfOrdersInQueue++;
		return true;
	}
	else
	{
		return false;
	}
}
int cQueueOfOrders::getNumberOfOrders()
{
	return mNumberOfOrdersInQueue;
}
int cQueueOfOrders::getPlaceOfOrderNumber(int pOrderNumber)
{
	Serial.print("mFirstIndex: " + String(mFirstIndex) + "AnzahlInQueue " + String(getNumberOfOrders()));
	int lIndex;
	for (int i = mFirstIndex; i < mFirstIndex + getNumberOfOrders(); i++)
	{
		lIndex = i%mMaxLenght; // Da der mFirstIndex groeser als der mLastIndex sein kann und der Index in einen Sprung vom letzten Index auf 0 macht.
		Serial.println("lIndex: " + String(lIndex));
		if (mQueue[lIndex].getOrderNumber() == pOrderNumber)
		{ // Falls die ite Bestellung in der Liste die angegebene Bestellnummer besitzt.
			return i - mFirstIndex; // Hier wird der Platz der Bestellung in der Warteschlange zurueckgegeben.
		}
	}
	return -1;
}