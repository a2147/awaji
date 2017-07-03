//
// Title: Decentralized electrity market on Awaji Island
//
// Credits: Arkadiusz P. Wojcik
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
using namespace std;

double string_to_double( const std::string& s );

int FirstDayOfCurrentMonth(int dayOfYear);

int DayToMonth(int dayOfYear);

int DaysInMonth(int monthId);

void
split( vector<string> & theStringVector,  /* Altered/returned value */
       const  string  & theString,
       const  string  & theDelimiter);