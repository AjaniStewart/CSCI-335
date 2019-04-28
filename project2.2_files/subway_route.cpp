/******************************************************************************
  Title          : subway_route.cpp
  Author         : Marin Pavlinov Marinov
  Created on     : April 22, 2018
  Description    : cpp file for the SubwayRoute object
  Purpose        : implements subway_route
  Usage          :
  Build with     : c++11
  Modifications  :

******************************************************************************/

#include "subway_route.h"

/*******************************************************************************
 *                    Functions related to subway routes                        *
 ******************************************************************************/

// function to check if string contains numbers 1 - 7
bool is_valid_num(string s) {
	return (s[0] == '1' || s[0] == '2' || s[0] == '3' || s[0] == '4' || s[0] == '5' || s[0] == '6'
	        || s[0] == '7');
}

bool is_route_id(string s) {
	// if string is empty, no need to do further checks
	if (s.empty())
		return false;

	// case 1: GS or FS
	if (s == "GS" || s == "FS")
		return true;

	// case 2: Numbers 1 through 7
	if (is_valid_num(s))
		return true;

	// case 3: Letters A - Z
	if (isalpha(s[0]))
		return true;

	// none of the 3 cases are true if program comes here
	return false;
}

string str_from_routeset(route_set s) {
	string str = "";
	for (int i = 1; i < 36; i++) {
		// get ith bit
		int bit = (s | s << i);
		// AND bit to check if its 1 or 0
		if ((bit & 1) == 1) {
			str += int2route_id(i);
			// separate routes by ,
			str += ',';
		}
	}

	return str;
}

int routestring2int(string s) {
	// FS and GS case
	if (s == "GS")
		return 8;

	if (s == "FS")
		return 9;

	// A-Z case
	/*
	    if its an alphabetical letter the ascii value of its uppercase minus 55
	    falls within the range of [0,63]
	    the -55 (Assuming letter is uppercase) makes the values start at 10 and end at 35
	    that is why I use toupper so that lowercase inputs are valid and still yield the same result
	 */
	if (isalpha(s[0]))
		return ((int) toupper(s[0]) - 55);

	// 1-7 case
	return stoi(s);
}

string int2route_id(int k) {
	// FS and GS case
	if (k == 8)
		return "GS";

	if (k == 9)
		return "FS";

	// A-Z case
	if (k > 9 || k < 36) {
		string s = "";
		char c = (char) (k + 55);
		s += c;
		return s;
	}

	// 1-7
	if (k > 0 || k < 8)
		return to_string(k);
}

/*******************************************************************************
 *                           SubwayRoute Class                                  *
 ******************************************************************************/

list<int> SubwayRoute::station_list() const {
	return stations;
}

void SubwayRoute::add_station_to_route(int station_id) {
	stations.push_back(station_id);
}

route_set SubwayRoute::get_routeset() const {
	return routes;
}
