//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#include "SimulationOfObjectivesForCitizens.h"

int SimulateInvestitionInSingleSolarPanel(int simDays,double monthlyConsE, Forecaster f1)
{
	cout << "\n[ ] Objectives 1A-1D: Simulation of single house with 24m^2 solar panel\n";

	//Household h1(simDays,monthlyConsE,24.0,0.1,-1.0,-1); //solar panel having 24m2 area and efficiency ratio 10%
	Household h1(simDays,monthlyConsE,34.16,0.1,5,622675); 
	//Producer(34.16,0.1,5.0,622675); 5kW
	double totalIncome = 0;
	double totalExpenses = 0;
	double monthlyEnergyProduction[13];
	double monthlyEnergyConsumption[13];
	double sumProdPerDay =0;
	double sumProdPerMonth =0;
	double sumProdPerYear =0;
	double sumConsPerDay =0;
	double fluxOfInsolation[13];
	double monthlyIncome[13];
	double monthlyExpense[13];
	double avgEnergyDaily[25];
	int monthlySaveDayCounter=1;

	Hour_Data currentWeather;
	
	FILE *fpobjective1A;
	FILE *fpobjective1B;
	FILE *fpobjective1C;
	FILE *fpobjective1D;

	for(int i=0;i<13;i++)
		monthlyIncome[i]=monthlyExpense[i]=fluxOfInsolation[i]=monthlyEnergyProduction[i]=monthlyEnergyConsumption[i]=0;
	
	for(int i=1;i<25;i++)
		avgEnergyDaily[i]=0;
	
	fpobjective1A=fopen("output\\Objective1A.txt","w");
	fpobjective1B=fopen("output\\Objective1B.txt","w");
	fpobjective1C=fopen("output\\Objective1C.txt","w");
	fpobjective1D=fopen("output\\Objective1D.txt","w");
	
	for (int dayId=0;dayId<=simDays;dayId++)
	{
		sumProdPerDay=0;
		sumConsPerDay=0;

		for(int hour = 1;hour<=24;hour++)
		{
			currentWeather = f1.RequestWeather(dayId,hour);

			h1.RequestToParticipate(dayId,hour,currentWeather,f1.RequestDailyFlux(dayId,hour));

			fluxOfInsolation[DayToMonth(dayId)]+=f1.RequestDailyFlux(dayId,hour)*currentWeather.solarTime;

			sumProdPerDay += h1.SellEnergy[dayId][hour];
			sumConsPerDay += h1.BuyEnergy[dayId][hour];
			
			if(dayId==102)
			{
				fprintf(fpobjective1A,"%d	%g	%g\n",hour, h1.SellEnergy[dayId][hour],h1.BuyEnergy[dayId][hour]);
			}

			avgEnergyDaily[hour]+= h1.SellEnergy[dayId][hour];
		}
		
		monthlyEnergyProduction[DayToMonth(dayId)] += sumProdPerDay;
		monthlyEnergyConsumption[DayToMonth(dayId)] += sumConsPerDay;

		totalIncome += h1.Income[dayId];
		totalExpenses += h1.Expense[dayId];

		monthlyIncome[DayToMonth(dayId)] += h1.Income[dayId];
		monthlyExpense[DayToMonth(dayId)] += h1.Expense[dayId];



	}

	for(int i=1;i<=24;i++)
	{
		fprintf(fpobjective1B, "%d	%g	%g\n", i, avgEnergyDaily[i]/simDays,h1.BuyEnergy[102][i]);
	}

	for(int i=1;i<=12;i++)
	{
		fprintf(fpobjective1C,"%d	%g	%g\n", i, monthlyIncome[i], monthlyExpense[i]);
		fprintf(fpobjective1D,"%d	%g	%g\n", i, monthlyEnergyProduction[i], monthlyEnergyConsumption[i]);
	}
	
	fclose(fpobjective1A);
	fclose(fpobjective1B);
	fclose(fpobjective1C);
	fclose(fpobjective1D);

    FILE * gnuplotPipe4 = _popen ("gnuplot \"config\\Objective1A.gnu\"", "w");
	_pclose( gnuplotPipe4 );
	 
    FILE * gnuplotPipe5 = _popen ("gnuplot \"config\\Objective1B.gnu\"", "w");
	 _pclose( gnuplotPipe5 );
	 
    FILE * gnuplotPipe6 = _popen ("gnuplot \"config\\Objective1C.gnu\"", "w");
	 _pclose( gnuplotPipe6 );
	 
    FILE * gnuplotPipe7 = _popen ("gnuplot \"config\\Objective1D.gnu\"", "w");
	 _pclose( gnuplotPipe7 );

	cout << "[+] Objectives(1A-1D).jpeg files have been generated\n";

	return 0;
}


int SimulateInvestitionInSingleWindTurbnie(int simDays, double monthlyConsE, Forecaster f1)
{
	cout << "\n[ ] Objectives 2A-2D: Simulation of single house with 10kW wind turbine\n";

	Household h1(simDays, monthlyConsE, 15,10,-1); //wind turbine 2kW having 12 meters tower

	double totalIncome = 0;
	double totalExpenses = 0;
	double monthlyEnergyProduction[13];
	double monthlyEnergyConsumption[13];
	double sumProdPerDay =0;
	double sumProdPerMonth =0;
	double sumProdPerYear =0;
	double sumConsPerDay =0;
	double fluxOfInsolation[13];
	double monthlyIncome[13];
	double monthlyExpense[13];
	double avgEnergyDaily[25];
	int monthlySaveDayCounter=1;

	Hour_Data currentWeather;
	
	FILE *fpobjective1A;
	FILE *fpobjective1B;
	FILE *fpobjective1C;
	FILE *fpobjective1D;

	for(int i=0;i<13;i++)
		monthlyIncome[i]=monthlyExpense[i]=fluxOfInsolation[i]=monthlyEnergyProduction[i]=monthlyEnergyConsumption[i]=0;
	
	for(int i=1;i<25;i++)
		avgEnergyDaily[i]=0;
	
	fpobjective1A=fopen("output\\Objective2A.txt","w");
	fpobjective1B=fopen("output\\Objective2B.txt","w");
	fpobjective1C=fopen("output\\Objective2C.txt","w");
	fpobjective1D=fopen("output\\Objective2D.txt","w");
	
	for (int dayId=0;dayId<=simDays;dayId++)
	{
		sumProdPerDay=0;
		sumConsPerDay=0;

		for(int hour = 1;hour<=24;hour++)
		{
			currentWeather = f1.RequestWeather(dayId,hour);

			h1.RequestToParticipate(dayId,hour,currentWeather,f1.RequestDailyFlux(dayId,hour));

			fluxOfInsolation[DayToMonth(dayId)]+=f1.RequestDailyFlux(dayId,hour)*currentWeather.solarTime;

			sumProdPerDay += h1.SellEnergy[dayId][hour];
			sumConsPerDay += h1.BuyEnergy[dayId][hour];
			
			if(dayId==102)
			{
				fprintf(fpobjective1A,"%d	%g	%g\n",hour, h1.SellEnergy[dayId][hour],h1.BuyEnergy[dayId][hour]);
			}

			avgEnergyDaily[hour]+= h1.SellEnergy[dayId][hour];
		}
		
		monthlyEnergyProduction[DayToMonth(dayId)] += sumProdPerDay;
		monthlyEnergyConsumption[DayToMonth(dayId)] += sumConsPerDay;

		totalIncome += h1.Income[dayId];
		totalExpenses += h1.Expense[dayId];

		monthlyIncome[DayToMonth(dayId)] += h1.Income[dayId];
		monthlyExpense[DayToMonth(dayId)] += h1.Expense[dayId];

	}

	for(int i=1;i<=24;i++)
	{
		fprintf(fpobjective1B, "%d	%g	%g\n", i, avgEnergyDaily[i]/simDays,h1.BuyEnergy[102][i]);
	}

	for(int i=1;i<=12;i++)
	{
		fprintf(fpobjective1C,"%d	%g	%g\n", i, monthlyIncome[i], monthlyExpense[i]);
		fprintf(fpobjective1D,"%d	%g	%g\n", i, monthlyEnergyProduction[i]/1000, monthlyEnergyConsumption[i]/1000);
	}
	
	fclose(fpobjective1A);
	fclose(fpobjective1B);
	fclose(fpobjective1C);
	fclose(fpobjective1D);
	
    FILE * gnuplotPipe4 = _popen ("gnuplot \"config\\Objective2A.gnu\"", "w");
	 _pclose( gnuplotPipe4 );
	 
    FILE * gnuplotPipe5 = _popen ("gnuplot \"config\\Objective2B.gnu\"", "w");
	 _pclose( gnuplotPipe5 );
	 
    FILE * gnuplotPipe6 = _popen ("gnuplot \"config\\Objective2C.gnu\"", "w");
	 _pclose( gnuplotPipe6 );
	 
    FILE * gnuplotPipe7 = _popen ("gnuplot \"config\\Objective2D.gnu\"", "w");
	 _pclose( gnuplotPipe7 );

	cout << "[+] Objectives(2A-2D).jpeg files have been generated\n";

	return 0;
}

int SimulateSmartGridAtTheAwajiIsland11Houses(Forecaster f1,int simulationDays, double monthlyConsE)
{
	const int amountOfHousehold = 11;
	bool info = true;

	cout << "\n[ ] Objective 3: Simulation of smart grid for " << amountOfHousehold << " houses" << endl;
	vector<Household> houses;
	/*
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleWindTurbine(1)));
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleWindTurbine(2)));
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleWindTurbine(3)));
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleWindTurbine(4)));
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleWindTurbine(5)));
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleSolarFarm()));
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleSolarPanel(1)));
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleSolarPanel(2)));
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleSolarPanel(3)));
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleSolarPanel(4)));
	houses.push_back(Household(simulationDays,randn_trig(monthlyConsE,100),ReturnSampleSolarPanel(5)));*/
	
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleWindTurbine(1)));
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleWindTurbine(2)));
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleWindTurbine(3)));
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleWindTurbine(4)));
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleWindTurbine(5)));
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleSolarFarm()));
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleSolarPanel(1)));
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleSolarPanel(2)));
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleSolarPanel(3)));
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleSolarPanel(4)));
	houses.push_back(Household(simulationDays,monthlyConsE,ReturnSampleSolarPanel(5)));
	
	
	for(int h=0;h<amountOfHousehold;h++)
	{
		switch(houses[h].producerUnit.producerType)
		{
			case solar_panel:
				cout << "[ ] created " <<houses[h].producerUnit.power << "kW solar panel with monthly cons " <<houses[h].consumerUnit.statisticalDailyConsumption <<endl ;
				break;
			case solar_farm:
				cout << "[ ] created " <<houses[h].producerUnit.power << "kW solar farm with monthly cons " <<houses[h].consumerUnit.statisticalDailyConsumption <<endl ;
				break;
			case wind_turbine:
				cout << "[ ] created " <<houses[h].producerUnit.power << "kW wind turbin with monthly cons " <<houses[h].consumerUnit.statisticalDailyConsumption <<endl ;
				break;
		}
	}
	/*for(int h=0;h<amountOfHousehold;h++)
	{
		double monthlyCons = randn_trig(monthlyConsE,100);
		houses.push_back(Household(simulationDays,monthlyCons));
		if(info)
		{
			switch(houses[h].producerUnit.producerType)
			{
				case solar_panel:
					cout << "[ ] created " <<houses[h].producerUnit.power << "kW solar panel\n";
					break;
				case solar_farm:
					cout << "[ ] created " <<houses[h].producerUnit.power << "kW solar farm\n";
					break;
				case wind_turbine:
					cout << "[ ] created " <<houses[h].producerUnit.power << "kW wind turbine\n";
					break;
			}
					
		}
	}*/
	double accountBalanceWeekly[53][amountOfHousehold];
	double expenseWeekly[53][amountOfHousehold];
	double incomeWeekly[53][amountOfHousehold];
	double buyEnergyWeekly[53][amountOfHousehold];
	double sellEnergyWeekly[53][amountOfHousehold];
	
	double accountBalanceMonthly[13][amountOfHousehold];
	double expenseMonthly[13][amountOfHousehold];
	double incomeMonthly[13][amountOfHousehold];
	double buyEnergyMonthly[13][amountOfHousehold];
	double sellEnergyMonthly[13][amountOfHousehold];
	
	for(int i=0;i<53;i++)
		for(int j=0;j<amountOfHousehold;j++)
			expenseWeekly[i][j] = incomeWeekly[i][j] = buyEnergyWeekly[i][j] = sellEnergyWeekly[i][j] = accountBalanceWeekly[i][j] = 0;
	
	for(int i=0;i<13;i++)
		for(int j=0;j<amountOfHousehold;j++)
			expenseMonthly[i][j] = incomeMonthly[i][j] = buyEnergyMonthly[i][j] = sellEnergyMonthly[i][j] = accountBalanceMonthly[i][j] = 0;
		
	
	////////////////////////////////
	//start of simulation
	////////////////////////////////
	for (int dayId=0;dayId<=simulationDays;dayId++)
	{
		//cout << "day" << dayId<<endl;
		for(int houseId=0;houseId<amountOfHousehold;houseId++)
		{
			//cout <<"house"<<houseId<<endl;
			
			for(int hour = 1;hour<=24;hour++)
			{
				Hour_Data currentWeather = f1.RequestWeather(dayId,hour);
				//cout <<"h" << hour;
				houses[houseId].RequestToParticipate(dayId,hour,currentWeather,f1.RequestDailyFlux(dayId,hour));
				//cout << "#";
				buyEnergyWeekly[dayId/7][houseId]+=houses[houseId].BuyEnergy[dayId][hour];
				sellEnergyWeekly[dayId/7][houseId]+=houses[houseId].SellEnergy[dayId][hour];
				accountBalanceWeekly[dayId/7][houseId]+=houses[houseId].AccountBalance[dayId][hour];
				buyEnergyMonthly[DayToMonth(dayId)][houseId]+=houses[houseId].BuyEnergy[dayId][hour];
				sellEnergyMonthly[DayToMonth(dayId)][houseId]+=houses[houseId].SellEnergy[dayId][hour];
				accountBalanceMonthly[DayToMonth(dayId)][houseId]+=houses[houseId].AccountBalance[dayId][hour];
			}
			//cout <<"end"<<endl;
			expenseWeekly[dayId/7][houseId]+=houses[houseId].Expense[dayId];
			incomeWeekly[dayId/7][houseId]+=houses[houseId].Income[dayId];
			expenseMonthly[DayToMonth(dayId)][houseId]+=houses[houseId].Expense[dayId];
			incomeMonthly[DayToMonth(dayId)][houseId]+=houses[houseId].Income[dayId];
		}
	}
	////////////////////////////////
	//end of simulation
	////////////////////////////////
	
	////////////////////////////////
	//saving results
	////////////////////////////////
	for(int houseID=0;houseID<amountOfHousehold;houseID++)
	{
		//cout <<"house"<<houseID<<endl;
		/*std::stringstream fileNameSS1, fileNameSS2,fileNameGnuSS,fileNameGnuSS2 ;
		fileNameSS1 << "output\\House" << houseID << ".txt";
		fileNameSS2 << "output\\House" << houseID << "-energy.txt";
		fileNameGnuSS << "output\\House" << houseID << ".gnu";
		fileNameGnuSS2 << "output\\House" << houseID << "-energy.gnu";*/
		
		std::stringstream fileNameSS[7];
		std::stringstream fileNameGnuSS[7];
		fileNameSS[0] << "output\\House" << houseID << "-w.txt";
		//fileNameSS[5] << "output\\House" << houseID << "-w-ab.txt";
		fileNameSS[1] << "output\\House" << houseID << "-w-energy.txt";
		fileNameSS[2] << "output\\House" << houseID << "-m.txt";
		fileNameSS[3] << "output\\House" << houseID << "-m-energy.txt";
		fileNameSS[4] << "output\\House" << houseID << "-roi.txt";
		fileNameGnuSS[0] << "output\\House" << houseID << "-w.gnu";
		//fileNameGnuSS[5] << "output\\House" << houseID << "-w-ab.gnu";
		fileNameGnuSS[1] << "output\\House" << houseID << "-w-energy.gnu";
		fileNameGnuSS[2] << "output\\House" << houseID << "-m.gnu";
		fileNameGnuSS[3] << "output\\House" << houseID << "-m-energy.gnu";
		fileNameGnuSS[4] << "output\\House" << houseID << "-roi.gnu";
		/*std::string fileName1 = fileNameSS1.str();
		std::string fileName2 = fileNameSS2.str();
		std::string fileNameGnu = fileNameGnuSS.str();
		std::string fileNameGnu2 = fileNameGnuSS2.str();*/
		std::string fileName[6],fileNameGnu[6];
		for(int i=0;i<5;i++)
		{
			fileName[i]	= fileNameSS[i].str();
			fileNameGnu[i] = fileNameGnuSS[i].str();
		}
		//FILE *fp1,*fp2,*fpGnu,*fpGnu2;
		//fp1 = fopen(fileName1.c_str(),"w");
		//fp2 = fopen(fileName2.c_str(),"w");
		FILE *fp[6],*fpGnu[6];
		for(int i=0;i<5;i++)
		{
			fp[i] = fopen(fileName[i].c_str(),"w");
		}
		
		for(int i=0;i<52;i++)
		{
			fprintf(fp[0], "%d	%g	%g\n", i, expenseWeekly[i][houseID], incomeWeekly[i][houseID]); //old is gold
			fprintf(fp[1], "%d	%g	%g\n", i, buyEnergyWeekly[i][houseID], sellEnergyWeekly[i][houseID]);
		}

		for(int i=1;i<=12;i++)
		{
			fprintf(fp[2], "%d	%g	%g\n", i, expenseMonthly[i][houseID], incomeMonthly[i][houseID]);
			fprintf(fp[3], "%d	%g	%g\n", i, buyEnergyMonthly[i][houseID], sellEnergyMonthly[i][houseID]);
		}
		
		fclose(fp[0]);
		fclose(fp[1]);
		fclose(fp[2]);
		fclose(fp[3]);
		
		///////////////////////////////////////////
		//generating gnu script file for results of weekly income/expense HouseXX-w.txt
		////////////////////////////////////////////
		fpGnu[0] = fopen(fileNameGnu[0].c_str(),"w");
		fprintf(fpGnu[0],"set terminal jpeg size 1600,900 enhanced font calibri 20\n");
		fprintf(fpGnu[0],"set output 'output\\House%d-w.jpeg'\n",houseID);
		if( houses[houseID].producerUnit.producerType == solar_panel)
			fprintf(fpGnu[0],"set title \"Simulation of one household with %g kW solar panel\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		if( houses[houseID].producerUnit.producerType == solar_farm)
			fprintf(fpGnu[0],"set title \"Simulation of one household with %g kW solar farm\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		if( houses[houseID].producerUnit.producerType == wind_turbine)
			fprintf(fpGnu[0],"set title \"Simulation of one household with %g kW wind power\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		fprintf(fpGnu[0],"set xlabel \"Week\" font \"calibri,20\"\n");
		fprintf(fpGnu[0],"set ylabel \"Yen\" font \"calibri,20\"\n");
		fprintf(fpGnu[0],"set data style linespoints\n");
		fprintf(fpGnu[0],"set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
		fprintf(fpGnu[0],"set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
		fprintf(fpGnu[0],"set xrange [0:52]\n");
		fprintf(fpGnu[0],"set yrange [0:*]\n");
		fprintf(fpGnu[0],"set multiplot\n");
		fprintf(fpGnu[0],"plot 'output\\House%d-w.txt' using 2 title \"Expense\",\\\n",houseID);
		fprintf(fpGnu[0],"	'output\\House%d-w.txt' using 3 title \"Income\"\n",houseID);
		fprintf(fpGnu[0],"unset multiplot\n");
		fclose(fpGnu[0]);

		
		///////////////////////////////////////////
		//generating gnu script file for results of weekly buy/sell energy HouseXX-w-energy.txt
		////////////////////////////////////////////
		fpGnu[1] = fopen(fileNameGnu[1].c_str(),"w");
		fprintf(fpGnu[1],"set terminal jpeg size 1600,900 enhanced font calibri 20\n");
		fprintf(fpGnu[1],"set output 'output\\House%d-w-energy.jpeg'\n",houseID);
		if( houses[houseID].producerUnit.producerType == solar_panel)
			fprintf(fpGnu[1],"set title \"Simulation of one household with %g kW solar panel\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		if( houses[houseID].producerUnit.producerType == solar_farm)
			fprintf(fpGnu[1],"set title \"Simulation of one household with %g kW solar farm\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		if( houses[houseID].producerUnit.producerType == wind_turbine)
			fprintf(fpGnu[1],"set title \"Simulation of one household with %g kW wind power\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		fprintf(fpGnu[1],"set xlabel \"Week\" font \"calibri,20\"\n");
		fprintf(fpGnu[1],"set ylabel \"Energy (kWh)\" font \"calibri,20\"\n");
		fprintf(fpGnu[1],"set data style linespoints\n");
		fprintf(fpGnu[1],"set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
		fprintf(fpGnu[1],"set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
		fprintf(fpGnu[1],"set xrange [0:52]\n");
		fprintf(fpGnu[1],"set yrange [0:*]\n");
		fprintf(fpGnu[1],"set multiplot\n");
		fprintf(fpGnu[1],"plot 'output\\House%d-w-energy.txt' using 2 title \"Consumption\",\\\n",houseID);
		fprintf(fpGnu[1],"	'output\\House%d-w-energy.txt' using 3 title \"Production\"\n",houseID);
		fprintf(fpGnu[1],"unset multiplot\n");
		fclose(fpGnu[1]);
		
		///////////////////////////////////////////
		//generating gnu script file for results of monthly income/expense HouseXX-m.txt
		////////////////////////////////////////////
		fpGnu[2] = fopen(fileNameGnu[2].c_str(),"w");
		fprintf(fpGnu[2],"set terminal jpeg size 1600,900 enhanced font calibri 20\n");
		fprintf(fpGnu[2],"set output 'output\\House%d-m.jpeg'\n",houseID);
		if( houses[houseID].producerUnit.producerType == solar_panel)
			fprintf(fpGnu[2],"set title \"Simulation of one household with %g kW solar panel\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		if( houses[houseID].producerUnit.producerType == solar_farm)
			fprintf(fpGnu[2],"set title \"Simulation of one household with %g kW solar farm\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		if( houses[houseID].producerUnit.producerType == wind_turbine)
			fprintf(fpGnu[2],"set title \"Simulation of one household with %g kW wind power\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		fprintf(fpGnu[2],"set xlabel \"Month\" font \"calibri,20\"\n");
		fprintf(fpGnu[2],"set ylabel \"Yen\" font \"calibri,20\"\n");
		fprintf(fpGnu[2],"set data style linespoints\n");
		fprintf(fpGnu[2],"set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
		fprintf(fpGnu[2],"set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
		fprintf(fpGnu[2],"set yrange [0:*]\n");
		fprintf(fpGnu[2],"set multiplot\n");
		fprintf(fpGnu[2],"plot 'output\\House%d-m.txt' using 2 title \"Expense\",\\\n",houseID);
		fprintf(fpGnu[2],"	'output\\House%d-m.txt' using 3 title \"Income\"\n",houseID);
		fprintf(fpGnu[2],"unset multiplot\n");
		fclose(fpGnu[2]);

		
		///////////////////////////////////////////
		//generating gnu script file for results of monthly buy/sell energy HouseXX-m-energy.txt
		////////////////////////////////////////////
		fpGnu[3] = fopen(fileNameGnu[3].c_str(),"w");
		fprintf(fpGnu[3],"set terminal jpeg size 1600,900 enhanced font calibri 20\n");
		fprintf(fpGnu[3],"set output 'output\\House%d-m-energy.jpeg'\n",houseID);
		if( houses[houseID].producerUnit.producerType == solar_panel)
			fprintf(fpGnu[3],"set title \"Simulation of one household with %g kW solar panel\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		if( houses[houseID].producerUnit.producerType == solar_farm)
			fprintf(fpGnu[3],"set title \"Simulation of one household with %g kW solar farm\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		if( houses[houseID].producerUnit.producerType == wind_turbine)
			fprintf(fpGnu[3],"set title \"Simulation of one household with %g kW wind power\" font \"calibri,26\"\n",houses[houseID].producerUnit.power);
		fprintf(fpGnu[3],"set xlabel \"Month\" font \"calibri,20\"\n");
		fprintf(fpGnu[3],"set ylabel \"Energy (kWh)\" font \"calibri,20\"\n");
		fprintf(fpGnu[3],"set data style linespoints\n");
		fprintf(fpGnu[3],"set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
		fprintf(fpGnu[3],"set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
		fprintf(fpGnu[3],"set yrange [0:*]\n");
		fprintf(fpGnu[3],"set multiplot\n");
		fprintf(fpGnu[3],"plot 'output\\House%d-m-energy.txt' using 2 title \"Consumption\",\\\n",houseID);
		fprintf(fpGnu[3],"	'output\\House%d-m-energy.txt' using 3 title \"Production\"\n",houseID);
		fprintf(fpGnu[3],"unset multiplot\n");
		fclose(fpGnu[3]);
		///////////////////////////////////////////
		//generating Rate of Return Graph(ROI)
		////////////////////////////////////////////
		double simYears=5;
		double sum=-1*houses[houseID].producerUnit.price;
		//including subisdy
		//if(houses[houseID].producerUnit.price<475000)
		//	sum+=houses[houseID].producerUnit.power*
		int simMonthCount=1;
		fprintf(fp[4], "%d	%g\n", 0, sum/10000.0);
		for(int year=1;year<=simYears;year++)
		{
			for(int month=1;month<=12;month++)
			{
				sum+=incomeMonthly[month][houseID];
				fprintf(fp[4], "%d	%g\n", (((year-1)*12)+month), sum/10000.0);
			}
		}
		fclose(fp[4]);
		double ROI=((sum+houses[houseID].producerUnit.price)/simYears)/houses[houseID].producerUnit.price; //"+" becasue suming started not from 0 by from -price
		int ROIproc=(int)(ROI*100);
		//saving
		fpGnu[4] = fopen(fileNameGnu[4].c_str(),"w");
		fprintf(fpGnu[4],"set terminal jpeg size 1600,900 enhanced font calibri 20\n");
		fprintf(fpGnu[4],"set output 'output\\House%d-roi.jpeg'\n",houseID);
		if( houses[houseID].producerUnit.producerType == solar_panel)
			fprintf(fpGnu[4],"set title \"Rate Of Interest for %g kW solar panel = %d%%\" font \"calibri,26\"\n",houses[houseID].producerUnit.power,ROIproc);
		if( houses[houseID].producerUnit.producerType == solar_farm)
			fprintf(fpGnu[4],"set title \"Rate Of Interest for %g kW solar farm = %d%%\" font \"calibri,26\"\n",houses[houseID].producerUnit.power,ROIproc);
		if( houses[houseID].producerUnit.producerType == wind_turbine)
			fprintf(fpGnu[4],"set title \"Rate Of Interest for %g kW wind turbine = %d%%\" font \"calibri,26\"\n",houses[houseID].producerUnit.power,ROIproc);
		fprintf(fpGnu[4],"set xlabel \"Month\" font \"calibri,20\"\n");
		fprintf(fpGnu[4],"set ylabel \"Raturn of investition in man yen\" font \"calibri,20\"\n");
		fprintf(fpGnu[4],"set data style linespoints\n");
		fprintf(fpGnu[4],"set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
		fprintf(fpGnu[4],"set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
		//fprintf(fpGnu[3],"set yrange [0:*]\n");
		fprintf(fpGnu[4],"set multiplot\n");
		fprintf(fpGnu[4],"plot 'output\\House%d-roi.txt' using 1:2 title \"Expected profit\" linecolor rgbcolor \"dark-red\"\n",houseID);
		//fprintf(fpGnu[4],"	'output\\House%d-roi.txt' using 3 title \"Production\"\n",houseID);
		fprintf(fpGnu[4],"unset multiplot\n");
		fclose(fpGnu[4]);

	}
	
		///////////////////////////////////////////
		//execute gnu file
		///////////////////////////////////////////
		for(int houseID=0;houseID<amountOfHousehold;houseID++)
		{
			std::stringstream GnuCommandSS;
			GnuCommandSS << "gnuplot \"output\\House" << houseID << "-w.gnu\"";
			std::string GnuCommand = GnuCommandSS.str();
			FILE * gnuplotPipe = _popen (GnuCommand.c_str(), "w");
			 _pclose( gnuplotPipe );
		}
		for(int houseID=0;houseID<amountOfHousehold;houseID++)
		{
			std::stringstream GnuCommandSS;
			GnuCommandSS << "gnuplot \"output\\House" << houseID << "-w-energy.gnu\"";
			std::string GnuCommand = GnuCommandSS.str();
			FILE * gnuplotPipe = _popen (GnuCommand.c_str(), "w");
			_pclose( gnuplotPipe );
		}
		for(int houseID=0;houseID<amountOfHousehold;houseID++)
		{
			std::stringstream GnuCommandSS;
			GnuCommandSS << "gnuplot \"output\\House" << houseID << "-m.gnu\"";
			std::string GnuCommand = GnuCommandSS.str();
			FILE * gnuplotPipe = _popen (GnuCommand.c_str(), "w");
			_pclose( gnuplotPipe );
		}
		for(int houseID=0;houseID<amountOfHousehold;houseID++)
		{
			std::stringstream GnuCommandSS;
			GnuCommandSS << "gnuplot \"output\\House" << houseID << "-m-energy.gnu\"";
			std::string GnuCommand = GnuCommandSS.str();
			FILE * gnuplotPipe = _popen (GnuCommand.c_str(), "w");
			_pclose( gnuplotPipe );
		}
		for(int houseID=0;houseID<amountOfHousehold;houseID++)
		{
			std::stringstream GnuCommandSS;
			GnuCommandSS << "gnuplot \"output\\House" << houseID << "-roi.gnu\"";
			std::string GnuCommand = GnuCommandSS.str();
			FILE * gnuplotPipe = _popen (GnuCommand.c_str(), "w");
			_pclose( gnuplotPipe );
		}
	return 0;

}


int SimulateSmartGridAtTheAwajiIsland(double dailyConsE)
{
	const int amountOfHousehold = 8000;
	const int simulationDays = 365;

	cout << "[ ] Objective 3A-3C: Simulation of smart grid for 10000 houses" << endl; 
	//maximum memory capcity is for 8000 households, result is later it is multiplied by houseRatio upto 10000 households

	vector<Household> houses;
	vector<Household> windPowerPlants;
	vector<Household> solarPowerPlants;
	vector<Household> privateSolarFarms;
	int producerTypeCount[3];
	Forecaster f1= Forecaster(2012);
//	int amountOfHouseholdInMemory;
//	int amountOfHouseholdSImulated;
//	double houseRatio;

	//to not fulfill memory - if more than 8000 households, application crushes
	//if(amountOfHousehold <5000)

	cout << "[+] generating 10000 households";

	producerTypeCount[0]= producerTypeCount[1]=producerTypeCount[2]=0;
	int countEmptyHouses=0;
	for(int h=0;h<amountOfHousehold;h++)
	{
		//double dailyCons = randn_notrig(dailyConsE,2.5);
		double dailyCons = randn_notrig(dailyConsE,6);
		if(dailyCons < 0)
		{
			dailyCons =0;
			countEmptyHouses++;
		}

		houses.push_back(Household(simulationDays,dailyCons)); 
		if(0==h%1000)
			cout << ".";
	}

	cout << endl << "[ ] empty houses = " << countEmptyHouses <<endl;
	
	for(int i=0;i<6;i++) //kanden wind farm
		windPowerPlants.push_back(Household(simulationDays,0,Producer(60,2000,-1)));
	
	cout << "[+] Generated Kanden's wind farm at the Awaji Island" <<endl;
	for(int i=0;i<15;i++) //CEF wind farm
		windPowerPlants.push_back(Household(simulationDays,0,Producer(60,2500,-1)));
	
	cout << "[+] Generated CEF's wind farm at the Awaji Island" <<endl;
	
	solarPowerPlants.push_back(Household(simulationDays,0,Producer(200000,0.1,30000,-1)));

	cout << "[+] Generated Kanden's solar farm at the Awaji Island" <<endl;
	
	for(int i=0;i<500;i++)
		privateSolarFarms.push_back(Household(simulationDays,0,Producer(500,0.1,73,12800883)));

	cout << "[+] Generated 500 private solar farms" << endl;
	
	//for all households
	double expenseMonthly[13];
	double incomeMonthly[13];
	//double accountBalanceMonthly[13];
	double buyEnergyMonthly[13];
	double sellEnergyMonthly[13];
	
	double sellEnergyMonthlyWindPowerPlants[13];
	double sellEnergyMonthlySolarPowerPlants[13];
	double sellEnergyMonthlyPrivateSolarFarms[13];
	double buyEnergyMonthlyPrivateSolarFarms[13];

	/*int amountOfHouseholdsAndPowerPlants= 10570;
	vector<Household> housesAndPowerPlants;
	Forecaster forecaster= Forecaster(2012);
	
	for (int dayId=0;dayId<=simulationDays;dayId++)
	{
		for(int hour = 1;hour<=24;hour++)
		{
			for(int id=0;id<amountOfHouseholdsAndPowerPlants;id++)
			{
				Hour_Data currentWeather = forecaster.RequestWeather(dayId,hour);
				double Flux = forecaster.RequestDailyFlux(dayId,hour);
				housesAndPowerPlants[id].RequestToParticipate(dayId,hour,currentWeather,Flux);

			}
		}
	}*/

	for(int i=0;i<13;i++)
	{
		 expenseMonthly[i] = incomeMonthly[i] = buyEnergyMonthly[i] = sellEnergyMonthly[i]=0;
		 sellEnergyMonthlyWindPowerPlants[i]=sellEnergyMonthlySolarPowerPlants[i]=sellEnergyMonthlyPrivateSolarFarms[i]=buyEnergyMonthlyPrivateSolarFarms[i]=0;
	}
		
	//for(int i=0;i<53;i++)
	//{
		// totalExpenseWeekly[i] = totalIncomeWeekly[i] = totalBuyEnergyWeekly[i] = totalSellEnergyWeekly[i]=0;
		// totalSellEnergyWeeklyWindPowerPlants[i]=totalSellEnergyWeeklySolarPowerPlants[i]=totalSellEnergyWeeklyPrivateSolarFarms[i]=0;
	//}
	cout << "[+] computing";
	///////////////////////////////
	//simulation of households
	////////////////////////////////
	for (int dayId=0;dayId<=simulationDays;dayId++)
	{
		for(int houseId=0;houseId<amountOfHousehold;houseId++)
		{
			for(int hour = 1;hour<=24;hour++)
			{
				Hour_Data currentWeather = f1.RequestWeather(dayId,hour);
				houses[houseId].RequestToParticipate(dayId,hour,currentWeather,f1.RequestDailyFlux(dayId,hour));
				
				buyEnergyMonthly[DayToMonth(dayId)]+=houses[houseId].BuyEnergy[dayId][hour];
				sellEnergyMonthly[DayToMonth(dayId)]+=houses[houseId].SellEnergy[dayId][hour];
			}

			expenseMonthly[DayToMonth(dayId)]+=houses[houseId].Expense[dayId];
			incomeMonthly[DayToMonth(dayId)]+=houses[houseId].Income[dayId];
		}
		if(0==dayId%8) cout << ".";
	}
	///////////////////////////////
	//simulation of wind farms
	////////////////////////////////
	for (int dayId=0;dayId<=simulationDays;dayId++)
	{
		for(int plantId=0;plantId<windPowerPlants.size();plantId++)
		{
			for(int hour = 1;hour<=24;hour++)
			{
				Hour_Data currentWeather = f1.RequestWeather(dayId,hour);
				windPowerPlants[plantId].RequestToParticipate(dayId,hour,currentWeather,f1.RequestDailyFlux(dayId,hour));
				sellEnergyMonthlyWindPowerPlants[DayToMonth(dayId)]+=windPowerPlants[plantId].SellEnergy[dayId][hour];
			}
		}
	}
	
	///////////////////////////////
	//simulation of Kadnen solar farm
	////////////////////////////////
	for (int dayId=0;dayId<=simulationDays;dayId++)
	{
		for(int plantId=0;plantId<solarPowerPlants.size();plantId++)
		{
			for(int hour = 1;hour<=24;hour++)
			{
				Hour_Data currentWeather = f1.RequestWeather(dayId,hour);
				solarPowerPlants[plantId].RequestToParticipate(dayId,hour,currentWeather,f1.RequestDailyFlux(dayId,hour));
				sellEnergyMonthlySolarPowerPlants[DayToMonth(dayId)]+=solarPowerPlants[plantId].SellEnergy[dayId][hour];
			}
		}
	}
	
	///////////////////////////////
	//simulation of private solar farms
	////////////////////////////////
	for (int dayId=0;dayId<=simulationDays;dayId++)
	{
		for(int plantId=0;plantId<privateSolarFarms.size();plantId++)
		{
			for(int hour = 1;hour<=24;hour++)
			{
				Hour_Data currentWeather = f1.RequestWeather(dayId,hour);
				privateSolarFarms[plantId].RequestToParticipate(dayId,hour,currentWeather,f1.RequestDailyFlux(dayId,hour));
				sellEnergyMonthlyPrivateSolarFarms[DayToMonth(dayId)]+=privateSolarFarms[plantId].SellEnergy[dayId][hour];
				buyEnergyMonthlyPrivateSolarFarms[DayToMonth(dayId)]+=privateSolarFarms[plantId].BuyEnergy[dayId][hour];
			}
		}
	}

	cout << endl << "[+] saving results and generating graphs";

	FILE *fpobjective3A,*fpobjective3B,*fpobjective3C,*fpobjective3C2,*fpobjective3D,*fpobjective3E;
	if(NULL == (fpobjective3A=fopen("output\\Objective3A.txt","w")))
	{
		printf("error opening file Objective3A.txt\n");
	}
	fpobjective3B=fopen("output\\Objective3B.txt","w");
	fpobjective3C=fopen("output\\Objective3C.txt","w");
	fpobjective3C2=fopen("output\\Objective3C2.txt","w");
	fpobjective3D=fopen("output\\Objective3D.txt","w");
	fpobjective3E=fopen("output\\Objective3E.txt","w");
	
	double totalEnergyInAwajiIslandProduced=0; //only households withoud solar farm
	double totalEnergyInAwajiIslandProduced2=0;  //with solar farm
	double totalEnergyInAwajiIslandConsumed=0;
	double totalProdEnergyInAwajiIslandProducedOnlySolarPlants=0;
	double totalProdEnergyInAwajiIslandProducedOnlyWindPlants=0;
	double totalProdEnergyInAwajiIslandProducedAlsoPowerPlants=0;
	//double totalConsEnergyInAwajiIslandProducedAlsoPowerPlants=0;
	
	double houseRatio = 10000/8000; //to calculate for 10000 houses
	double energyConsumedCurrentMonth=0;
	for(int i=1;i<=12;i++)
	{
		fprintf_s(fpobjective3A,"%d	%g	%g\n", i, houseRatio*incomeMonthly[i]/10000, houseRatio*expenseMonthly[i]/10000);
		fprintf_s(fpobjective3B,"%d	%g	%g\n", i, houseRatio*sellEnergyMonthly[i]/1000, houseRatio* buyEnergyMonthly[i]/1000);
		//totalEnergyInAwajiIslandProduced += (totalSellEnergyWeekly[i])/1000;
		//totalEnergyInAwajiIslandProduced2 += (totalSellEnergyWeekly[i] + totalSellEnergyWeeklyPrivateSolarFarms[i])/1000;
		totalEnergyInAwajiIslandProduced += houseRatio*sellEnergyMonthly[i];
		totalEnergyInAwajiIslandProduced2 += (houseRatio*sellEnergyMonthly[i] + sellEnergyMonthlyPrivateSolarFarms[i]);
		energyConsumedCurrentMonth = (((53075-500)/amountOfHousehold)*houseRatio*buyEnergyMonthly[i]+buyEnergyMonthlyPrivateSolarFarms[i])/1000;
		totalEnergyInAwajiIslandConsumed += energyConsumedCurrentMonth;
		fprintf_s(fpobjective3C,"%d	%g	%g\n", i, sellEnergyMonthly[i]/1000 , energyConsumedCurrentMonth);
		//fprintf_s(fpobjective3C2,"%d	%g	%g	%g\n", i, totalSellEnergyWeekly[i]/1000 , (totalSellEnergyWeekly[i]+totalSellEnergyWeeklyPrivateSolarFarms[i])/1000 , (53075/amountOfHousehold)*totalBuyEnergyWeekly[i]/1000);
		fprintf_s(fpobjective3C2,"%d	%g	%g	%g\n", i, houseRatio*sellEnergyMonthly[i]/1000 , (houseRatio*sellEnergyMonthly[i]+sellEnergyMonthlyPrivateSolarFarms[i])/1000 , energyConsumedCurrentMonth);
		//fprintf_s(fpobjective3D,"%d	%g	%g	%g	%g	%g\n", i, totalSellEnergyWeekly[i]/1000 ,totalSellEnergyWeeklyWindPowerPlants[i]/1000, totalSellEnergyWeeklySolarPowerPlants[i]/1000, totalSellEnergyWeeklyPrivateSolarFarms[i]/1000, (53075/amountOfHousehold)*totalBuyEnergyWeekly[i]/1000);
		fprintf_s(fpobjective3D,"%d	%g	%g	%g	%g	%g\n", i, houseRatio*sellEnergyMonthly[i]/1000 ,sellEnergyMonthlyWindPowerPlants[i]/1000, sellEnergyMonthlySolarPowerPlants[i]/1000, sellEnergyMonthlyPrivateSolarFarms[i]/1000, energyConsumedCurrentMonth);
		totalProdEnergyInAwajiIslandProducedAlsoPowerPlants+=sellEnergyMonthlyWindPowerPlants[i];
		totalProdEnergyInAwajiIslandProducedAlsoPowerPlants+=sellEnergyMonthlySolarPowerPlants[i];
		totalProdEnergyInAwajiIslandProducedAlsoPowerPlants+=sellEnergyMonthlyPrivateSolarFarms[i];
		totalProdEnergyInAwajiIslandProducedAlsoPowerPlants+=houseRatio*sellEnergyMonthly[i];
		totalProdEnergyInAwajiIslandProducedOnlySolarPlants+=sellEnergyMonthlySolarPowerPlants[i];
		totalProdEnergyInAwajiIslandProducedOnlyWindPlants+=sellEnergyMonthlyWindPowerPlants[i];
		//? totalConsEnergyInAwajiIslandProducedAlsoPowerPlants+=((53075-500)/amountOfHousehold)*buyEnergyMonthly[i]+buyEnergyMonthlyPrivateSolarFarms[i];
		//fprintf_s(fpobjective3E,"%d	%g	%g\n", i, (totalSellEnergyWeeklyWindPowerPlants[i]+totalSellEnergyWeeklySolarPowerPlants[i]+totalSellEnergyWeeklyPrivateSolarFarms[i]+totalSellEnergyWeekly[i])/1000 , (53075/amountOfHousehold)*totalBuyEnergyWeekly[i]/1000);
		fprintf_s(fpobjective3E,"%d	%g	%g\n", i, (sellEnergyMonthlyWindPowerPlants[i]+sellEnergyMonthlySolarPowerPlants[i]+sellEnergyMonthlyPrivateSolarFarms[i]+houseRatio*sellEnergyMonthly[i])/1000 , energyConsumedCurrentMonth);
		cout << ".";
	}
	
	fclose(fpobjective3A);
	fclose(fpobjective3B);
	fclose(fpobjective3C);
	fclose(fpobjective3C2);
	fclose(fpobjective3D);
	fclose(fpobjective3E);
	
    FILE * gnuplotPipe4 = _popen ("gnuplot \"config\\Objective3A.gnu\"", "w"); _pclose( gnuplotPipe4 ); cout << ".";
    FILE * gnuplotPipe5 = _popen ("gnuplot \"config\\Objective3B.gnu\"", "w"); _pclose( gnuplotPipe5 ); cout << ".";
	 
	 ///////////////////////////////////////////
	//generating gnu script file for self sufficiency ratio without private solar farms
	////////////////////////////////////////////
	// double ratio = (totalEnergyInAwajiIslandProduced / totalEnergyInAwajiIslandConsumed ) * 100;
	 double ratio = (totalEnergyInAwajiIslandProduced * 100 / (totalEnergyInAwajiIslandConsumed*1000)); //statistical data in MWH so multiplied by 1000 to kWH units
	 FILE *fpobjective3Cgnu;
	fpobjective3Cgnu = fopen("output\\Objective3C.gnu","w");
	fprintf(fpobjective3Cgnu,"set terminal jpeg size 1600,900 enhanced font calibri 20\n");
	fprintf(fpobjective3Cgnu,"set output 'output\\Objective3C.jpeg'\n");
	fprintf(fpobjective3Cgnu,"set title \"Energetical self-sufficiency ratio for Awaji Island - %2.2f%%\" font \"calibri,26\"\n",ratio);
	fprintf(fpobjective3Cgnu,"set xlabel \"Month\" font \"calibri,20\"\n");
	fprintf(fpobjective3Cgnu,"set ylabel \"Energy (MWh)\" font \"calibri,20\"\n");
	fprintf(fpobjective3Cgnu,"set data style linespoints\n");
	fprintf(fpobjective3Cgnu,"set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
	fprintf(fpobjective3Cgnu,"set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
	fprintf(fpobjective3Cgnu,"set xrange [0:13]\n");
	fprintf(fpobjective3Cgnu,"set yrange [0:21000]\n");
	fprintf(fpobjective3Cgnu,"set multiplot\n");
	fprintf(fpobjective3Cgnu,"plot 'output\\Objective3C.txt' using 1:2 title \"Production %d houses\",\\\n", 10000 ); //houseRatio*amountOfHousehold
	fprintf(fpobjective3Cgnu,"	'output\\Objective3C.txt' using 1:3 title \"Consumption in 53075 households\"\n");
	fprintf(fpobjective3Cgnu,"unset multiplot\n");
	fclose(fpobjective3Cgnu);

    FILE * gnuplotPipe6 = _popen ("gnuplot \"output\\Objective3C.gnu\"", "w");	_pclose( gnuplotPipe6 ); cout << ".";

	 ///////////////////////////////////////////
	//generating gnu script file for self sufficiency ratio
	////////////////////////////////////////////
	// double ratio2 = (totalEnergyInAwajiIslandProduced2 / totalEnergyInAwajiIslandConsumed ) * 100;
	 double ratio2 = (totalEnergyInAwajiIslandProduced2 * 100/ (totalEnergyInAwajiIslandConsumed*1000)); //statistical data in MWH so multiplied by 1000 to kWH units
	 FILE *fpobjective3C2gnu;
	fpobjective3C2gnu = fopen("output\\Objective3C2.gnu","w");
	fprintf(fpobjective3C2gnu,"set terminal jpeg size 1600,900 enhanced font calibri 20\n");
	fprintf(fpobjective3C2gnu,"set output 'output\\Objective3C2.jpeg'\n");
	//fprintf(fpobjective3C2gnu,"set title \"Energetical self-sufficiency ratio for Awaji Island - %d%%\" font \"calibri,30\"\n",(int)ratio2);
	fprintf(fpobjective3C2gnu,"set title \"Energetical self-sufficiency ratio for Awaji Island\" font \"calibri,26\"\n");
	fprintf(fpobjective3C2gnu,"set xlabel \"Month\" font \"calibri,20\"\n");
	fprintf(fpobjective3C2gnu,"set ylabel \"Energy (MWh)\" font \"calibri,20\"\n");
	fprintf(fpobjective3C2gnu,"set data style linespoints\n");
	fprintf(fpobjective3C2gnu,"set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
	fprintf(fpobjective3C2gnu,"set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
	fprintf(fpobjective3C2gnu,"set xrange [0:13]\n");
	fprintf(fpobjective3C2gnu,"set yrange [0:22000]\n");
	fprintf(fpobjective3C2gnu,"set multiplot\n");
	fprintf(fpobjective3C2gnu,"plot 'output\\Objective3C2.txt' using 1:2 title \"Production %d houses - %2.2f%%\",\\\n", 10000,ratio );//houseRatio*amountOfHousehold
	fprintf(fpobjective3C2gnu," 'output\\Objective3C2.txt' using 1:3 title \"Production %d houses + 500 solar farms - %2.2f%%\" linecolor rgbcolor \"blue\",\\\n", 10000, ratio2 );
	fprintf(fpobjective3C2gnu,"	'output\\Objective3C2.txt' using 1:4 title \"Consumption in 53075 households\"\n");
	fprintf(fpobjective3C2gnu,"unset multiplot\n");
	fclose(fpobjective3Cgnu);
	
    FILE * gnuplotPipe62 = _popen ("gnuplot \"output\\Objective3C2.gnu\"", "w"); _pclose( gnuplotPipe62 ); cout << ".";
	 
	 ///////////////////////////////////////////
	//generating gnu script file for plants comparision graph
	////////////////////////////////////////////
	double ratioWind = totalProdEnergyInAwajiIslandProducedOnlyWindPlants * 100 / (totalEnergyInAwajiIslandConsumed*1000);
	double ratioSolar = totalProdEnergyInAwajiIslandProducedOnlySolarPlants * 100 / (totalEnergyInAwajiIslandConsumed*1000);
	 FILE *fpobjective3Dgnu;
	fpobjective3Dgnu = fopen("output\\Objective3D.gnu","w");
	fprintf(fpobjective3Dgnu,"set terminal jpeg size 1600,900 enhanced font calibri 20\n");
	fprintf(fpobjective3Dgnu,"set output 'output\\Objective3D.jpeg'\n");
	fprintf(fpobjective3Dgnu,"set title \"Energy production at the Awaji Island different sources\" font \"calibri,26\"\n");
	fprintf(fpobjective3Dgnu,"set xlabel \"Month\" font \"calibri,20\"\n");
	fprintf(fpobjective3Dgnu,"set ylabel \"Energy (MWh)\" font \"calibri,20\"\n");
	fprintf(fpobjective3Dgnu,"set data style linespoints\n");
	fprintf(fpobjective3Dgnu,"set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
	fprintf(fpobjective3Dgnu,"set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
	fprintf(fpobjective3Dgnu,"set xrange [0:13]\n");
	fprintf(fpobjective3Dgnu,"set yrange [0:22000]\n");
	fprintf(fpobjective3Dgnu,"set multiplot\n");
	fprintf(fpobjective3Dgnu,"plot 'output\\Objective3D.txt' using 1:2 title \"%d residental solar panels - %2.2f%%\",\\\n", 10000,ratio ); //houseRatio*amountOfHousehold
	fprintf(fpobjective3Dgnu,"	'output\\Objective3D.txt' using 1:3 title \"CEF+Kandens wind farm - %2.2f%%\",\\\n",ratioWind);
	fprintf(fpobjective3Dgnu,"	'output\\Objective3D.txt' using 1:4 title \"Kandens solar farm - %2.2f%%\",\\\n",ratioSolar);
	fprintf(fpobjective3Dgnu,"	'output\\Objective3D.txt' using 1:5 title \"%d private solar farms - %2.2f%%\",\\\n", privateSolarFarms.size(),(ratio2-ratio));
	fprintf(fpobjective3Dgnu,"	'output\\Objective3D.txt' using 1:6 title \"Consumption in 53075 houses\"\n");
	fprintf(fpobjective3Dgnu,"unset multiplot\n");
	fclose(fpobjective3Dgnu);
	
    FILE * gnuplotPipe8 = _popen ("gnuplot \"output\\Objective3D.gnu\"", "w"); _pclose( gnuplotPipe8 ); cout << ".";

	 
	 ///////////////////////////////////////////
	//generating gnu script file for agregated energy production
	////////////////////////////////////////////
	// int totalRatio = (int)(totalProdEnergyInAwajiIslandProducedAlsoPowerPlants*100/totalConsEnergyInAwajiIslandProducedAlsoPowerPlants);
	  double totalRatio = (totalProdEnergyInAwajiIslandProducedAlsoPowerPlants*100/(totalEnergyInAwajiIslandConsumed*1000)); //statistical data in MWH so multiplied by 1000 to kWH units
	 FILE *fpobjective3Egnu;
	fpobjective3Egnu = fopen("output\\Objective3E.gnu","w");
	fprintf(fpobjective3Egnu,"set terminal jpeg size 1600,900 enhanced font calibri 20\n");
	fprintf(fpobjective3Egnu,"set output 'output\\Objective3E.jpeg'\n");
	fprintf(fpobjective3Egnu,"set title \"Smart Grid at the Awaji Island - sufficiency ratio %2.2f%%\" font \"calibri,26\"\n",totalRatio);
	fprintf(fpobjective3Egnu,"set xlabel \"Month\" font \"calibri,20\"\n");
	fprintf(fpobjective3Egnu,"set ylabel \"Energy (MWh)\" font \"calibri,20\"\n");
	fprintf(fpobjective3Egnu,"set data style linespoints\n");
	fprintf(fpobjective3Egnu,"set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
	fprintf(fpobjective3Egnu,"set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0\n");
	fprintf(fpobjective3Egnu,"set xrange [0:13]\n");
	fprintf(fpobjective3Egnu,"set yrange [0:22000]\n");
	fprintf(fpobjective3Egnu,"set multiplot\n");
	fprintf(fpobjective3Egnu,"plot 'output\\Objective3E.txt' using 1:2 title \"Agregated energy production\",\\\n" );
	fprintf(fpobjective3Egnu,"	'output\\Objective3E.txt' using 1:3 title \"Consumption in 53075 house\"  linecolor rgbcolor \"blue\"\n");
	fprintf(fpobjective3Egnu,"unset multiplot\n");
	fclose(fpobjective3Egnu);
	
    FILE * gnuplotPipe7 = _popen ("gnuplot \"output\\Objective3E.gnu\"", "w");	_pclose( gnuplotPipe7 ); cout << "." <<endl<<endl;


	return 0;
}
