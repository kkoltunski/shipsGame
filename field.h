/*****************************************************************//**
 * \file   field.h
 * \brief  Single field representation class in whole board
 * 
 * \author kkoltunski
 * \date   April 2020
***********************************************************************/

#ifndef FIELD_H
#define FIELD_H

#include <iostream>

class ship;
/**
 * Field is class representing part of board.
 */
class field 
{
private:
	bool occupiedByShip;
	bool shipDirection;
	ship* pToShip;

	field(bool _ocupation = false) : occupiedByShip(_ocupation), pToShip{ nullptr }, shipDirection{false}{
	}
	virtual ~field();

public:
	///Copy operator.
	field& operator=(field& _originalField);

	///User and board communication interface.
	friend struct iBoard;
	///Board is making changes in fields.
	friend class board;
	///Ship function modyfing field states.
	friend class ship;
	///Ship function modyfing field states.
	friend class scout;
	///Ship function modyfing field states.
	friend class u_bot;
	///Ship function modyfing field states.
	friend class hybrid;
	///Ship function modyfing field states.
	friend class destroyer;
	///Ship function modyfing field states.
	friend class aircraft_carrier;
	///External << operator to make possible showing field information.
	friend std::ostream& operator<<(std::ostream& _inStream, const field& _inField);
};

#endif
