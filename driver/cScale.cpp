#include "cScale.h"
#include <stdio.h>

cScale::cScale()
{
	mTare = 96.57;
	mHX711Scale = NULL;
}

cScale::cScale(uint8_t pPinScaleData, uint8_t pPinScaleCLK)
{
	mHX711Scale = new HX711(pPinScaleData, pPinScaleCLK);
	//mHX711Scale.set_scale(1);
	mTare = 96.57;
}
double cScale::getWeight()
{
	// Folgende Werte wurden durch Messen ermittelt.
	//		Gewicht (G)		 digitaler Wert (DW)
	// 1:	0g			=	 123463
	// 2:	100g		=    252298
	// Linearer Zusammenhang: G = m * DW + b
	// m = (G1 - G2) / (DW1 - DW2) = (0 - 100) / (123463 - 252298) = 0,000776185631313688 = 1/1288;
	// b = G1 - m * DW1 = 0 - 0,000776185631313688 * 123463 = -95,83

	return (double)mHX711Scale->get_units(10) / 1288 - mTare; // Cast als Double, damit das Zwischenergebniss nicht gerundet wird.
}
double cScale::getWeight(int pPoints)
{
	// Folgende Werte wurden durch Messen ermittelt.
	//		Gewicht (G)		 digitaler Wert (DW)
	// 1:	0g			=	 123463
	// 2:	100g		=    252298
	// Linearer Zusammenhang: G = m * DW + b
	// m = (G1 - G2) / (DW1 - DW2) = (0 - 100) / (123463 - 252298) = 0,000776185631313688 = 1/1288;
	// b = G1 - m * DW1 = 0 - 0,000776185631313688 * 123463 = -95,83

	return (double)mHX711Scale->get_units(pPoints) / 1288 - mTare; // Cast als Double, damit das Zwischenergebniss nicht gerundet wird.
}
void cScale::Tare()
{
	mTare = 0;
	mTare = getWeight();
}

