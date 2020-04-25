/*****************************************************************//**
 * \file   shipyard.h
 * \brief  Polimorphic alternative for switch..case instruction used in ship placement process
 * 
 * \author kkoltunski
 * \date   April 2020
***********************************************************************/

#ifndef TSHIP_H
#define TSHIP_H

#include "field.h"
#include "settings.h"

using std::string;
using std::cout;

/**
 * Polimorphic alternative for switch..case instruction used in ship placement process
 */
class ship
{
private:
	int multiplier;

protected:
	///Method to allocate ship at correct field.
	virtual void allocator();

	///Field address where ship begining.
	field* initialFieldAddress;
	///Information in which direction ship is placed (0 - horizontal, 1 - vertical).
	bool placementDirection;
	///Ship type.
	shipType type;

public:
	///Constructor.
	ship(field* _pos, bool _dir, shipType _type);
	///Destructor.
	virtual ~ship() = default;
};

class scout : public ship
{
public:
	///Constructor.
	scout(field* _initialFieldAddress, bool _shipDirection, shipType _type);
	///Destructor.
	virtual ~scout() override = default;

	///Ship and interface communication.
	friend struct iShip;
};

class u_bot : public ship
{
public:
	///Constructor.
	u_bot(field* _initialFieldAddress, bool _shipDirection, shipType _type);
	///Destructor.
	virtual ~u_bot() override = default;

	///Ship and interface communication.
	friend struct iShip;
};

class hybrid : public ship
{
public:
	///Constructor.
	hybrid(field* _initialFieldAddress, bool _shipDirection, shipType _type);
	///Destructor.
	virtual ~hybrid() override = default;

	///Ship and interface communication.
	friend struct iShip;
};

class destroyer : public ship
{
public:
	///Constructor.
	destroyer(field* _initialFieldAddress, bool _shipDirection, shipType _type);
	///Destructor.
	virtual ~destroyer() override = default;

	///Ship and interface communication.
	friend struct iShip;
};

class aircraft_carrier : public ship
{
public:
	///Constructor.
	aircraft_carrier(field* _initialFieldAddress, bool _shipDirection, shipType _type);
	///Destructor.
	virtual ~aircraft_carrier() override = default;

	///Ship and interface communication.
	friend struct iShip;
};
#endif
