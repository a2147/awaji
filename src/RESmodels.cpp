//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//


#include "RESmodels.h"

Producer ReturnSampleWindTurbine(int modelID)
{
	switch(modelID)
	{
	case 1:
		//2000w
		//7414 euro + 688 + 1790 euro = 9892 euro = 1060441yen
		//http://windykraft.ee/en/products/wind-generator-2kw/

		return Producer(12, 2.0,1060441);

	case 2:
		//3kW
		//8370+688+1790 euro = 10848 euro = 1162926yen
		//http://windykraft.ee/en/products/wind-generator-3kw/

		return Producer(12,3.0,1162926);

	case 3:
		//5kW
		//13320+688+1790 euro net = 15798 euro = 1693575yen
		//http://windykraft.ee/en/products/wind-generator-5kw/

		return Producer(12,5.0,1693575);

	case 4:
		//10kW
		//25246+688+1790 EUR ner = 27724 euro = 2972065yen
		//http://windykraft.ee/en/products/wind-generator-10kw/

		return Producer(15,10.0,2972065);

	case 5:
		//20kW
		//36672+688+1790 EUR = 39150 euro = 4196954yen
		//http://windykraft.ee/en/products/wind-generator-20kw/

		return Producer(18,20.0,4196954);

	}

	cout << "error 101\n";
	return Producer();
}

Producer ReturnSampleSolarFarm()
{
	bool info = false;
	//http://www.siliconsolar.com/90-watt-solmaxx-solar-panel-p-503365.html
	//$199.00
	//21" x 47" = 53.34 cm x 119.38 cm = 0.63677m2
	//500m2 requires 786 units
	//old version :total cost = 393000 usd = 3 216 3024yen
	//new version: 156414 usd = 1 280 0883 yen
	//total power = 73kW

	return Producer(500.0,0.1,73,12800883);
}

Producer ReturnSampleSolarPanel(int modelID)
{
	//http://solar-plexus.co.uk/index.php/component/virtuemart/solar-panels-1520w-to-5000w-pv-bundles-mcs-tuv-ce-iec-approved.html

	switch(modelID)
	{
	case 1:
		//1640 pounds net= 216170yen
		//1.5kW
		return Producer(9.76,0.1,1.5,216170);
	
	case 2:
		//1984 pounds net= 261513yen
		//2kW
		return Producer(13.01,0.1,2.0,261513);

	case 3:
		//2791 punds net = 367884yen
		//3kW
		return Producer(19.52, 0.1,3.0,367884);

	case 4:
		//3750 pounds net = 494291yen
		//4kW
		return Producer(26.03,0.1,4.0,494291);

	case 5:
		//4724 pounds net = 622675yen
		//5kW
		return Producer(34.16,0.1,5.0,622675);

	case 6:
		//2*3kW
		return Producer(39.04, 0.1,6.0,735768);

	case 7:
		//2*4kW
		return Producer(52.06, 0.1, 8.0, 988582);

	case 8:
		//2*5kW
		return Producer(68.32, 0.1, 10.0, 1245350);

	}

	cout << "error 102\n";
	return Producer();
}