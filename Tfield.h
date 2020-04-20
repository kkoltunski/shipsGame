#ifndef TFIELD_H
#define TFIELD_H

/*This class is used as single field in whole board*/
#include <iostream>

class Tship;

class Tfield
{
	private:																				//
		bool Occupied;																//Information if field is occupied
		int Typ;																	//Information what kind of ship is standing here
		Tship* pToShip;
		Tfield(bool _ocupation = false)	: Occupied(_ocupation), pToShip{nullptr}
		{
		}
		
		friend class Tboard;
		friend class Tship;
		friend std::ostream& operator<<(std::ostream& In1, Tfield &In2);
};

#endif
