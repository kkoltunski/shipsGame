#ifndef TSHIP_H
#define TSHIP_H

/*This class is used as ships 1-4 type*/
#include "Tfield.h"
#include <iostream>

using std::string;
using std::cout;

class Tship
{
	protected:
		enum Type {Scout = 1, U_bot, Hybrid, Destroyer, Aircraft_carrier};		//Aircraftcarrier is special type 
		Type Name; 																//Value is also equivalent of healt points
		const Tfield *Begining; 												//Address of field where is begining of ship
		bool Direction;															//Direction: 0 = horizontal, 1 = vertical;
		int Health = Name;
	
	public:
		Tship(Tfield *_pos, int _name, bool _dir = false);	
	
	friend class Tboard;														//Necessary for Tboard destructor
};

#endif
