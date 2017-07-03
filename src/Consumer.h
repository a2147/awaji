//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#ifndef __CONSUMERCLASS
#define __CONSUMERCLASS
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Consumer
{
public:
	//<summary>
	//daily demand
	//</summary>
	double statisticalDailyConsumption;

	Consumer(){}
	Consumer(double E_avg);
	double current_demand(int hour, int month);

};

#endif