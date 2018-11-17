#include "cGlasses.h"

cGlasses::cGlasses()
{

}
int cGlasses::checkGlasses(int pWeight) // Wenn mehr als eine Sorte Glaeser verwendet werden sollen, wird hier zum unterscheiden noch eine weitere Messgroese benoetigt.
{
	Serial.println("CheckGlasses" + String(pWeight));
	for (int i = 0; i<mGlasses.size(); i++)
	{
		if (pWeight <= WeightEmptyScale)
		{
			return ERROR_checkGlasses_KeinGlas;
		}

		int lcheckGlas = mGlasses[i].checkGlas(pWeight); // Prueft, ob das Gewicht zu dem Glas an dem angegebenen Index passt.
		if(lcheckGlas >= 1)
		{
			return i;
		}
	}
	return ERROR_checkGlasses_UnpassendeGlasses; // ggf. noch Statistik über aktuelle "Beladung" ausgeben...
}
cGlass cGlasses::getGlas(int pIndex)
{
	return mGlasses[pIndex];
}
bool cGlasses::addGlas(cGlass* pGlas)
{
	if (mGlasses.size() < MaxNumberOfDifferentGlasses)
	{
		mGlasses.push_back(*pGlas);
		return true;
	}
	else
	{
		return false;
	}
}
int cGlasses::getNumberOfGlasses()
{
	return mGlasses.size();
}
int cGlasses::getBigAmount()
{
	return mBigAmount;
}
int cGlasses::getSmallAmount()
{
	return mSmallAmount;
}
void cGlasses::setBigAmount(int pBigAmount)
{
	mBigAmount = pBigAmount;
}
void cGlasses::setSmallAmount(int pSmallAmount)
{
	mSmallAmount = pSmallAmount;
}