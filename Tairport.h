#ifndef TAIRPORT_H
#define TAIRPORT_H

/*This class is only as inheritance exercise*/
#include <iostream>

using std::string;
using std::cout;

class Tairport
{
	protected:
		unsigned int planeNb, runwayNb;
		double petrolSupply;
		 
		Tairport() = default;
		Tairport(int _planes/* = 10*/, int _runways = 5, double _tank = 1000.5) : planeNb(_planes), runwayNb(_runways), petrolSupply{_tank}
		{
		}
};

#endif
