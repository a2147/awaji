//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//

#include "Consumer.h"

//<summary>
//average energy used per houshold at the Awaji Island (units kWh)
//</summary>

Consumer::Consumer(double E_avg)
{
	statisticalDailyConsumption = E_avg;
}

double Consumer::current_demand(int hour, int month)
{
	double mod = 1;

	switch(month)
	{
	case 1:
		mod=1.376257545;
		break;
	case 2:
		mod=1.110663984;
		break;
	case 3:
		mod=1.038229376;
		break;
	case 4:
		mod=1.062374245;
		break;
	case 5:
		mod=0.893360161;
		break;
	case 6:
		mod=0.772635815;
		break;
	case 7:
		mod=0.941649899;
		break;
	case 8:
		mod=1.086519115;
		break;
	case 9:
		mod=1.014084507;
		break;
	case 10:
		mod=0.869215292;
		break;
	case 11:
		mod=0.845070423;
		break;
	case 12:
		mod=0.989939638;
		break;
	default:
		printf("error current_demand(..) month=%d\n",month);
	}

	//according to the table
	switch(hour)
	{
		case 1:
			return statisticalDailyConsumption*0.03781*mod;
		case 2:
			return statisticalDailyConsumption*0.03041*mod;
		case 3:
			return statisticalDailyConsumption*0.02608*mod;
		case 4:
			return statisticalDailyConsumption*0.02454*mod;
		case 5:
			return statisticalDailyConsumption*0.02524*mod;
		case 6:
			return statisticalDailyConsumption*0.02963*mod;
		case 7:
			return statisticalDailyConsumption*0.03882*mod;
		case 8:
			return statisticalDailyConsumption*0.04939*mod;
		case 9:
			return statisticalDailyConsumption*0.04399*mod;
		case 10:
			return statisticalDailyConsumption*0.03781*mod;
		case 11:
			return statisticalDailyConsumption*0.03396*mod;
		case 12:
			return statisticalDailyConsumption*0.03288*mod;
		case 13:
			return statisticalDailyConsumption*0.03488*mod;
		case 14:
			return statisticalDailyConsumption*0.03496*mod;
		case 15:
			return statisticalDailyConsumption*0.03411*mod;
		case 16:
			return statisticalDailyConsumption*0.03527*mod;
		case 17:
			return statisticalDailyConsumption*0.03982*mod;
		case 18:
			return statisticalDailyConsumption*0.05001*mod;
		case 19:
			return statisticalDailyConsumption*0.05973*mod;
		case 20:
			return statisticalDailyConsumption*0.05827*mod;
		case 21:
			return statisticalDailyConsumption*0.06444*mod;
		case 22:
			return statisticalDailyConsumption*0.06452*mod;
		case 23:
			return statisticalDailyConsumption*0.06189*mod;
		case 24:
			return statisticalDailyConsumption*0.05155*mod;
	}
	printf("error 124\n");
	return 0;

}