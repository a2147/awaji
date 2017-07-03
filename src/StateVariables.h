//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#ifndef _STATEVAR
#define _STATEVAR

/////////////////////////////////
//state variables editable by user 
/////////////////////////////////

//<summary>
//time range in days
//</summary>
int simulationDays = 365;

//<summary>
//amount of households
//</summary>
int n = 100;

//<summary>
//amount of households having wind turbines
//</summary>
int n_wr = 10;

//<summary>
//amount of households having solar panels on roof
//</summary>
int n_sr = 10;

//<summary>
//amount of households having solar panels on field
//</summary>
int n_sf = 0;

/////////////////////////////////
//  constant values
/////////////////////////////////

//<summary>
//average yearly energy used per houshold at the Awaji Island (units kWh)
//</summary>
//yearly 185864732.3487978 kWh for all households at the Awaji Island
//yearly 3501.926186505846 kWh per 1 household
//daily 9.836871310409681 kWh per 1 household

//const double  E_avg = 27.70267796282077;// per one hosehold without companies 
//const double E_avg = 183.5000680677274;
const double E_avg = 9.836871310409681;

//<summary>
//Air density (for temperature 15C and pressure 0.1MPa in kg/m3
//</summary>
const double  p = 0.1225;

#endif