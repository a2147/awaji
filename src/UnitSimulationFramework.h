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
#include <vector>

void SimulateSingleSolarPanelUnit(double monthlyConsE);
void SimulateSingleWindTurbineUnit(double monthlyConsE);
void SimulateRateOfInterestForSolarPanels(double monthlyConsE);
void SimulateRateOfInterestForWindTurbines(double monthlyConsE);
void SimulateRateOfInterestForSolarFarm(double monthlyConsE);
void TestDistrubutionFunction(int count, int mu, int sigma);