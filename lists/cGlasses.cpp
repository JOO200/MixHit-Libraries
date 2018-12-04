#include "cGlasses.h"
#include "esp_log.h"


cGlasses::cGlasses()
{
	mSmallAmount = 0;
	mBigAmount = 0;
}

int cGlasses::checkGlasses(int pWeight) // Wenn mehr als eine Sorte Glaeser verwendet werden sollen, wird hier zum unterscheiden noch eine weitere Messgroese benoetigt.
{
	ESP_LOGI("Glasses", "Check Glasses %d", pWeight);
	for (int i = 0; i<mGlasses.size(); i++)
	{
		if (pWeight <= WEIGHT_EMPTY_SCALE)
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
	if (mGlasses.size() < MAX_DIFFERENT_GLASSES)
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
