#include "WindPower.h"

//requires:
//windblade in meters
//wind speed
//1.88kg/m3

//The quantity 1.88 kg / m^3 appearing in the calculation arises 
//from a factor of pi x D / 2, in the original formula, where D is the density of air
//

//watt = kg x m^2 / s^3
//1 kWh = 3.6 x 10^6 J.

//source http://www.ehow.com/how_6729764_calculate-kwh-wind-turbine.html
/*
double CalculateWindPowerInKWHfromBladeLenght(double windSpeed, double bladeLenght)
{
	double density = 1.2 ; //using standard density of air at 68 F is 1.2 kg / m^3
	double Cp = 0.35; //Maximum power coefficient, ranging from 0.25 to 0.45, dimension less (theoretical maximum = 0.59)
	
	double PowerInJoulesPerSecond = Cp * pow(bladeLenght,2) * 3.141592 * density * pow(windSpeed,3) /2;
	double PowerInJoulesPerHour = PowerInJoulesPerSecond * 3600;
	double PowerInKWH = PowerInJoulesPerHour / (3.6 * pow(10.0,6));

	//double turbineSweptArea = 2 * 3.141592 * pow(bladeLenght,2);


	return PowerInKWH;
}


double CalculateWindPowerinKWHfromPower(double windSpeed,int PowerInKW)
{
	if (windSpeed < 3.5)
		return 0;

	return PowerInKW; // multiplied by 1 hour -> kWh
}

double CalculateWindPowerinKWHfromPowerCurve(double windSpeed, int PowerInKW)
{
	//windness coefficient : 60 meters up, at the top of the tower is much more windy
	double windSpeedAtTopOfTower=EstimateWindSpeedDependsOnTurbineTower(windSpeed,60); 
	
	if (windSpeedAtTopOfTower <2.5) //cut-in speed
		return 0;
	
	if (windSpeedAtTopOfTower >25) //cut-out speed
		return 0;
	
	if (windSpeedAtTopOfTower > 12.5)
		return PowerInKW; //multiplied by 1 hour ->kWh

	return (PowerInKW/2000) * (1.7366 * pow(windSpeedAtTopOfTower,3) - 13.926*pow(windSpeedAtTopOfTower,2) 
		+ 45.666*windSpeedAtTopOfTower - 40.839);
}

double EstimateWindSpeedDependsOnTurbineTower(double windSpeedAtGround, double turbineHeight)
{
	//explanation at the file euqtions.xlsx
	return (windSpeedAtGround / 2.7) * ( -0.0011 * pow(turbineHeight,2) + 0.131*turbineHeight + 2.4488);
}
*/