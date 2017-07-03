//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#ifndef __HOUSEHODLCLASS
#define __HOUSEHODLCLASS

#include "Consumer.h"
#include "Producer.h"
#include "Forecaster.h"
#include "NormalDistribution.h"
#include "RESmodels.h"
#include "NormalDistribution.h"
#include "StdOps.h"

class Household
{
public:
	//<summary>
	//Income[day] - income in JPY day by day
	//</summary>
	double * Income;

	//<summary>
	//Expense[day] - expenses in JPY day by day
	//</summary>
	double * Expense;
	
	//<summary>
	//AccountBalance[day][hour] - relative value between expense and income in JPY hour by hour
	//</summary>
	double ** AccountBalance;

	//<summary>
	//Buy_energy[day][hour] - energy bought by household in Wh
	//</summary>
	double ** BuyEnergy;

	//<summary>
	//Sell_energy[day][hour] - energy sold by household in Wh
	//</summary>
	double ** SellEnergy;

	Consumer consumerUnit;
	Producer producerUnit;
	
	Household(int maxdays, double monthlyConsE);
	Household(int maxdays, double monthlyConsE, Producer producer );
	Household(int maxdays, double monthlyConsE, int towerHeightInM, double powerKW, double priceInYen); //wind turbine
	Household(int maxdays, double monthlyConsE, double solarAreaM2, double solarEfficiencyRatio, double powerKW, double priceInYen); //solar panel

	double RequestToParticipate(int dayId, int hour, Hour_Data currentWeather, double solarRadiation );
	void PrintConsumptionHistory(int dayId);
};

#endif