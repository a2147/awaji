//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#include "Forecaster.h"
#include "StdOps.h"
#include "Flux.h"


int Forecaster::download(int id, int day, int month, int year)
{
	try
	{
		stringstream link;
		link << "http://www.data.jma.go.jp/obd/stats/etrn/view/hourly_s1.php?prec_no=63&block_no=47776&year=" 
			<< year << "&month=" << month << "&day=" << day << "&view=";
		URI uri(link.str());
		HTTPClientSession session(uri.getHost(), uri.getPort());
		session.setProxy("px1.ai.u-hyogo.ac.jp",8080);

		// prepare path
		string path(uri.getPathAndQuery());
		if (path.empty()) path = "/";

		// send request
		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		session.sendRequest(req);

		// get response
		HTTPResponse res;
	
		// print response
		istream &is = session.receiveResponse(res);
		std::string htmldata;
		StreamCopier::copyToString(is,htmldata);
	
		istringstream iss(htmldata);
		vector<string> tokens;
		vector<string> weatherEveryHour;
		vector<string> weatherEveryHourSplit;
		split( weatherEveryHour, htmldata, "<tr class=\"mtx\" style=\"text-align:right;\">" );

		//cutting off metadata from the last position
		weatherEveryHour[24] = weatherEveryHour[24].substr(0,weatherEveryHour[23].length());
		Hour_Data todayWeather[25];

		for(int i=1; i<=24;i++)
		{
		weatherEveryHourSplit.clear();
		split(weatherEveryHourSplit,weatherEveryHour[i],"<td class=\"data_0_0\">");

		//todayWeather[i].pressure = string_to_double(weatherEveryHourSplit[1].substr(0,weatherEveryHourSplit[1].find('<')));
		todayWeather[i].temp =string_to_double(weatherEveryHourSplit[4].substr(0,weatherEveryHourSplit[4].find('<')));
		todayWeather[i].windSpeed = string_to_double(weatherEveryHourSplit[8].substr(0,weatherEveryHourSplit[8].find('<')));
		todayWeather[i].solarTime = string_to_double(weatherEveryHourSplit[9].substr(0,weatherEveryHourSplit[9].find('<')));

		//downloadedWeather[id][i].pressure = string_to_double(weatherEveryHourSplit[1].substr(0,weatherEveryHourSplit[1].find('<')));
		downloadedWeather[id][i].temp =string_to_double(weatherEveryHourSplit[4].substr(0,weatherEveryHourSplit[4].find('<')));
		downloadedWeather[id][i].windSpeed = string_to_double(weatherEveryHourSplit[8].substr(0,weatherEveryHourSplit[8].find('<')));
		downloadedWeather[id][i].solarTime = string_to_double(weatherEveryHourSplit[9].substr(0,weatherEveryHourSplit[9].find('<')));
	}
	
	return 0;
}
  catch (Exception &ex)
  {
    cerr << ex.displayText() << endl;
    return -1;
  }
  return 0;
}

//constructor
Forecaster::Forecaster(int year)
{
	int maxdays = 365;
	//“úŽË—Ê
	Flux = CalculateFluxOfSolarRadiation();

	int downloadedCount = 0; //downloaded days
	downloadedWeather = createHourDataMatrix(maxdays+1,25);
	//downloadedWeather

	//calculate random year between 1990 - 2010 (in order to download data)
	//srand ( (unsigned)time(NULL) );
	//int year = rand() %  20 + 1990;
	//int year = 2012;

	//try to open file
	std::stringstream fileNameSS;
	fileNameSS << "config\\weather" << year << ".dat";
	string fileName = fileNameSS.str();

	FILE *file;
	if (file = fopen(fileName.c_str(), "r"))
    {
		//try to read
        //printf("[+] file config\\weather%d.dat exists, weather don't need to be downloaded\n",year);
		int lines = 365*24;
		int count=1;
		int tmpa,tmpb;
		//printf("a\n");
		for(int dayId=1;dayId<=365&&count<=lines;dayId++)
			for(int hour=1;hour<=24;hour++,count++)
			{
				fscanf(file,"%d	%d	%lg	%lg	%lg\n",&tmpa,&tmpb,&downloadedWeather[dayId][hour].solarTime,&downloadedWeather[dayId][hour].temp,&downloadedWeather[dayId][hour].windSpeed);
				//if(dayId<3)
				//	printf("read: %d	%d	%g	%g	%g\n",tmpa,tmpb,downloadedWeather[dayId][hour].solarTime,downloadedWeather[dayId][hour].temp,downloadedWeather[dayId][hour].windSpeed);
			}
		fclose(file);
		//exit(0);
    } else
	{
		printf("[-] file config\\weather%d.dat does NOT exists\n",year);
        //fclose(file);
		//printf("b\n");


		//download data
		int month = 1; //start from January 1st
		int day = 1;
		cout << "[+] downloading weather data since " << day <<"/" << month << "/" << year << endl << "[";

		for(int id=1; id <= maxdays; id++)
		{
			
			//printf("day download %d\n",id);
			if(-1 == download(id,day,month,year)) 
				cout << "!";
			else
			{
				downloadedCount++;
				if(0 == id%5)
				cout << "=";
			}
			if(day == 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
			{
				day = 1;
				month ++;
				if (month == 13)
				{
					month =1;
					year++;
				}
			}
			else if(day == 30 && (month == 4 || month ==6 || month == 9 || month == 11))
			{
				day = 1;
				month++;
			}
			else if(day == 28 && month == 2)
			{
				day = 1;
				month = 3;
			}
			else {
					day++;
			}

		}
		cout << "]" << endl;
		cout << "[+] downloaded data for " << downloadedCount << " days"<<endl<<endl;

		//save file
		FILE *file = fopen(fileName.c_str(), "w");
		for(int id=1; id <= maxdays; id++)
			for(int h=1;h<=24;h++)
				fprintf(file, "%d	%d	%g	%g	%g\n", id, h, downloadedWeather[id][h].solarTime,downloadedWeather[id][h].temp,downloadedWeather[id][h].windSpeed);
		fclose(file);
		
	}
	
}

Hour_Data ** Forecaster::createHourDataMatrix(unsigned int days, unsigned int hours) {
	Hour_Data ** matrix;
	matrix = (Hour_Data **) calloc(days, sizeof(Hour_Data *));
	for(unsigned int i = 0; i < days; i++)
		matrix[i] = (Hour_Data *) calloc(hours, sizeof(Hour_Data));
	return matrix;
}

void Forecaster::PrintWeather(int dayId)
{
	cout << "[ ] manual request to print weather for day no. "<< dayId << endl << endl;
	for(int i = 1;i<=24; i++)
	{
	//cout << "time= " << i <<" pressure " << downloadedWeather[dayId][i].pressure << " temp "<< downloadedWeather[dayId][i].temp << " wind " << downloadedWeather[dayId][i].windSpeed << " suntime " << downloadedWeather[dayId][i].solarTime <<endl;
		cout << "time= " << i <<" temp "<< downloadedWeather[dayId][i].temp << " wind " << downloadedWeather[dayId][i].windSpeed << " suntime " << downloadedWeather[dayId][i].solarTime <<endl;
	}
	cout << endl<< endl;;
}

Hour_Data Forecaster::RequestWeather(int dayId, int hour)
{
	return downloadedWeather[dayId][hour];
}

double Forecaster::RequestDailyFlux(int dayId, int hour)
{
	if(dayId>365)
		return Flux[dayId%365][hour];

	return Flux[dayId][hour];
}