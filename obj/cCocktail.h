#ifndef _CCOCKTAIL_H_
#define _CCOCKTAIL_H_

#include "cIngredient.h"
#include <string>
#include <vector>

class cCocktail
{
public:
	cCocktail(std::string pCocktailName, std::vector<cIngredient> pIngredients, int pFuel);
	std::string getCocktailName();						// Gibt den Namen des Cocktails aus.
	int getNumberOfIngredients();					// Gibt die Anzahl an verwendeten Zutaten aus.
	cIngredient getIngredient(int pIndex);			// Gibt die Zutat mit dem entsprechenden Index aus.

	static void fromJson(std::string json);
	std::string toJson();

private:
	std::vector<cIngredient> mIngredients;				// Verwendete Zutaten.
	std::string mCocktailName;							// Name des Cocktails
	int mFuel;
};
#endif
