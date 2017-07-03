//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#include "UnitSimulationFramework.h"

void SimulateRateOfInterestForSolarPanels(double monthlyConsE)
{
	cout << "\n[ ] Perform simulation of Rate Of Interest of solar panels on 10 years period"<<endl;

	const int simYears = 10;
	const int simDays = simYears * 365; //10 years, 365 days per year
	const int forecasterNum=10;
	const int houseNum=6;

	Forecaster forecasterlist[10]={Forecaster(2003),Forecaster(2004),
								   Forecaster(2005),Forecaster(2006),
								   Forecaster(2007),Forecaster(2008),
								   Forecaster(2009),Forecaster(2010),
								   Forecaster(2011),Forecaster(2012)};
	
	Household houselist[6] = {Household(simDays,monthlyConsE,19.52, 0.1,3.0,367884),
						Household(simDays,monthlyConsE,26.03,0.1,4.0,494291),
						Household(simDays,monthlyConsE,34.16,0.1,5.0,622675),
						Household(simDays,monthlyConsE,39.04, 0.1,6.0,735768),
						Household(simDays,monthlyConsE,52.06, 0.1, 8.0, 988582),
						Household(simDays,monthlyConsE,68.32, 0.1, 10.0, 1245350)};

	double accountBalance[1+simYears*12][houseNum];
	
	for(int h=0;h<houseNum;h++)
		for(int m=0;m<121;m++)
			accountBalance[m][h]=0;

	for(int h=0;h<houseNum;h++)
		accountBalance[0][h] = -1 * houselist[h].producerUnit.price + houselist[h].producerUnit.CalculateSubsidy();

	for(int year=0;year<simYears;year++)
	{
		for(int day=1;day<=365;day++)
		{
			for(int hour=1;hour<=24;hour++)
			{
				Hour_Data currentWeather = forecasterlist[year].RequestWeather(day,hour);

				for(int houseId=0;houseId<houseNum;houseId++)
				{
					houselist[houseId].RequestToParticipate(day,hour,currentWeather,forecasterlist[year].RequestDailyFlux(day,hour));
					accountBalance[12*year+DayToMonth(day)][houseId] += houselist[houseId].AccountBalance[day][hour];
				}
			}
		}
	}
	
	for(int houseId=0;houseId<houseNum;houseId++)
	{
		for(int monthId=1;monthId<=120;monthId++)
		{
			accountBalance[monthId][houseId]+=accountBalance[monthId-1][houseId];
		}
	}

	FILE *fp;
	fp=fopen("output\\SolarPanelRateOfInterest.txt","w");
	
	for(int monthId=0;monthId<=120;monthId++)
		fprintf(fp,"%g	%g	%g	%g	%g	%g	%g\n", (double)monthId/12.0, accountBalance[monthId][0]/10000, accountBalance[monthId][1]/10000, accountBalance[monthId][2]/10000, accountBalance[monthId][3]/10000, accountBalance[monthId][4]/10000, accountBalance[monthId][5]/10000);
	
	fclose(fp);

	FILE * gnuplotPipe = _popen ("gnuplot \"config\\SolarPanelRateOfInterest.gnu\"", "w"); _pclose( gnuplotPipe ); 

	double ROI[houseNum];
	for(int h=0;h<houseNum;h++)
	{
		ROI[h]=((accountBalance[120][h]+houselist[h].producerUnit.price- houselist[h].producerUnit.CalculateSubsidy())/10)/(houselist[h].producerUnit.price- houselist[h].producerUnit.CalculateSubsidy());
	}
	cout << "Rate of Interest for 3kW solar panel is " << ROI[0]*100 <<"%" <<endl;
	cout << "Rate of Interest for 4kW solar panel is " << ROI[1]*100 <<"%" <<endl;
	cout << "Rate of Interest for 5kW solar panel is " << ROI[2]*100 <<"%" <<endl;
	cout << "Rate of Interest for 6kW solar panel is " << ROI[3]*100 <<"%" <<endl;
	cout << "Rate of Interest for 8kW solar panel is " << ROI[4]*100 <<"%" <<endl;
	cout << "Rate of Interest for 10kW solar panel is " << ROI[5]*100 <<"%" <<endl;

}


void SimulateRateOfInterestForSolarFarm(double monthlyConsE)
{
	cout << "\n[ ] Perform simulation of Rate Of Interest of solar farm on 10 years period"<<endl;

	const int simYears = 10;
	const int simDays = simYears * 365; //10 years, 365 days per year
	const int forecasterNum=10;
	const int houseNum=1;

	Forecaster forecasterlist[10]={Forecaster(2003),Forecaster(2004),
								   Forecaster(2005),Forecaster(2006),
								   Forecaster(2007),Forecaster(2008),
								   Forecaster(2009),Forecaster(2010),
								   Forecaster(2011),Forecaster(2012)};
	
	Household houselist[1] = {Household(simDays,monthlyConsE,500.0,0.1,70,12800883)};
	double bankMonthlyPayment=132666.31;
	//Household houselist[1] = {Household(simDays,monthlyConsE,1000.0,0.1,140,25601766)}; //to verify if twice bigger area has the same ROI ->yes
	//bankMonthlyPayment *= 2;

	double accountBalance[1+simYears*12][houseNum];
	
	for(int h=0;h<houseNum;h++)
		for(int m=0;m<121;m++)
			accountBalance[m][h]=0;

	for(int h=0;h<houseNum;h++)
		accountBalance[0][h] = -1 * houselist[h].producerUnit.price + houselist[h].producerUnit.CalculateSubsidy();

	for(int year=0;year<simYears;year++)
	{
		for(int day=1;day<=365;day++)
		{
			for(int hour=1;hour<=24;hour++)
			{
				Hour_Data currentWeather = forecasterlist[year].RequestWeather(day,hour);

				for(int houseId=0;houseId<houseNum;houseId++)
				{
					houselist[houseId].RequestToParticipate(day,hour,currentWeather,forecasterlist[year].RequestDailyFlux(day,hour));
					accountBalance[12*year+DayToMonth(day)][houseId] += houselist[houseId].AccountBalance[day][hour];
				}
			}
		}
	}
	double bankCase[121],avgIncome=0,avgIncomeBank=0;
	bankCase[0]=0;
	for(int i=1;i<=120;i++)
	{
		avgIncome+=accountBalance[i][0];
		bankCase[i]=bankCase[i-1]+accountBalance[i][0]-bankMonthlyPayment;
	}
	avgIncome/=120;
	avgIncomeBank=avgIncome-bankMonthlyPayment;
	
	for(int houseId=0;houseId<houseNum;houseId++)
	{
		for(int monthId=1;monthId<=120;monthId++)
		{
			accountBalance[monthId][houseId]+=accountBalance[monthId-1][houseId];
		}
	}

	FILE *fp;
	fp=fopen("output\\SolarFarmRateOfInterest.txt","w");
	
	for(int monthId=0;monthId<=120;monthId++)
		fprintf(fp,"%g	%g	%g\n", (double)monthId/12.0, accountBalance[monthId][0]/10000,bankCase[monthId]/10000);
	
	fclose(fp);

	FILE * gnuplotPipe = _popen ("gnuplot \"config\\SolarFarmRateOfInterest.gnu\"", "w"); _pclose( gnuplotPipe ); 

	double ROI[houseNum];
	for(int h=0;h<houseNum;h++)
	{
		ROI[h]=((accountBalance[120][h]+houselist[h].producerUnit.price- houselist[h].producerUnit.CalculateSubsidy())/10)/(houselist[h].producerUnit.price- houselist[h].producerUnit.CalculateSubsidy());
	}
	double ROIbank = (bankCase[120]/10)/(houselist[0].producerUnit.price- houselist[0].producerUnit.CalculateSubsidy());
	
	cout << "ROI for 73kW solar farm is " << ROI[0]*100 <<"% average monthly profit " <<avgIncome << "yen"<<endl;
	cout << "ROI for 73kW solar farm with 4.5% loan is " << ROIbank*100 <<"% avg monthly profit " << avgIncomeBank << "yen"<<endl<<endl;

}



void SimulateRateOfInterestForWindTurbines(double monthlyConsE)
{
	cout << "\n[ ] Perform simulation of Rate Of Interest of wind turbines on 10 years period"<<endl;

	const int simYears = 10;
	const int simDays = simYears * 365; //10 years, 365 days per year
	const int forecasterNum=10;
	const int houseNum=3;

	Forecaster forecasterlist[10]={Forecaster(2003),Forecaster(2004),
								   Forecaster(2005),Forecaster(2006),
								   Forecaster(2007),Forecaster(2008),
								   Forecaster(2009),Forecaster(2010),
								   Forecaster(2011),Forecaster(2012)};
	
	Household houselist[3] = {Household(simDays,monthlyConsE,12,5.0,1693575),
						Household(simDays,monthlyConsE,15,10.0,2972065),
						Household(simDays,monthlyConsE,18,20.0,4196954)};

	double accountBalance[1+simYears*12][houseNum];
	
	for(int h=0;h<houseNum;h++)
		for(int m=0;m<121;m++)
			accountBalance[m][h]=0;

	for(int h=0;h<houseNum;h++)
		accountBalance[0][h] = -1 * houselist[h].producerUnit.price + houselist[h].producerUnit.CalculateSubsidy();

	for(int year=0;year<simYears;year++)
	{
		for(int day=1;day<=365;day++)
		{
			for(int hour=1;hour<=24;hour++)
			{
				Hour_Data currentWeather = forecasterlist[year].RequestWeather(day,hour);

				for(int houseId=0;houseId<houseNum;houseId++)
				{
					houselist[houseId].RequestToParticipate(day,hour,currentWeather,forecasterlist[year].RequestDailyFlux(day,hour));
					accountBalance[12*year+DayToMonth(day)][houseId] += houselist[houseId].AccountBalance[day][hour];
				}
			}
		}
	}
	
	for(int houseId=0;houseId<houseNum;houseId++)
	{
		for(int monthId=1;monthId<=120;monthId++)
		{
			accountBalance[monthId][houseId]+=accountBalance[monthId-1][houseId];
		}
	}


	FILE *fp;
	fp=fopen("output\\WindTurbineRateOfInterest.txt","w");
	
	for(int monthId=0;monthId<=120;monthId++)
		fprintf(fp,"%g	%g	%g	%g\n", (double)monthId/12.0, accountBalance[monthId][0]/10000, accountBalance[monthId][1]/10000, accountBalance[monthId][2]/10000);
	
	fclose(fp);

	FILE * gnuplotPipe = _popen ("gnuplot \"config\\WindTurbineRateOfInterest.gnu\"", "w"); _pclose( gnuplotPipe ); 

	double ROI[houseNum];
	for(int h=0;h<houseNum;h++)
	{
		ROI[h]=((accountBalance[120][h]+houselist[h].producerUnit.price- houselist[h].producerUnit.CalculateSubsidy())/10)/(houselist[h].producerUnit.price- houselist[h].producerUnit.CalculateSubsidy());
	}
	cout << "Rate of Interest for 12kW wind turbine is " << ROI[0]*100 <<"%" <<endl;
	cout << "Rate of Interest for 15kW wind turbine is " << ROI[1]*100 <<"%" <<endl;
	cout << "Rate of Interest for 20kW wind turbine is " << ROI[2]*100 <<"%" <<endl;

}

void SimulateSingleSolarPanelUnit(double monthlyConsE)
{
	cout << "\n[ ] Perform simulation of single solar panel\n";

	Forecaster f2008(2008); 
	Forecaster f2009(2009); 
	Forecaster f2010(2010); 
	Forecaster f2011(2011); 
	Forecaster f1(2012);

	int simDays=365;
	//3kW Producer(19.52, 0.1,3.0,367884);
	//4kW Producer(26.03,0.1,4.0,494291);
	//5kW Producer(34.16,0.1,5.0,622675);
	//2x3kW Producer(39.04, 0.1,6.0,735768);
	//2x4kW Producer (52.06, 0.1, 8.0, 988582);
	//2x10KW Producer(68.32, 0.1, 10.0, 1245350);
	
	Household h1(simDays,monthlyConsE,26.03,0.1,4.0,494291); //solar panel 4kW having 26m2 area and efficiency ratio 10%
	//Household h1(simDays,monthlyConsE,19.52,0.1,3.0,367884); //solar panel 3kW having 19.5m2 area and efficiency ratio 10%
	//Household h1(simDays,monthlyConsE,68.32, 0.1, 10.0, 1245350); //10kW

	Household hlist[6] = {Household(simDays,monthlyConsE,19.52, 0.1,3.0,367884),
						Household(simDays,monthlyConsE,26.03,0.1,4.0,494291),
						Household(simDays,monthlyConsE,34.16,0.1,5.0,622675),
						Household(simDays,monthlyConsE,39.04, 0.1,6.0,735768),
						Household(simDays,monthlyConsE,52.06, 0.1, 8.0, 988582),
						Household(simDays,monthlyConsE,68.32, 0.1, 10.0, 1245350)};
	
	FILE *fp, *fpd, *fpdab, *fpdavg, *fpdavgab, *fpm, *fpmab, *fpmie, *fpy, *fpyab, *fpyie,*fpy6,*fpyab6,*fpavg;

	double sumAvgDayAb=0,sumOneDayAb=0,sumOneMonthAb=0,SumOneYearProd=0,SumOneYearCons=0,SumOneYearAb=0;
	double monthlyEnergyProduction[13];
	double monthlyEnergyConsumption[13];
	double monthlyAccountBalance[13];
	double listMonthlyEnergyProduction[13][6];
	double listMonthlyAccountBalance[13][6];
	double avgAcountBalanceDaily[25];
	double avgEnergyDaily[25];
	double expenseMonthly[13];
	double incomeMonthly[13];
	double fluxOfInsolationMax[13];
	double fluxOfInsolation[13];
	double fluxOfInsolation2008[13];
	double fluxOfInsolation2009[13];
	double fluxOfInsolation2010[13];
	double fluxOfInsolation2011[13];

	Hour_Data currentWeather;
	
	for(int i=0;i<13;i++)
		expenseMonthly[i]=incomeMonthly[i]=monthlyAccountBalance[i]=fluxOfInsolation[i]=fluxOfInsolation2008[i]=fluxOfInsolation2009[i]=fluxOfInsolation2010[i]=fluxOfInsolation2011[i]=fluxOfInsolationMax[i]=monthlyEnergyProduction[i]=monthlyEnergyConsumption[i]=0; //monthlyIncome
	
	for(int i=0;i<13;i++)
		for(int j=0;j<6;j++)
			listMonthlyEnergyProduction[i][j]=listMonthlyAccountBalance[i][j]=0;

	for(int i=1;i<25;i++)
		avgEnergyDaily[i]=avgAcountBalanceDaily[i]=0;
	
	if(NULL == ( fpd=fopen("output\\SolarPanelUnitTest-one-day.txt","w")))
	{
			printf("error creating file SolarPanelUnitTest-one-day.txt\n") ;
	}
	fpdab=fopen("output\\SolarPanelUnitTest-one-day-ab.txt","w");
	fpdavg=fopen("output\\SolarPanelUnitTest-avg-day.txt","w");
	fpdavgab=fopen("output\\SolarPanelUnitTest-avg-day-ab.txt","w");
	fpm=fopen("output\\SolarPanelUnitTest-one-month.txt","w");
	fpmab=fopen("output\\SolarPanelUnitTest-one-month-ab.txt","w");
	fpmie=fopen("output\\SolarPanelUnitTest-one-month-ie.txt","w");
	fpy=fopen("output\\SolarPanelUnitTest-one-year.txt","w");
	fpy6=fopen("output\\SolarPanelUnitTest-one-year-6.txt","w");
	fpyab=fopen("output\\SolarPanelUnitTest-one-year-ab.txt","w");
	fpyab6=fopen("output\\SolarPanelUnitTest-one-year-ab-6.txt","w");
	fpyie=fopen("output\\SolarPanelUnitTest-one-year-ie.txt","w");
	fp=fopen("output\\SolarPanelUnitTest-function.txt","w");
	fpavg=fopen("output\\SolarPanelUnitTest-function-avg.txt","w");
	
	cout << "[ ] computing"<<endl;
	for (int dayId=1;dayId<=simDays;dayId++)
	{
		for(int hour = 1;hour<=24;hour++)
		{
			
			currentWeather = f1.RequestWeather(dayId,hour);
			h1.RequestToParticipate(dayId,hour,currentWeather,f1.RequestDailyFlux(dayId,hour));
			for(int house=0;house<6;house++)
				hlist[house].RequestToParticipate(dayId,hour,currentWeather, f1.RequestDailyFlux(dayId,hour));

			fluxOfInsolationMax[DayToMonth(dayId)]+=f1.RequestDailyFlux(dayId,hour);
			fluxOfInsolation[DayToMonth(dayId)]+=f1.RequestDailyFlux(dayId,hour)*currentWeather.solarTime;

			//comparision flux 2008-2011
			fluxOfInsolation2008[DayToMonth(dayId)]+=f2008.RequestDailyFlux(dayId,hour)*f2008.RequestWeather(dayId,hour).solarTime;
			fluxOfInsolation2009[DayToMonth(dayId)]+=f2009.RequestDailyFlux(dayId,hour)*f2009.RequestWeather(dayId,hour).solarTime;
			fluxOfInsolation2010[DayToMonth(dayId)]+=f2010.RequestDailyFlux(dayId,hour)*f2010.RequestWeather(dayId,hour).solarTime;
			fluxOfInsolation2011[DayToMonth(dayId)]+=f2011.RequestDailyFlux(dayId,hour)*f2011.RequestWeather(dayId,hour).solarTime;

			if(dayId==102)
			{ 
				sumOneDayAb+=h1.AccountBalance[dayId][hour];
				fprintf(fpd,"%d	%g	%g\n",hour, h1.SellEnergy[dayId][hour],h1.BuyEnergy[dayId][hour]);
				fprintf(fpdab,"%d	%g\n",hour,h1.AccountBalance[dayId][hour]);
			}
			avgEnergyDaily[hour]+= h1.SellEnergy[dayId][hour];
			avgAcountBalanceDaily[hour]+=h1.AccountBalance[dayId][hour];

			monthlyEnergyConsumption[DayToMonth(dayId)] += h1.BuyEnergy[dayId][hour];
			monthlyEnergyProduction[DayToMonth(dayId)] += h1.SellEnergy[dayId][hour];
			monthlyAccountBalance[DayToMonth(dayId)] += h1.AccountBalance[dayId][hour];
			for(int house=0;house<6;house++)
			{
				listMonthlyEnergyProduction[DayToMonth(dayId)][house] += hlist[house].SellEnergy[dayId][hour];
				listMonthlyAccountBalance[DayToMonth(dayId)][house] += hlist[house].AccountBalance[dayId][hour];
			}

		}

		expenseMonthly[DayToMonth(dayId)] += h1.Expense[dayId];
		incomeMonthly[DayToMonth(dayId)] += h1.Income[dayId];

		if(DayToMonth(dayId)==7)
		{
			//todays acount balance & todays production
			double tab=0,tprod=0,tcons=0;
			for(int h=1;h<=24;h++)
			{
				tcons += h1.BuyEnergy[dayId][h];
				tprod += h1.SellEnergy[dayId][h];
				tab += h1.AccountBalance[dayId][h];
			}
			
			sumOneMonthAb+=tab;
			fprintf(fpm, "%d	%g	%g\n",dayId-181,tprod,tcons); //181 is dayOfYear for June 31, so counting starts from 1
			fprintf(fpmab,"%d	%g\n",dayId-181,tab);
			fprintf(fpmie,"%d	%g	%g\n", dayId-181, h1.Income[dayId], h1.Expense[dayId]);
		}
	}

	cout << "[+] saving results and generating graphs";

	for(int i=1;i<=12;i++)
	{
		SumOneYearProd+=monthlyEnergyProduction[i];
		SumOneYearCons+=monthlyEnergyConsumption[i];
		SumOneYearAb+=monthlyAccountBalance[i];
		fprintf(fpyie,"%d	%g	%g\n", i, incomeMonthly[i], expenseMonthly[i]);
		fprintf(fpyab,"%d	%g\n", i, monthlyAccountBalance[i]);
		fprintf(fpyab6, "%d	%g	%g	%g	%g	%g	%g\n", i, listMonthlyAccountBalance[i][0], listMonthlyAccountBalance[i][1], listMonthlyAccountBalance[i][2], listMonthlyAccountBalance[i][3], listMonthlyAccountBalance[i][4], listMonthlyAccountBalance[i][5]);
		fprintf(fpavg,"%d	%g	%g\n",i, fluxOfInsolationMax[i], 0.2*(fluxOfInsolation[i]+fluxOfInsolation2011[i]+fluxOfInsolation2010[i]+fluxOfInsolation2009[i]+fluxOfInsolation2008[i]));
		fprintf(fp,"%d	%g	%g	%g	%g	%g	%g\n",i, fluxOfInsolationMax[i], fluxOfInsolation2008[i], fluxOfInsolation2009[i], fluxOfInsolation2010[i], fluxOfInsolation2011[i], fluxOfInsolation[i]);
		fprintf(fpy,"%d	%g	%g\n",i,monthlyEnergyProduction[i],monthlyEnergyConsumption[i]);
		fprintf(fpy6, "%d	%g	%g	%g	%g	%g	%g	%g\n", i, listMonthlyEnergyProduction[i][0], listMonthlyEnergyProduction[i][1], listMonthlyEnergyProduction[i][2], listMonthlyEnergyProduction[i][3], listMonthlyEnergyProduction[i][4], listMonthlyEnergyProduction[i][5],monthlyEnergyConsumption[i]);
	}

	for(int i=1;i<=24;i++)
	{
		sumAvgDayAb+=avgAcountBalanceDaily[i]/simDays;
		fprintf(fpdavgab,"%d	%g\n", i, avgAcountBalanceDaily[i]/simDays);
		fprintf(fpdavg, "%d	%g	%g\n", i,avgEnergyDaily[i]/simDays,h1.BuyEnergy[1][i]);
	}
	
	fclose(fp); 
	fclose(fpdab);
	fclose(fpdavg);
	fclose(fpdavgab);
	fclose(fpd);
	fclose(fpdab);
	fclose(fpm);
	fclose(fpmab);
	fclose(fpmie);
	fclose(fpy);
	fclose(fpy6);
	fclose(fpyab);
	fclose(fpyab6);
	fclose(fpyie);
	fclose(fpavg);
	
	FILE * gnuplotPipe = _popen ("gnuplot \"config\\SolarPanelUnitTest-function.gnu\"", "w");      _pclose( gnuplotPipe );  cout << ".";
    FILE * gnuplotPipe0 = _popen ("gnuplot \"config\\SolarPanelUnitTest-one-day.gnu\"", "w");      _pclose( gnuplotPipe0 ); cout << ".";
    FILE * gnuplotPipe1 = _popen ("gnuplot \"config\\SolarPanelUnitTest-avg-day.gnu\"", "w");      _pclose( gnuplotPipe1 ); cout << ".";
    FILE * gnuplotPipe2 = _popen ("gnuplot \"config\\SolarPanelUnitTest-one-month.gnu\"", "w");    _pclose( gnuplotPipe2 ); cout << ".";
    FILE * gnuplotPipe3 = _popen ("gnuplot \"config\\SolarPanelUnitTest-one-year.gnu\"", "w");     _pclose( gnuplotPipe3 ); cout << ".";
    FILE * gnuplotPipe4 = _popen ("gnuplot \"config\\SolarPanelUnitTest-one-day-ab.gnu\"", "w");   _pclose( gnuplotPipe4 ); cout << ".";
	FILE * gnuplotPipe5 = _popen ("gnuplot \"config\\SolarPanelUnitTest-avg-day-ab.gnu\"", "w");   _pclose( gnuplotPipe5 ); cout << ".";
	FILE * gnuplotPipe6 = _popen ("gnuplot \"config\\SolarPanelUnitTest-one-month-ab.gnu\"", "w"); _pclose( gnuplotPipe6 ); cout << ".";
	FILE * gnuplotPipe7 = _popen ("gnuplot \"config\\SolarPanelUnitTest-one-year-ab.gnu\"", "w");  _pclose( gnuplotPipe7 ); cout << ".";
	FILE * gnuplotPipe8 = _popen ("gnuplot \"config\\SolarPanelUnitTest-one-month-ie.gnu\"", "w");  _pclose( gnuplotPipe8 ); cout << ".";
	FILE * gnuplotPipe9 = _popen ("gnuplot \"config\\SolarPanelUnitTest-one-year-ie.gnu\"", "w");  _pclose( gnuplotPipe9 ); cout << ".";
    FILE * gnuplotPipe10 = _popen ("gnuplot \"config\\SolarPanelUnitTest-one-year-6.gnu\"", "w");     _pclose( gnuplotPipe10 ); cout << ".";
	FILE * gnuplotPipe11 = _popen ("gnuplot \"config\\SolarPanelUnitTest-one-year-ab-6.gnu\"", "w");  _pclose( gnuplotPipe11 ); cout << ".";
	FILE * gnuplotPipe12 = _popen ("gnuplot \"config\\SolarPanelUnitTest-function-avg.gnu\"", "w");      _pclose( gnuplotPipe12 ); cout << "." <<endl;
	
	cout << "[+] SolarPanelUnitTest-avg-day-ab.jpeg total value " << sumAvgDayAb <<" yen\n";
	cout << "[+] SolarPanelUnitTest-one-day-ab.jpeg total value " << sumOneDayAb <<" yen\n";
	cout << "[+] SolarPanelUnitTest-one-month-ab.jpeg total value " << sumOneMonthAb <<" yen\n";
	cout << "[+] SolarPanelUnitTest-one-year.jpeg total production " << SumOneYearProd <<" kWh\n";
	cout << "[+] SolarPanelUnitTest-one-year.jpeg total consumption " << SumOneYearCons <<" kWh\n";
	cout << "[+] SolarPanelUnitTest-one-year-ab.jpeg total account balance " << SumOneYearAb <<" yen\n";
}

void SimulateSingleWindTurbineUnit(double monthlyConsE)
{
	cout << "\n[ ] Perform simulation of single wind turbine\n";

	int simDays = 365;
	 Forecaster f1(2012);
	//Household h1(simDays,monthlyConsE,80,2000.0,2972065); //kanden's wind turbine 2000kW tower 80m ->2017–œkWh yearly produced by 6 units
	Household h1(simDays,monthlyConsE,18,20.0,4196954);

	Household hlist[3] = {Household(simDays,monthlyConsE,12,5.0,1693575),
						Household(simDays,monthlyConsE,15,10.0,2972065),
						Household(simDays,monthlyConsE,18,20.0,4196954)};

	FILE *fpd, *fpdab, *fpdavg, *fpdavgab, *fpm, *fpmab, *fpmie, *fpy, *fpyab, *fpyie,*fpy3,*fpyab3;
	//FILE *fpfunction;
	
	double sumAvgDayAb=0,sumOneDayAb=0,sumOneMonthAb=0,SumOneYearProd=0,SumOneYearCons=0,SumOneYearAb=0;
	double monthlyEnergyProduction[13];
	double monthlyEnergyConsumption[13];
	double monthlyAccountBalance[13];
	double listMonthlyEnergyProduction[13][3];
	double listMonthlyAccountBalance[13][3];
	double expenseMonthly[13];
	double incomeMonthly[13];
	double avgEnergyDaily[25];
	double avgAcountBalanceDaily[25];
	int monthlySaveDayCounter=1;
	

	for(int i=0;i<13;i++)
		incomeMonthly[i]=expenseMonthly[i]=monthlyAccountBalance[i]=monthlyEnergyProduction[i]=monthlyEnergyConsumption[i]=0;
	
	for(int i=1;i<25;i++)
		avgAcountBalanceDaily[i]=avgEnergyDaily[i]=0;

	for(int i=0;i<13;i++)
		for(int j=0;j<3;j++)
			listMonthlyEnergyProduction[i][j]=listMonthlyAccountBalance[i][j]=0;

	
	if(NULL == (fpd=fopen("output\\WindTurbineUnitTest-one-day.txt","w")))
	{
		printf("error creating file WindTurbineUnitTest-one-day.txt\n") ;
	}
	fpdab=fopen("output\\WindTurbineUnitTest-one-day-ab.txt","w");
	fpdavg=fopen("output\\WindTurbineUnitTest-avg-day.txt","w");
	fpdavgab=fopen("output\\WindTurbineUnitTest-avg-day-ab.txt","w");
	fpm=fopen("output\\WindTurbineUnitTest-one-month.txt","w");
	fpmab=fopen("output\\WindTurbineUnitTest-one-month-ab.txt","w");
	fpmie=fopen("output\\WindTurbineUnitTest-one-month-ie.txt","w");
	fpy=fopen("output\\WindTurbineUnitTest-one-year.txt","w");
	fpy3=fopen("output\\WindTurbineUnitTest-one-year-3.txt","w");
	fpyab=fopen("output\\WindTurbineUnitTest-one-year-ab.txt","w");
	fpyab3=fopen("output\\WindTurbineUnitTest-one-year-ab-3.txt","w");
	fpyie=fopen("output\\WindTurbineUnitTest-one-year-ie.txt","w");
	//fpfunction=fopen("output\\WindTurbineUnitTest-function.txt","w");

	
	cout << "[ ] computing"<<endl;
	for (int dayId=1;dayId<=simDays;dayId++)
	{
		for(int hour = 1;hour<=24;hour++)
		{
			Hour_Data currentWeather = f1.RequestWeather(dayId,hour);
			h1.RequestToParticipate(dayId,hour,currentWeather,f1.RequestDailyFlux(dayId,hour));
			for(int house=0;house<3;house++)
				hlist[house].RequestToParticipate(dayId,hour,currentWeather, f1.RequestDailyFlux(dayId,hour));

			if(dayId==102)
			{
				sumOneDayAb += h1.AccountBalance[dayId][hour];
				fprintf(fpd,"%d	%g	%g\n",hour, h1.SellEnergy[dayId][hour],h1.BuyEnergy[dayId][hour]);
				fprintf(fpdab,"%d	%g\n",hour,h1.AccountBalance[dayId][hour]);
			}

			avgEnergyDaily[hour]+= h1.SellEnergy[dayId][hour];
			avgAcountBalanceDaily[hour]+=h1.AccountBalance[dayId][hour];
			
			monthlyEnergyConsumption[DayToMonth(dayId)] += h1.BuyEnergy[dayId][hour];
			monthlyEnergyProduction[DayToMonth(dayId)] += h1.SellEnergy[dayId][hour];
			monthlyAccountBalance[DayToMonth(dayId)] += h1.AccountBalance[dayId][hour];

			for(int house=0;house<3;house++)
			{
				listMonthlyEnergyProduction[DayToMonth(dayId)][house] += hlist[house].SellEnergy[dayId][hour];
				listMonthlyAccountBalance[DayToMonth(dayId)][house] += hlist[house].AccountBalance[dayId][hour];
			}
		}
		
		expenseMonthly[DayToMonth(dayId)] += h1.Expense[dayId];
		incomeMonthly[DayToMonth(dayId)] += h1.Income[dayId];

		if(DayToMonth(dayId)==7)
		{
			//todays acount balance & todays production
			double tab=0,tprod=0,tcons=0;
			for(int h=1;h<=24;h++)
			{
				tcons += h1.BuyEnergy[dayId][h];
				tprod += h1.SellEnergy[dayId][h];
				tab += h1.AccountBalance[dayId][h];
			}
			
			sumOneMonthAb+=tab;
			fprintf(fpm, "%d	%g	%g\n",dayId-181,tprod,tcons); //181 is dayOfYear for June 31, so counting starts from 1
			fprintf(fpmab,"%d	%g\n",dayId-181,tab);
			fprintf(fpmie,"%d	%g	%g\n", dayId-181, h1.Income[dayId], h1.Expense[dayId]);
		}
	}


	cout << "[+] saving results and generating graphs";

	//for(int testWindSpeed=0; testWindSpeed<= 25; testWindSpeed++)	//graph of power curve 
	//	fprintf(fpfunction,"%d	%g\n",testWindSpeed, h1.producerUnit.CalculateWindPower2(testWindSpeed));
	
	for(int i=1;i<=24;i++)
	{
		sumAvgDayAb+=avgAcountBalanceDaily[i]/simDays;
		fprintf(fpdavgab,"%d	%g\n", i, avgAcountBalanceDaily[i]/simDays);
		fprintf(fpdavg, "%d	%g	%g\n", i,avgEnergyDaily[i]/simDays,h1.BuyEnergy[1][i]);
	}

	for(int i=1;i<=12;i++)
	{
		SumOneYearProd+=monthlyEnergyProduction[i];
		SumOneYearCons+=monthlyEnergyConsumption[i];
		SumOneYearAb+=monthlyAccountBalance[i];
		fprintf(fpyab,"%d	%g\n", i, monthlyAccountBalance[i]);
		fprintf(fpyab3, "%d	%g	%g	%g\n", i, listMonthlyAccountBalance[i][0], listMonthlyAccountBalance[i][1], listMonthlyAccountBalance[i][2]);
		fprintf(fpy,"%d	%g	%g\n",i,monthlyEnergyProduction[i],monthlyEnergyConsumption[i]);
		fprintf(fpy3, "%d	%g	%g	%g	%g\n", i, listMonthlyEnergyProduction[i][0], listMonthlyEnergyProduction[i][1], listMonthlyEnergyProduction[i][2],monthlyEnergyConsumption[i]);
		fprintf(fpyie,"%d	%g	%g\n", i, incomeMonthly[i], expenseMonthly[i]);
	}
	
	fclose(fpd);
	fclose(fpdab); 
	fclose(fpdavg); 
	fclose(fpdavgab); 
	fclose(fpm);
	fclose(fpmab); 
	fclose(fpmie); 
	fclose(fpy);
	fclose(fpy3); 
	fclose(fpyab); 
	fclose(fpyab3); 
	fclose(fpyie);
	//fclose(fpfunction);
	
    //FILE * gnuplotPipe = _popen ("gnuplot \"config\\WindTurbineUnitTest-function.gnu\"", "w"); _pclose( gnuplotPipe ); cout << ".";
    FILE * gnuplotPipe0 = _popen ("gnuplot \"config\\WindTurbineUnitTest-one-day.gnu\"", "w"); _pclose( gnuplotPipe0 ); cout << ".";
    FILE * gnuplotPipe1 = _popen ("gnuplot \"config\\WindTurbineUnitTest-avg-day.gnu\"", "w"); _pclose( gnuplotPipe1 ); cout << ".";
    FILE * gnuplotPipe2 = _popen ("gnuplot \"config\\WindTurbineUnitTest-one-month.gnu\"", "w"); _pclose( gnuplotPipe2 ); cout << ".";
    FILE * gnuplotPipe3 = _popen ("gnuplot \"config\\WindTurbineUnitTest-one-year.gnu\"", "w"); _pclose( gnuplotPipe3 ); cout << ".";
    FILE * gnuplotPipe4 = _popen ("gnuplot \"config\\WindTurbineUnitTest-one-day-ab.gnu\"", "w"); _pclose( gnuplotPipe4 ); cout << ".";
    FILE * gnuplotPipe5 = _popen ("gnuplot \"config\\WindTurbineUnitTest-avg-day-ab.gnu\"", "w"); _pclose( gnuplotPipe5 ); cout << ".";
    FILE * gnuplotPipe6 = _popen ("gnuplot \"config\\WindTurbineUnitTest-one-month-ab.gnu\"", "w"); _pclose( gnuplotPipe6 ); cout << ".";
    FILE * gnuplotPipe7 = _popen ("gnuplot \"config\\WindTurbineUnitTest-one-year-ab.gnu\"", "w"); _pclose( gnuplotPipe7 ); cout << ".";
    FILE * gnuplotPipe8 = _popen ("gnuplot \"config\\WindTurbineUnitTest-one-month-ie.gnu\"", "w"); _pclose( gnuplotPipe8 ); cout << ".";
    FILE * gnuplotPipe9 = _popen ("gnuplot \"config\\WindTurbineUnitTest-one-year-ie.gnu\"", "w"); _pclose( gnuplotPipe9 ); cout << ".";
    FILE * gnuplotPipe10 = _popen ("gnuplot \"config\\WindTurbineUnitTest-one-year-3.gnu\"", "w"); _pclose( gnuplotPipe10 ); cout << ".";
    FILE * gnuplotPipe11 = _popen ("gnuplot \"config\\WindTurbineUnitTest-one-year-ab-3.gnu\"", "w"); _pclose( gnuplotPipe11 ); cout << "." <<endl;
	
	cout << "[+] WindTurbineUnitTest-avg-day-ab.jpeg total value " << sumAvgDayAb <<" yen\n";
	cout << "[+] WindTurbineUnitTest-one-day-ab.jpeg total value " << sumOneDayAb <<" yen\n";
	cout << "[+] WindTurbineUnitTest-one-month-ab.jpeg total value " << sumOneMonthAb <<" yen\n";
	cout << "[+] WindTurbineUnitTest-one-year.jpeg total production " << SumOneYearProd <<" kWh\n";
	cout << "[+] WindTurbineUnitTest-one-year.jpeg total consumption " << SumOneYearCons <<" kWh\n";
	cout << "[+] WindTurbineUnitTest-one-year-ab.jpeg total account balance " << SumOneYearAb <<" yen\n";
}

void TestDistrubutionFunction(int count, int mu, int sigma)
{
	FILE *fp;
	fp=fopen("output\\TestDistributionFunction.txt","w");
	vector<double> dist;
	dist.clear();
	for(double i=0;i<2*mu;i+=(2*mu/count))
		dist.push_back(randn_trig(mu,sigma));
	
	std::sort(dist.begin(), dist.end());
	
	int k=0;
	for(double i=0;i<2*mu;i+=(2*mu/count),k++)
		fprintf(fp, "%g	%g\n", i,dist[k]);
	fclose(fp);
	
    FILE * gnuplotPipe7 = _popen ("gnuplot \"config\\TestDistributionFunction.gnu\"", "w");
	 _pclose( gnuplotPipe7 );
}