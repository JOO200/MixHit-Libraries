#include "cCocktail.h"
#include "cJSON.h"

cCocktail::cCocktail(std::string pCocktailName, std::vector<cIngredient> pIngredients, int pFuel)
{
	mCocktailName = pCocktailName;
	mFuel = pFuel;
	mIngredients = pIngredients;
}

std::string cCocktail::getCocktailName()
{
	return mCocktailName;
}
int cCocktail::getNumberOfIngredients()
{
	return mIngredients.size();
}
cIngredient cCocktail::getIngredient(int pIndex)
{
	return mIngredients[pIndex];
}

std::string cCocktail::toJson() {
	return "";
}

void cCocktail::fromJson(std::string json) {
	cJSON *root = cJSON_Parse(json.c_str());
	cJSON_Print(root);
	/*
	cJSON *child = root->child;
	std::string name = cJSON_GetObjectItem(child, "Name")->string;
	int volume = cJSON_GetObjectItem(child, "Volume")->valueint;
	cJSON *ingArray = cJSON_GetObjectItem(child, "Inhaltsstoffe");
	std::vector<cIngredient> ingredients;

	while(true) {
		std::string ingName = cJSON_GetObjectItem(ingArray, "Zutat")->string;
		int percent = cJSON_GetObjectItem(ingArray, "Anteil")->valueint;
		ingredients.push_back(cIngredient(ingName, percent));

		if(ingArray->next == NULL) break;
		else ingArray = ingArray->next;
	}

	return cCocktail(name, ingredients, volume);*/
}
