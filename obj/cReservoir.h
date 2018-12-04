#ifndef _CVORRATSBEHAELTER_H_
#define _CVORRATSBEHAELTER_H_

#include <string>
#include <map>

#define MAX_NUMBER_RESERVOIR 8


class SingleReservoir
{
public:
	SingleReservoir();
	SingleReservoir(int id, std::string pName, double pm, double pb, int pSumServed = 0);

	bool getInitState();

	int AmountToTime(double pml);

	void addToSum(int amount, bool reset = false);

	int getId();
	std::string getName();
	double getSum();

	double mm;
	double mb;
private:
	int id;
	std::string mName;
	int mSumServed;
};

class cReservoir
{
public:
	cReservoir();												// Konstruktor mit Namen
	bool addReservoir(int index, SingleReservoir* reservoir);							// Fuegt ein Vorratsbehaelter hinzu (ohne Parameter zur Berechung von Maeche in Zeit).
	void setParams(double pm[], double pb[]);					// Setzt alle Parameter fuer die umrechnung von Maenge in Zeit.
	std::string getReservoirName(int pIndex);						// Gibt den Namen des Vorrates an der gegebenen Stelle zurueck.
	SingleReservoir* getReservoir(int index);
	int getReservoirIndex(std::string pName);						// Gibt den Index des Vorrates mit dem angegebenen Namen zurueck.

private:
	SingleReservoir * reservoirs[MAX_NUMBER_RESERVOIR];
	//std::map<int, SingleReservoir*> map;
};

#endif
