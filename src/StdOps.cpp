//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#include "StdOps.h"

int FirstDayOfCurrentMonth(int dayOfYear)
{
	if (dayOfYear<=31)
		return 1;

	if (dayOfYear<=59)
		return 32;

	if (dayOfYear<=90)
		return 60;

	if (dayOfYear<=120)
		return 91;

	if (dayOfYear<=151)
		return 121;

	if (dayOfYear<=181)
		return 152;

	if (dayOfYear<=212)
		return 182;

	if (dayOfYear<=243)
		return 213;

	if (dayOfYear<=273)
		return 244;

	if (dayOfYear<=304)
		return 274;

	if (dayOfYear<=334)
		return 305;

	if (dayOfYear<=365)
		return 335;

	//if(dayOfYear < 0 || dayOfYear >365)
	printf("error 121\n");
	return -1;
}
int DayToMonth(int dayOfYear)
{
	if (dayOfYear<=31)
		return 1;

	if (dayOfYear<=59)
		return 2;

	if (dayOfYear<=90)
		return 3;

	if (dayOfYear<=120)
		return 4;

	if (dayOfYear<=151)
		return 5;

	if (dayOfYear<=181)
		return 6;

	if (dayOfYear<=212)
		return 7;

	if (dayOfYear<=243)
		return 8;

	if (dayOfYear<=273)
		return 9;

	if (dayOfYear<=304)
		return 10;

	if (dayOfYear<=334)
		return 11;

	if (dayOfYear<=365)
		return 12;
	
	//if(dayOfYear < 0 || dayOfYear >365)
	printf("error 122\n");
	return -1;
}

int DaysInMonth(int monthId)
{
	if(monthId == 1 || monthId == 3 || monthId == 5 || monthId == 7 || monthId == 8 || monthId == 10 || monthId == 12)
		return 31;
	
	if(monthId == 2)
		return 28;

	if(monthId<1 || monthId > 12)
		return -1;

	return 30;
}

double string_to_double( const std::string& s )
 {
   std::istringstream i(s);
   double x;
   if (!(i >> x))
     return 0;
   return x;
 } 


void
split( vector<string> & theStringVector,  /* Altered/returned value */
       const  string  & theString,
       const  string  & theDelimiter)
{
   assert( theDelimiter.size()> 0); // My own ASSERT macro.

    size_t  start = 0, end = 0;

    while ( end != string::npos)
    {
        end = theString.find( theDelimiter, start);

        // If at end, use length=maxLength.  Else use length=end-start.
        theStringVector.push_back( theString.substr( start,
                       (end == string::npos) ? string::npos : end - start));

        // If at end, use start=maxSize.  Else use start=end+delimiter.
        start = (   ( end > (string::npos - theDelimiter.size()) )
                  ?  string::npos  :  end + theDelimiter.size());
    }
}