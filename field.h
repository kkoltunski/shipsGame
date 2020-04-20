#ifndef FIELD_H
#define FIELD_H

/*This class is used as single field in whole board*/
#include <iostream>

class ship;

class field
{
private:
	bool occupiedByShip;
	bool shipDirection;
	ship* pToShip;

	field(bool _ocupation = false)	: occupiedByShip(_ocupation), pToShip{nullptr}{
	}
	field& operator=(field& _in);

	friend class iBoardField;
	friend class board;
	friend class ship;
	friend class scout;
	friend class u_bot;
	friend class hybrid;
	friend class destroyer;
	friend class aircraft_carrier;
	friend std::ostream& operator<<(std::ostream& In1, field &In2);
};

#endif
