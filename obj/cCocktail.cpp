#include "cCocktail.h"
#include "cJSON.h"
#include "esp_log.h"
#include <stddef.h>
#include "string.h"

cCocktail::cCocktail()
{
	mCocktailName = "";
	mFuel = 0;
}

cCocktail::cCocktail(std::string pCocktailName, int pFuel)
{
	mCocktailName = pCocktailName;
	mFuel = pFuel;
}

std::string cCocktail::getCocktailName()
{
	return mCocktailName;
}
int cCocktail::getNumberOfIngredients()
{
	return mIngredients.size();
}
int cCocktail::getFuel()
{
	return mFuel;
}
/*
int cCocktail::getIngredient(int pIndex)
{
	return mIngredients[pIndex];
}*/

void cCocktail::addIngredient(int pIndex, int pPercent) {
	mIngredients.insert(std::pair<int,int>(pIndex, pPercent));
}

std::map<int, int> cCocktail::getIngredients()
{
	return mIngredients;
}

std::string cCocktail::toJson() {
	return "";
}
