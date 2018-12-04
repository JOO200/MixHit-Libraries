#include "RFID.h"
//#include "../MixHit/src/mixer/cCocktailMixer.h"		//include Queue of Orders class to wrap RFID data
//#include "../MixHit/src/mixer/Main_CocktailMixer.h"	//Quick and dirty bugfix for error "vector elements not found"
#include "string.h"
#include <string>
#include <cIngredient.h>

#include "esp_log.h"

/*RFID::RFID(uint8_t addr, uint8_t rstPin)
{
	MFRC522(addr, rstPin);
}*/

bool RFID::tagAvailable()
{
	//Unused
	return false;
}

/**
This function writes the RfidData struct to the RFID tag.
RFID tag needs to be detected first.
*/

bool RFID::writeData(RfidData data, MIFARE_Key *stdKey)
{
	StatusCode status;
	uint8_t Sector1Buffer[32];
	uint8_t Sector2Buffer[48];
	
	//Sort uint32 into 4 uint8 for transfer
	for (int i = 0; i < 4; i++) {
		Sector1Buffer[i] = (uint8_t)(data.Bestellnummer >> (8 * (3 - i))& 0x000000FF);
		}
	//Sort uint16 into 2 uint8 for transfer
	for (int i = 0; i < 2; i++) {
		Sector1Buffer[i+6] = (uint8_t)(data.CocktailNr >> (8 * (2 - i)) & 0x00FF);
	}
	//Transfer Date into buffer
	for(int ii = 0; ii < 8; ii++) {
		Sector1Buffer[ii + 9] = data.LieferDatum[ii];
	}
	//Transfer of ml array
	for(int iii = 0; iii < 16; iii=iii+2) {
		Sector1Buffer[iii + 16] = (uint8_t)((data.mlProFlasche[iii/2] >> 8) & 0x0FF);
		Sector1Buffer[iii + 17] = (uint8_t)(data.mlProFlasche[iii/2] & 0x00FF);
	}
	
	memcpy(&Sector2Buffer[0], &data.Name[0], 16);
	memcpy(&Sector2Buffer[16], &data.NameCocktail[0], 32);
	
	// Authenticate using key A
	status = (StatusCode) PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, 7, stdKey, &(uid));
	if (status != STATUS_OK) {
		ESP_LOGI("RFID", "Write Data Authenticate failed.");
		return false;
	}
	ESP_LOGI("RFID", "Write Data Authenticated.");
	for (int i = 0; i < 2; i++) {
		status = (StatusCode) MIFARE_Write(i+4, &Sector1Buffer[i*16], 16);
		if (status != STATUS_OK) {
			ESP_LOGI("RFID", "Write Data failed in Step %d.", i);
			return false;
		}
	}

	// Authenticate using key A
	status = (StatusCode) PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, 11, stdKey, &(uid));
	if (status != STATUS_OK) {
		ESP_LOGI("RFID", "Write Data Authenticate failed.");
		return false;
	}
	ESP_LOGI("RFID", "Write Data Authenticated.");
	for (int i = 0; i < 3; i++) {
		status = (StatusCode) MIFARE_Write(i+8, &Sector2Buffer[i*16], 16);
		if (status != STATUS_OK) {
			ESP_LOGI("RFID", "Write Data failed in Step %d.", i);
			return false;
		}
	}
	ESP_LOGI("RFID", "Finished with success.");
	return true;
}

/**
* This function reads data from the RFID tag and returns it as ref param.
* 
* 
*/

bool RFID::readData(RfidData & data, MIFARE_Key *stdKey)
{

	//temporary buffers for all data (data has checksums which we want to remove)
	uint8_t MiscBuffer[36];
	uint8_t NameBuffer[18];
	uint8_t CocktailNameBuffer[36];
	uint8_t size = 18; // var for the read command to check buffer size. Buffer is always large enougth! The two last bytes are a checksum

	//Get Data from Sector 0
	StatusCode status;
	status = (StatusCode) PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, 7, stdKey, &(uid)); //Authenticate at sector 0
	if (status != STATUS_OK)
		return false;
	status = (StatusCode) MIFARE_Read(4, &MiscBuffer[0], &size);   //Read sector 0
	if (status != STATUS_OK)
		return false;
	status = (StatusCode) MIFARE_Read(5, &MiscBuffer[18], &size);  //Read sector 1
	if (status != STATUS_OK)
		return false;
	//PCD_StopCrypto1(); //Stop encrytion for sector 0
	//Get Data from Sector 1
	status = (StatusCode) PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, 11, stdKey, &(uid)); //Authenticate at sector 1
	if (status != STATUS_OK)
		return false;
	status = (StatusCode) MIFARE_Read(8, &NameBuffer[0], &size);  //Read sector 4
	if (status != STATUS_OK)
		return false;
	status = (StatusCode) MIFARE_Read(9, &CocktailNameBuffer[0], &size); //Read sector 5
	if (status != STATUS_OK)
		return false;
	
	status = (StatusCode) MIFARE_Read(10, &CocktailNameBuffer[18], &size); //Read sector 6
	if (status != STATUS_OK)
		return false;


	// Sort bytes into the correct data types
	data.Bestellnummer = (MiscBuffer[0] << 24) | (MiscBuffer[1] << 16) | (MiscBuffer[2] << 8) | MiscBuffer[3];
	data.CocktailNr	   = (MiscBuffer[6] << 8)  | MiscBuffer[7];

	memcpy(&data.LieferDatum[0], &MiscBuffer[9], 8);

	for (int i = 0; i < 8; i++) {
		data.mlProFlasche[i] = (MiscBuffer[i * 2 + 18] << 8) | MiscBuffer[i * 2 + 19];
	}
	memcpy(&data.Name, &NameBuffer, 16);

	memcpy(&data.NameCocktail[0] , &CocktailNameBuffer[0], 16);
	memcpy(&data.NameCocktail[16], &CocktailNameBuffer[18], 16); // two steps to remove Checksum 
	
	return true;
}

bool RFID::getDrinkStatus(uint8_t &status, MIFARE_Key *secretKey)		{
	StatusCode auth_status;
	uint8_t buffer[18] = {0};
	uint8_t size = sizeof(buffer);
	//Get Data from Sector 2 This sector has a special key for access restriction! The key is hardcoded.
	auth_status = (StatusCode)PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, 15, secretKey, &(uid));
	if (auth_status != STATUS_OK)
	{
		ESP_LOGE("RFID", "Authenticate wrong.");
		return false;
	}
	auth_status = (StatusCode)MIFARE_Read(12, &buffer[0], &size); //Read the whole sector
	if (auth_status != STATUS_OK)
	{
		return false;
	}
	status = buffer[1]; //pass the status byte

	return true;
}


bool RFID::setDrinkStatus(uint8_t status, MIFARE_Key *secretKey)
{


	uint8_t temp[16];
	temp[1] = status;
	// Authenticate using key A
	status = (StatusCode) PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, 15, secretKey, &(uid));
	if (status != STATUS_OK) {
		return false;
	}
	status = (StatusCode) MIFARE_Write(12, &temp[0], 16);
	if (status != STATUS_OK) {
		return false;
	}

	return true;
}


bool RFID::changeSecretKey(MIFARE_Key *oldKey, MIFARE_Key *newKey) {

	ESP_LOGI("RFID", "Changing secret key");
	StatusCode auth_status;
	uint8_t buffer[18];
	uint8_t size = 16;
	memcpy(&buffer[0], &newKey->keyByte[0], 6);
	buffer[6] = 0xFF; // Access bits setup (need keyA for all functions (read/write)
	buffer[7] = 0x07;
	buffer[8] = 0x80;
	buffer[9] = 0x69;
	for (int i = 10; i < 16; i++) {
		buffer[i] = 0xFF;
	}

	//
	auth_status = (StatusCode)PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, 15, oldKey, &(uid));
	if (auth_status != STATUS_OK) {
		ESP_LOGI("RFID", "Failed PICC_CMD_MF_AUTH_KEY_A 1, StatusCode %d", auth_status);
		return false;
	}
	auth_status = (StatusCode)MIFARE_Write(15, &buffer[0], size);
	if (auth_status != STATUS_OK) {
		ESP_LOGI("RFID", "Failed MIFARE_Write 2, StatusCode %d", auth_status);
		return false;
	}
	size+=2;
	auth_status = (StatusCode)PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, 15, newKey, &(uid));
	if (auth_status != STATUS_OK) {
		ESP_LOGI("RFID", "Failed PICC_CMD_MF_AUTH_KEY_A 3, StatusCode %d", auth_status);
		return false;
	}
	auth_status = (StatusCode)MIFARE_Read(15, &buffer[0], &size);
	if (auth_status != STATUS_OK) {
		ESP_LOGI("RFID", "Failed MIFARE_Read 4, StatusCode %d", auth_status);
		return false;
	}
	return true;
}
