#include "cIngredient.h"

cIngredient::cIngredient()
{
	mIndex = 0;
	mPercent = 0;
}

cIngredient::cIngredient(int pIndex, int pPercent)
{
	mIndex = pIndex;
	mPercent = pPercent;
}

#if 0
std::string cIngredient::getName()
{
	return mName;
}
#endif
int cIngredient::getIndex()
{
	return mIndex;
}

int cIngredient::getPercent()
{
	return mPercent;
}
