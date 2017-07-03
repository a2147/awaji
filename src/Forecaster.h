//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#ifndef _FORECAST
#define _FORECAST
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <iostream>
#include <time.h>
using namespace Poco::Net;
using namespace Poco;
using namespace std;

struct Hour_Data
{
	double solarTime; //per hour, solar time = 0.5 means 30 minutes
	double windSpeed; //in kph
//	double pressure;
	double temp;
};

class Forecaster
{
	

	double ** Flux;
	Hour_Data ** downloadedWeather;
	Hour_Data ** createHourDataMatrix(unsigned int days, unsigned int hours);
	int download(int id, int day, int month, int year);
	void CalculateFluxPerDay();

public:
	Forecaster(int maxdays);
	Hour_Data RequestWeather(int dayId, int hour);
	double RequestDailyFlux(int dayId,int hour);
	void PrintWeather(int dayId);
};
#endif
