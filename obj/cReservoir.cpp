#include "cReservoir.h"
#include "esp_log.h"

static const char* LOG_TAG = "Reservoir";
/*
cReservoir::cReservoir()
{
	mNumberOfReservoir = 0;
	for (int i = 0; i<MaxNumberOfReservoir; i++)
	{
		mNames[i] = "";
		mm[i] = 0;
		mb[i] = 0;
		mSumServed[i] = 0;
	}
}
*/

SingleReservoir::SingleReservoir(int pId, std::string pName, double pm, double pb, int pSumServed)
{
	id = pId;
	mName = pName;
	mm = pm;
	mb = pb;
	mSumServed = pSumServed;
}

int SingleReservoir::getId()
{
	return id;
}

bool SingleReservoir::getInitState()
{
	ESP_LOGD(LOG_TAG, "[%d] m=%f, b=%f, InitOk=xx", id, mm, mb);
	return mm != 0 || mb != 0;
}

std::string SingleReservoir::getName()
{
	return mName;
}

void SingleReservoir::addToSum(int amount, bool reset) {
	if(reset) mSumServed = 0;
	mSumServed += amount;
}

int SingleReservoir::AmountToTime(double pml)
{
	double time = (double)pml * mm + mb;
	ESP_LOGD(LOG_TAG, "m=%f, b=%f, Time=%f", mm, mb, time);
	return time;
	/* Linearer Zusammenhang:
	Zeit (Einheit: ms) = Wunschmaenge (Einheit: ml) * Steigung (Einheit: ms / ml) + Offset (Einheit: ms);
	Wobei davon ausgegangen wird, dass ein Milliliter einem Gramm entsprincht.
	*/
}


cReservoir::cReservoir()
{

}

bool cReservoir::addReservoir(int pIndex, SingleReservoir* reservoir)
{
	if(pIndex >= MAX_NUMBER_RESERVOIR) return false;
	reservoirs[pIndex] = reservoir;
	return true;
}

std::string cReservoir::getReservoirName(int pIndex)
{
	if(pIndex >= MAX_NUMBER_RESERVOIR) return "";
	return reservoirs[pIndex]->getName();
}

int cReservoir::getReservoirIndex(std::string pName)
{
	for (uint8_t i = 0; i < MAX_NUMBER_RESERVOIR; i++) {
		if(reservoirs[i] == NULL) continue;
		ESP_LOGD("cReservoir", "Comparing Name %s against %s", reservoirs[i]->getName().c_str(), pName.c_str());
		if(pName.compare(reservoirs[i]->getName()) == 0) {
			return i;
		}
	}
	return -1;
}
