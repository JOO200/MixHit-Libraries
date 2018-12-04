#ifndef _CZUTATEN_H_
#define _CZUTATEN_H_

#include <string>

class cIngredient
{
public:
	cIngredient();
	cIngredient(int pIndex, int pAmount);
	int getIndex();
	int getPercent();
#if 0
	cIngredient(std::string pName, int pAmount);
	std::string getName();
	int getPercent();
#endif

private:
#if 0
	std::string mName;
#endif
	int mIndex;
	int mPercent;			// Prozent (0..100)
};


#endif
