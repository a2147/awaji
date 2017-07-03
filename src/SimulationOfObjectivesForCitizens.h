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
#include "StdOps.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>


int SimulateInvestitionInSingleSolarPanel(int simDays,double monthlyConsE,  Forecaster f1);
int SimulateInvestitionInSingleWindTurbnie(int simDays,double monthlyConsE,  Forecaster f1);
int SimulateSmartGridAtTheAwajiIsland11Houses(Forecaster f1,int simulationDays, double monthlyConsE);
int SimulateSmartGridAtTheAwajiIsland(double monthlyConsE);