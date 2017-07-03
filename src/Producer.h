//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#ifndef __PRODECERCLASS
#define __PRODECERCLASS

#include "Forecaster.h"
//#include "SolarPower.h"
#include "WindPower.h"

enum production_unit_type {
	solar_panel = 0,
	solar_farm = 1,
	wind_turbine = 2,
	wind_farm = 3,
	kanden = 4
};

class Producer
{

public:
	production_unit_type producerType;
	double price;

	//solar panel parameters
	double solarEfficiency;
	double solarArea; //in square meters
	
	//wind turbine parameters
	double power;
	int towerHeight;

	//constructors
	Producer(){} ; //random
	Producer(int towerHeightInM, double powerKW, double priceInYen); //wind turbine
	Producer(double solarAreaM2, double solarEfficiencyRatio, double powerKW,double priceInYen);//solar panel
	
	//main function of the Producer class
	double EstiamateProduction(Hour_Data currentWeather, double solarRadiation, int dayOfYear);
	
	//auxiliary functions
	double CalculateSolarPanelPower(Hour_Data currentWeather, double solarRadiation);
	double CalculateWindTurbinePower(double windSpeed);
	//double CalculateWindPower2(double windSpeed);
	double EstimateWindSpeedDependsOnTurbineTower(double windSpeedAtGround, double turbineHeight);

	double CalculateSubsidy();
};

#endif