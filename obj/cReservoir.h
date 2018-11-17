#ifndef _CVORRATSBEHAELTER_H_
#define _CVORRATSBEHAELTER_H_

#include <string>

#define MAX_NUMBER_RESERVOIR 8

class cReservoir
{
public:
	cReservoir(std::string pNames[MAX_NUMBER_RESERVOIR], int pNumberOfUsedReservoir);	// Konstruktor mit Namen
	bool addReservoir(std::string pName);							// Fuegt ein Vorratsbehaelter hinzu (ohne Parameter zur Berechung von Maeche in Zeit).
	bool addReservoir(std::string pName, double pm, double pb);		// Fuegt ein Vorratsbehaelter hinzu (mit Parameter).
	void setParams(double pm[], double pb[]);					// Setzt alle Parameter fuer die umrechnung von Maenge in Zeit.
	std::string getReservoirName(int pIndex);						// Gibt den Namen des Vorrates an der gegebenen Stelle zurueck.
	int getReservoirIndex(std::string pName);						// Gibt den Index des Vorrates mit dem angegebenen Namen zurueck.
	int getNumberOfReservoir();									// Gibt die Anzahl an Verwendeten Vorratsgehaelter zurueck.
	int AmountToTime(int pIndex, int pml);						// Gibt die Oeffungszeit des Ventiles fuer die angegebene Maenge zurueck.
	void setMB(int pIndex, double pm, double pb);				// Set die Parameter fur die Umrechnung von Maenge in Zeit fuer den angegebenen Vorratsbehaelter.
	bool getInitState(int pIndex);								// Gibt an, ob der Vorratsbehaelter Initialisiert ist oder nicht.
	bool getInitStateAll();										// Gibt an, ob jeder Vorratsbehaelter initialisiert ist.
	void addToSum(int pIndex, int pAmount);						// Fuegt eine Maenge zur gesamten ausgeschenkten Maenge eines Vorrates seit Programmstart hinzu (Angabe in ml).
	double getSum(int pIndex);									// Gibt die gesamte ausgeschenkte Maenge des angegebenen Vorrates seit Programmstart zurueck (Angabe in ml).
	double getM(int pIndex);									// Gibt die Steigung des Lienearen zusammenhangs zwischen Maenge und Zeit zurueck.
	double getB(int pIndex);									// Gibt den Offset des Lienearen zusammenhangs zwischen Maenge und Zeit zurueck.
private:
	std::string mNames[MAX_NUMBER_RESERVOIR];						// Namen der Vorratsbehaelter
	int mNumberOfReservoir;										// Anzahl an verwendeten Vorratsbehalter.
	//bool mInitOK[MaxNumberOfReservoir];							// Initialisierungszustaende der Vorratsbehaleter
	double mm[MAX_NUMBER_RESERVOIR];							// Steigung; Für die umrechnung von cl bzw. g in die Öffungszeig der Valve.
	double mb[MAX_NUMBER_RESERVOIR];							// Offset; Für die umrechnung von cl bzw. g in die Öffungszeig der Valve.
	int mSumServed[MAX_NUMBER_RESERVOIR];						// Gesamte ausgeschenkte Maenge des angegebenen Vorrates seit Programmstart zurueck (Angabe in ml).
};

#endif
