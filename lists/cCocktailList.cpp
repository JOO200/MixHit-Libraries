#include "cCocktailList.h"


cCocktailList gAlcoholicList;
cCocktailList gNonAlcoholicList;



cCocktailList::cCocktailList()
{

}

bool cCocktailList::addCocktail(cCocktail* pCocktail)
{
	// Pruefen ob der Cocktail mit den Zutaten und den vorhandenen Vorratsbehaelter moeglich ist.
	for (int i = 0; i < (*pCocktail).getNumberOfIngredients(); i++)
	{
		if (gCocktailMixer.mReservoir.getReservoirIndex((*pCocktail).getIngredient(i).getName()) < 0) // Pruefen ob die Zutat in den Vorraeten vorhanden ist.
		{ // Falls nicht, kann der COcktail nicht gemixt werden.
			return false;
		}
	}
	mCocktailList.push_back(*pCocktail); // Falls alle Zutaten vorhanden sind wird er der Liste hinzugefuegt.
	return true;
}
cCocktail cCocktailList::getCocktail(int pIndex)
{
	return mCocktailList[pIndex];
}
int cCocktailList::getAmountOfCocktailsInList()
{
	return mCocktailList.size();
}
