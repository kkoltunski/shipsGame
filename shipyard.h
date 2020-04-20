#ifndef TSHIP_H
#define TSHIP_H

/*This class is used as ships 1-4 type*/
#include <iostream>
#include "field.h"
#include "settings.h"

using std::string;
using std::cout;

class ship
{
protected:
	virtual void allocator();

	field* initialFieldAddress;
	bool placementDirection;						//Direction: 0 = horizontal, 1 = vertical;
	shipType type;
	int multiplier;

public:
	ship( field* _pos, bool _dir, shipType _type) : initialFieldAddress{ _pos }, placementDirection{ _dir }, type{ _type }{
		multiplier = (_dir ? boardColumns : 1);
	}
	virtual ~ship() = default;

//	friend class board;								//Necessary for Tboard destructor
};

class scout : public ship
{
public:
	scout(field* _initialFieldAddress, bool _shipDirection, shipType _type) : ship(_initialFieldAddress, _shipDirection, _type){
		allocator();
	}
	virtual ~scout() override = default;

	friend class iShip;
};

class u_bot : public ship
{
public:
	u_bot(field* _initialFieldAddress, bool _shipDirection, shipType _type) : ship(_initialFieldAddress, _shipDirection, _type) {
		allocator();
	}
	virtual ~u_bot() override = default;

	friend class iShip;
};

class hybrid : public ship
{
public:
	hybrid(field* _initialFieldAddress, bool _shipDirection, shipType _type) : ship(_initialFieldAddress, _shipDirection, _type) {
		allocator();
	}
	virtual ~hybrid() override = default;

	friend class iShip;
};

class destroyer : public ship
{
public:
	destroyer(field* _initialFieldAddress, bool _shipDirection, shipType _type) : ship(_initialFieldAddress, _shipDirection, _type) {
		allocator();
	}
	virtual ~destroyer() override = default;

	friend class iShip;
};

class aircraft_carrier : public ship
{
public:
	aircraft_carrier(field* _initialFieldAddress, bool _shipDirection, shipType _type) : ship(_initialFieldAddress, _shipDirection, _type) {
		allocator();
	}
	virtual ~aircraft_carrier() override = default;

	friend class iShip;
};
#endif
