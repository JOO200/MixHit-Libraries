#include "cGlass.h"
#include "../cCocktailMixer.h"

cGlass::cGlass(int pTare, int pTolerance)
{
	mTare = pTare;
	mTolerance = pTolerance;
}
int cGlass::checkGlas(int mWeight)
{
	if (mTare - mTolerance < mWeight && mTare + mTolerance > mWeight)
	{ // Glas ist leer
		return 1;
	}
	/*else if (mTare - mTolerance < mWeight && (mTare + mTolerance) + (gCocktailMixer.mGlasses.getSmallAmount() - 20) > mWeight)
	{ // Glas mit (vermutlich) Eiswuerfel. Das Gewicht muss kleiner sein, als das Gewicht eines leeren Glases mit einem kleinen Cocktail (abzueglich einer Tolleranz)
	  // D.h., das Eis darf maximal so viel wiegen, wie die Maenge eines kleinen Cocktails abzueglich 20g. 
		return 2;
	}*/
	else if (mTare + mTolerance < mWeight && mTare - mTolerance > mWeight)
	{ // Glas ist eventuell teilweise gefüllt
		return -2;
	}
	else if (mTare - mTolerance > mWeight)
	{ // Leichter als Minimalgewicht
		return -3;
	}
	else
	{ // Sonstiges...
		return -99;
	}	
}
int cGlass::getTare()
{
	return mTare;
}