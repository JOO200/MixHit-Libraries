#include "cValveControl.h"
#include "SX1509.h"
#include "esp_log.h"

cValveControl::cValveControl()
{
	io = new SX1509();
	mFastMode = false;
}

void cValveControl::init(int PinSX1509Valve[MAX_NUMBER_RESERVOIR], uint8_t addr)
{
	io->init();
	for (int i = 0; i < MAX_NUMBER_RESERVOIR; i++)
	{
		mValveStates[i] = false;
		mValvePinNumbers[i] = PinSX1509Valve[i];
		io->pinMode(mValvePinNumbers[i], SX1509_OUTPUT);
		io->digitalWrite(mValvePinNumbers[i], 0);
	}
	mFastMode = true; // Damit mehre Ventile gleichzeitig geoeffnet werden duerfen.
}

void cValveControl::setFastMode(bool pMode)
{
	mFastMode = pMode;
}
void cValveControl::setValveState(int pValveIndex, bool pState)
{
//	MyMutex_I2C_lock(); // I2C fuer andere Threads sperren (da das OLED ebenfalls I2C verwendet).
	io->digitalWrite(mValvePinNumbers[pValveIndex], pState ? 1 : 0); // Ventil-Pin setzen / ruecksetzen.
//	MyMutex_I2C_unlock(); // I2C freigeben
	mValveStates[pValveIndex] = pState; // Ventilstatus intern speichern.

}
void cValveControl::setValveState(int pValveIndices[], long pTime[], int pNumberOfIngredients)
{
	ESP_LOGI("Valve", "Setting %d Valves.", pNumberOfIngredients);
	int lNumberOfIngredientsDone = 0; // Anzahl an bereits erledigten Zutaten.
	int lNumberOfOpenedValves = 0; // Anzahl an gleichzeitig offenen Ventielen
	int lMaxlNumberOfOpenedValves = mFastMode ? MAX_OPENED_VALVES : 1; // Festlegen wieviele Ventiele maximal gleichzeitig offen sein duerfen
	int lIndex = 0; // Aktueller angefragter Index.
	int* lIngredientsDone = new int[MAX_NUMBER_RESERVOIR]; // Array in dem Informationen bezueglich dem Vortschritt der Zutat hinterlegt ist. (0 = Noch nicht begonnen, 1 = gerade geoeffnet, 2 = fertig)
	unsigned long* StartTimes = new unsigned long[MAX_NUMBER_RESERVOIR]; // Speichert die Zeiten, an denen die jeweiligen Ventiele geoeffnet wurden (damit man weiss, wann das Ventil wieder geschlossen werden muss).
	for (int i = 0; i < pNumberOfIngredients; i++)
	{
		lIngredientsDone[i] = 0; // Fortschritt aller Ventile auf 0 setzen.
		StartTimes[i] = 0; // Startzeiten auf 0 setzen
		if (pTime[i] < 0) // Pruefen ob faeleschlicherweise eine negative Zeit uebergeben wurde
		{ // Ist kleiner als 0
			pTime[i] = 0; // Zeit auf 0 setzen
		}

	}
	unsigned long LastTimeVentilOpened = 0; // Gibt an, zu welchem Zeitpunkt zuletzt ein Ventil geoeffnet wurde (damit die Ventile nicht zu schnell hintereinander oeffnen und keine zu hohen Stromspitzen entstehen).
	while (lNumberOfIngredientsDone < pNumberOfIngredients) // Solange bis alle benoetigen Zutaten erledigt sind.
	{/*
		if (!(CheckNormalMode() || CheckInitMode())) // Pruefen ob sich die Maschiene in einem falschen Zustand befindet.
		{
			// Bei einem falschen Zustand werden alle Ventiele geschlossen und die Funktion verlassen.
			for (int i = 0; i < pNumberOfIngredients; i++)
			{
				setValveState(i, false);
			}
			delay(1000);
			return; 
		}*/ // TODO: Task nutzen, dann kann der Mixer den Task beenden.
		if (lIngredientsDone[lIndex] == 0 && lNumberOfOpenedValves < lMaxlNumberOfOpenedValves) 
		{ // Falls die Zutat noch nicht begonnen wurde und die Maximale anzahl an gleichzeitig offenen Ventielen noch nicht erreicht wurde.
			if ((esp_timer_get_time() / 1000) - LastTimeVentilOpened > MIN_TIME_VENTILE_OPEN) // Pruefen ob zwischen dem letztn Oeffnen und der jetzigen anfrage die minimale Zeitdifferenz vergangen ist. Damit die Stromausnahme nicht auf einmal zu groß wird.
			{
				setValveState(pValveIndices[lIndex], true); // Ventil oeffnen
				StartTimes[lIndex] = (esp_timer_get_time() / 1000); // Oeffnungszeit des Ventils merken
				LastTimeVentilOpened = StartTimes[lIndex]; // Letzte Oeffnungszeit eines Ventiles merken.
				lIngredientsDone[lIndex] = 1; // Zustand der Zutat auf 1 setztn (gerade geoeffnet)
				lNumberOfOpenedValves++; // Anzahl an aktuell geoeffneten Ventielen um eins erhoehen.
				
				ESP_LOGI("Valve", "[%d] Start - Soll Zeit: %lu", lIndex, pTime[lIndex]);
			}
		}

		if (lIngredientsDone[lIndex] == 1 && ((esp_timer_get_time() / 1000) - StartTimes[lIndex]) >= pTime[lIndex]) // Falls das Ventil geoeffnet ist und die benoetige Oeffnungszeit erreicht wurde
		{
			setValveState(pValveIndices[lIndex], false); // Ventil schliessen
			lIngredientsDone[lIndex] = 2; // Zustand auf 2 setzrn (Zutat erledigt)
			lNumberOfIngredientsDone++; // Anzahl an erledigten Zutaten um eins erhoehen.
			lNumberOfOpenedValves--; // Anzahl an derzeit offenen Ventielen um eins veringern.

			ESP_LOGI("Valve", "[%d] Ende - Zeit_Differenz: %lu", lIndex,
					(long unsigned int)(pTime[lIndex] - ((esp_timer_get_time() / 1000) - StartTimes[lIndex] - 1)));
		}
		vTaskDelay(10);
		lIndex = (lIndex + 1) % pNumberOfIngredients; // lIndex um eins erhoehen (Falls lIndex >= pNumberOfIngredients --> lIndex = 0)
	}
}
