#ifndef _CCOCKTAILLIST_H_
#define _CCOCKTAILLIST_H_

#include "../obj/cCocktail.h"
#include "../cCocktailMixer.h"


class cCocktailList
{
public:
	cCocktailList();						// Standartkonstruktor
	bool addCocktail(cCocktail* pCocktail);	// Fuegt einen Cocktail (als Pointer) der Liste hinzu.
	cCocktail getCocktail(int pIndex);		// Gibt den Cocktail an dem angegebenen Index aus.
	int getAmountOfCocktailsInList();		// Gibt die Anzahl an Cocktails in dieser Liste aus.
private:
	vector<cCocktail> mCocktailList;		// Wird als Array an Pointer verwendet. Jeder Pointer in der Liste zeigt auf einen Cocktail.
};
extern cCocktailList gAlcoholicList;
extern cCocktailList gNonAlcoholicList;
#endif