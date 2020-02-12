#ifndef TAIRCRAFT_CARRIER_H
#define TAIRCRAFT_CARRIER_H

/*This class is used as special type of ship (hybrid with airport)*/
#include "Tship.h"
#include "Tairport.h"
#include <iostream>

using std::string;
using std::cout;

class Taircraft_carrier : public Tship, protected virtual Tairport
{
	public:
		Taircraft_carrier(Tfield *_pos, int _name, bool _dir = false) : Tship(_pos, _name, _dir), Tairport(10)
		{
		}

	protected:
};

#endif
