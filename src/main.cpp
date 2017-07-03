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
#include "UnitSimulationFramework.h"
#include "SimulationOfObjectivesForCitizens.h"
#include "StateVariables.h"

int main()
{
	SimulateSingleSolarPanelUnit(E_avg);

	SimulateSingleWindTurbineUnit(E_avg);

	SimulateRateOfInterestForSolarPanels(E_avg);

	SimulateRateOfInterestForWindTurbines(E_avg);

	SimulateRateOfInterestForSolarFarm(E_avg);

	/*SimulateInvestitionInSingleSolarPanel(simulationDays,E_avg, forecaster);
	
	SimulateInvestitionInSingleWindTurbnie(simulationDays, E_avg, forecaster);

	SimulateSmartGridAtTheAwajiIsland11Houses(forecaster,simulationDays, E_avg);*/

	SimulateSmartGridAtTheAwajiIsland(E_avg);

	return 0;
}