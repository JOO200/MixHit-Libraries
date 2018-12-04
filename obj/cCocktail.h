#ifndef _CCOCKTAIL_H_
#define _CCOCKTAIL_H_

#include "cIngredient.h"
#include <string>
#include <map>
#include "RFID.h"

class cCocktail
{
public:
	cCocktail();
	cCocktail(std::string pCocktailName, int pFuel);
	std::string getCocktailName();						// Gibt den Namen des Cocktails aus.
	int getNumberOfIngredients();					// Gibt die Anzahl an verwendeten Zutaten aus.
//	cIngredient getIngredient(int pIndex);			// Gibt die Zutat mit dem entsprechenden Index aus.
	void addIngredient(int ingIndex, int mPercent);			// Gibt die Zutat mit dem entsprechenden Index aus.
	std::map<int, int> getIngredients();
	int getFuel();

	static bool fromJson(RfidData & cocktail, std::string json);
	std::string toJson();

private:
	// std::vector<cIngredient> mIngredients;				// Verwendete Zutaten.
	std::map<int, int> mIngredients;
	std::string mCocktailName;							// Name des Cocktails
	int mFuel;
};
#endif
