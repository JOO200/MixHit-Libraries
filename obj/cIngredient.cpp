#include "cIngredient.h"

cIngredient::cIngredient(std::string pName, int pPercent)
{
	mName = pName;
	mPercent = pPercent;
}

std::string cIngredient::getName()
{
	return mName;
}

int cIngredient::getPercent()
{
	return mPercent;
}
