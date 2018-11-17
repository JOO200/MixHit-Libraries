#ifndef _CZUTATEN_H_
#define _CZUTATEN_H_

#include <string>

class cIngredient
{
public:
	cIngredient(std::string pName, int pAmount);
	std::string getName();
	int getPercent();

private:
	std::string mName;
	int mPercent;			// Prozent (0..100)
};


#endif
