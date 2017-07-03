//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#include "Household.h"

Household::Household(int maxdays, double monthlyConsE, double solarAreaM2, double solarEfficiencyRatio, double powerKW, double priceInYen) //solar panel
{
	consumerUnit = Consumer(monthlyConsE);
	producerUnit = Producer(solarAreaM2,solarEfficiencyRatio,powerKW, priceInYen);
	
	Income = (double *) calloc(maxdays+1, sizeof(double));
	Expense = (double *) calloc(maxdays+1, sizeof(double));
	
	AccountBalance = (double **) calloc(maxdays+1, sizeof(double *));
	BuyEnergy = (double **) calloc(maxdays+1, sizeof(double *));
	SellEnergy = (double **) calloc(maxdays+1, sizeof(double *));
	
	for(unsigned int i = 0; i < maxdays+1; i++)
	{
		BuyEnergy[i] = (double *) calloc(25, sizeof(double)); //24 hours per day +1 (counting from zero)
		SellEnergy[i] = (double *) calloc(25, sizeof(double)); 
		AccountBalance[i] = (double *) calloc(25, sizeof(double)); 
	}

}

Household::Household(int maxdays, double monthlyConsE, int towerHeightInM, double powerKW, double priceInYen) //wind turbine
{
	consumerUnit = Consumer(monthlyConsE);
	producerUnit = Producer(towerHeightInM,powerKW,priceInYen);

	Income = (double *) calloc(maxdays+1, sizeof(double));
	Expense = (double *) calloc(maxdays+1, sizeof(double));
	
	AccountBalance = (double **) calloc(maxdays+1, sizeof(double *));
	BuyEnergy = (double **) calloc(maxdays+1, sizeof(double *));
	SellEnergy = (double **) calloc(maxdays+1, sizeof(double *));
	for(unsigned int i = 0; i < maxdays+1; i++)
	{
		BuyEnergy[i] = (double *) calloc(25, sizeof(double)); //24 hours per day +1 (counting from zero)
		SellEnergy[i] = (double *) calloc(25, sizeof(double)); 
		AccountBalance[i] = (double *) calloc(25, sizeof(double)); 
	}
}

Household::Household(int maxdays, double monthlyCons)
{
	if(monthlyCons<0)
	{
		cout <<"error! monthlyCons=" << monthlyCons <<endl;
		monthlyCons=0;
	}
	consumerUnit = Consumer(monthlyCons);

	double x = ((double)rand()) / RAND_MAX;

	if(x<0.166)
		producerUnit = ReturnSampleSolarPanel(3);
	else if(x<0.33)
		producerUnit = ReturnSampleSolarPanel(4);
	else if(x<0.5)
		producerUnit = ReturnSampleSolarPanel(5);
	else if(x<0.666)
		producerUnit = ReturnSampleSolarPanel(6);
	else if(x<0.83)
		producerUnit = ReturnSampleSolarPanel(7);
	else
		producerUnit = ReturnSampleSolarPanel(8);

	Income = (double *) calloc(maxdays+1, sizeof(double));
	Expense = (double *) calloc(maxdays+1, sizeof(double));
	
	AccountBalance = (double **) calloc(maxdays+1, sizeof(double *));
	BuyEnergy = (double **) calloc(maxdays+1, sizeof(double *));
	SellEnergy = (double **) calloc(maxdays+1, sizeof(double *));
	for(unsigned int i = 0; i < maxdays+1; i++)
	{
		BuyEnergy[i] = (double *) calloc(25, sizeof(double)); //24 hours per day +1 (counting from zero)
		SellEnergy[i] = (double *) calloc(25, sizeof(double)); 
		AccountBalance[i] = (double *) calloc(25, sizeof(double)); 
	}
}

Household::Household(int maxdays, double monthlyConsE, Producer producer )
{
	consumerUnit = Consumer(monthlyConsE);
	producerUnit = producer;

	/*double x = rand() / RAND_MAX;
	if(x<0.5)
		producerUnit = ReturnSampleWindTurbine(1+ ((int)(4*rand()/RAND_MAX)));
	else
		producerUnit = ReturnSampleSolarPanel(1+ ((int)(4*rand()/RAND_MAX)));*/

	Income = (double *) calloc(maxdays+1, sizeof(double));
	Expense = (double *) calloc(maxdays+1, sizeof(double));
	
	AccountBalance = (double **) calloc(maxdays+1, sizeof(double *));
	BuyEnergy = (double **) calloc(maxdays+1, sizeof(double *));
	SellEnergy = (double **) calloc(maxdays+1, sizeof(double *));
	for(unsigned int i = 0; i < maxdays+1; i++)
	{
		BuyEnergy[i] = (double *) calloc(25, sizeof(double)); //24 hours per day +1 (counting from zero)
		SellEnergy[i] = (double *) calloc(25, sizeof(double)); 
		AccountBalance[i] = (double *) calloc(25, sizeof(double)); 
	}
}

///<summary>
///based on kanden tarriff http://www.alldenka-hybrid.jp/power_company/06/
///</summary>
double Household::RequestToParticipate(int dayId, int hour, Hour_Data currentWeather, double solarRadiation )
{
	BuyEnergy[dayId][hour] = consumerUnit.current_demand(hour, DayToMonth(dayId));
	SellEnergy[dayId][hour] = producerUnit.EstiamateProduction(currentWeather,solarRadiation,dayId);
	double delta = BuyEnergy[dayId][hour] - SellEnergy[dayId][hour]; //if positive more consumption than production

	if(delta > 0)//cons>prod -> buy from kanden
	{
		//calculate how much energy has been consumed this month, if 0 -initial fee 320yen
		double sumThisMonth=0;
		int d=FirstDayOfCurrentMonth(dayId);

		for(;d<=dayId;d++)
			for(int h=1;h<24;h++)
			{
				if(d==dayId && h==hour)
					break;

				sumThisMonth+=BuyEnergy[d][h];
			}

		//if first day of month +320en
		if(sumThisMonth == 0)
		{
			AccountBalance[dayId][hour] = -320 - delta * 19.05; //initial fee 320‰~@{@19.05‰~@per kWh
			//Expense[dayId] += 320 + BuyEnergy[dayId][hour] * 19.05;
			Expense[dayId] += 320 + delta * 19.05;
		}

		if(sumThisMonth >0 && sumThisMonth <= 120)
		{
			AccountBalance[dayId][hour] = -delta  * 19.05; //consumption/expense to negative //(!)
			//Expense[dayId] += BuyEnergy[dayId][hour] * 19.05;
			Expense[dayId] += delta * 19.05;
		}

		if(sumThisMonth > 120 && sumThisMonth <= 300)
		{
			AccountBalance[dayId][hour] = -delta * 24.21; //24.21‰~@per kWh
			//Expense[dayId] += BuyEnergy[dayId][hour] * 24.21;
			Expense[dayId] += delta * 24.21;
		}

		if(sumThisMonth > 300)
		{
			AccountBalance[dayId][hour] = -delta * 25.55; //25.55‰~@per kWh
			//Expense[dayId] += BuyEnergy[dayId][hour] * 25.55;
			Expense[dayId] += delta * 25.55;
		}

		if(AccountBalance[dayId][hour] >0)
			printf("error 123\n");
	}
	
	if(delta < 0)//cons<prod -> sell to kanden
	{
		AccountBalance[dayId][hour] = -delta * 42; //minus to convert selling overproduction to positive number
		//Income[dayId] += SellEnergy[dayId][hour] * 42; 
		Income[dayId] += -delta * 42; 
	}

	return delta;
}

void Household::PrintConsumptionHistory(int dayId)
{
	cout << "[ ] manual request to print purchased energy amount[W] for day no. "<< dayId << endl << endl;
	
	for(int i = 1;i<=24; i++)
	{
		cout << BuyEnergy[dayId][i] << ",";
	}
	cout << endl<< endl << "total energy expense for this day: " << Expense[dayId] << "‰~"<< endl << endl;
}