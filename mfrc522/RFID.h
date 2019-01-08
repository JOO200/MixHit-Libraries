#ifndef _RFID_H_
#define _RFID_H_

//#include "../mixer/Configuration.h"
//#include "I2C.h"
#include <MFRC522I2C.h>
#include <stdint.h>

#define THRESHOLD_BIG_SMALL_COCKTAIL 200		// Threshold for cocktail size: over -> big cocktail, under -> small cocktail;

struct RfidData
{
	uint32_t  Bestellnummer;		
	uint16_t  CocktailNr;
	uint8_t  Status;					// use the upper 8 bits to determine the priority of the cocktail (0, 1, 2)
	uint16_t  mlProFlasche[8];
	uint8_t  Name[16];
	uint8_t  NameCocktail[32];
	uint8_t  LieferDatum[7];
};


class RFID: public MFRC522_I2C
{
public:

	//using MFRC522::MFRC522;
	RFID(uint8_t chipAddress, uint8_t resetPowerDownPin) : MFRC522_I2C(chipAddress,resetPowerDownPin) {};
	bool tagAvailable();			
	bool writeData(RfidData data, MIFARE_Key *stdKey);
	bool readData(RfidData &data, MIFARE_Key *stdKey);
	bool getDrinkStatus(uint8_t &status, MIFARE_Key *secretKey);
	bool setDrinkStatus(uint8_t status, MIFARE_Key *secretKey);
	bool changeSecretKey(MIFARE_Key *oldKey, MIFARE_Key *newKey);
	bool addDrinkToMixerQueue(RfidData &data);



private:
	uint8_t adr = 0;
	uint16_t intPin = 0;
};





#endif
