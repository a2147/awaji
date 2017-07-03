//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#include "Producer.h"

///<summary>
///Constructor function for solar panel
///</summary>
Producer::Producer(double solarAreaM2, double solarEfficiencyRatio, double powerKW,double priceInYen)
{
	price = priceInYen;
	producerType = solar_panel;
	solarEfficiency = solarEfficiencyRatio;
	solarArea = solarAreaM2;
	power = powerKW;

	//doesn't concern - reserved for wind turbine
	towerHeight = -1;
}

///<summary>
///Constructor function for wind turbine unit
///</summary>
Producer::Producer(int towerHeightInM, double powerKW,double priceInYen)
{
	price = priceInYen;
	producerType = wind_turbine;
	power = powerKW;
	towerHeight = towerHeightInM;

	//doesn't concern - reserved for solar panel
	solarEfficiency = -1;
	solarArea = -1;
}

///<summary>
///Estimate amount of energy that can be genrated by 
///specific wind turbine during one hour.
///</summary>
/// <param name="windSpeed">Speed of the wind downloaded from JMA</param>
///<returns>Genrated power during one hour (in kWh)</returns>
double Producer::CalculateWindTurbinePower(double windSpeed)
{
	//windness coefficient : 60 meters up, at the top of the tower is much more windy
	double windSpeedAtTopOfTower=EstimateWindSpeedDependsOnTurbineTower(windSpeed,towerHeight); 

	if (windSpeedAtTopOfTower <2.5) //cut-in speed
		return 0;
	
	if (windSpeedAtTopOfTower >30) //cut-out speed
		return 0;
	
	if (windSpeedAtTopOfTower > 12.5)
	{
		return power; //multiplied by 1 hour ->kWh
	}
	
	return (power/2000) * (1.7366 * pow(windSpeedAtTopOfTower,3) - 13.926*pow(windSpeedAtTopOfTower,2) 
		+ 45.666*windSpeedAtTopOfTower - 40.839);
	
}

double Producer::CalculateSolarPanelPower(Hour_Data currentWeather, double solarRadiation)
{
	return solarRadiation * solarArea * currentWeather.solarTime * solarEfficiency;
}
/*
double Producer::CalculateWindPower2(double windSpeed)//without estimating windness coefficient
{
	if (windSpeed <2.5) //cut-in speed
		return 0;
	
	if (windSpeed >30) //cut-out speed
		return 0;
	
	if (windSpeed > 12.5)
		return power; //multiplied by 1 hour ->kWh

	return (power/2000) * (1.7366 * pow(windSpeed,3) - 13.926*pow(windSpeed,2) 
		+ 45.666*windSpeed - 40.839);
}*/

///<summary>
///Estimate specific speed of the wind, because the higher tower wind turbine is, the faster wind blows.
///</summary>
///<seealso>./Modelling/Wind Tubine Model/equations.xlsx</seealso>
double Producer::EstimateWindSpeedDependsOnTurbineTower(double windSpeedAtGround, double turbineHeight)
{
	if(turbineHeight>30)
		return windSpeedAtGround * pow((turbineHeight/9.6),0.54);

	return windSpeedAtGround * pow((turbineHeight/9.6),0.34);
}


double Producer::EstiamateProduction(Hour_Data currentWeather, double solarRadiation, int dayOfYear)
{
	
	switch(producerType)
	{
	case kanden:
		return 0;

	case solar_panel:
		return CalculateSolarPanelPower(currentWeather, solarRadiation);

	case wind_farm: 
		return CalculateWindTurbinePower(currentWeather.windSpeed);
		
	case wind_turbine:
		return CalculateWindTurbinePower(currentWeather.windSpeed);
	}
	
	printf("error 125\n");
	return 0;

}

double Producer::CalculateSubsidy()
{
	if(producerType == solar_panel)
	{
		if(price > 475000)
			return 30000*power; //3–œ‰~ per kWh
		else
			return 35000*power;
	}

	return 0;
}