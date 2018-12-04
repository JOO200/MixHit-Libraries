
#ifndef _RFID_ERRORCODES_H_
#define _RFID_ERRORCODES_H_


enum RFIDerrorcode
{
	RFID_OK,				// Everything ok
	RFID_FCARDSERIAL,		// Failed to read current card serial
	RFID_FUIDIDENTICAL,		// UID matches last UID -> card read twice
	RFID_FDRINKSTATUS,		// Can't read drink status
	RFID_FWRONGSTATUS,		// Unexpected Status
	RFID_FDATAREAD,			// Failed to read RFID data
	RFID_FMIXERQUEUE,		// Unable to add order to mixer queue
	RFID_FWRITECARD			// Exception while trying to write the card

};

#endif
