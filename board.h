/*****************************************************************//**
 * \file   board.h
 * \brief  Board for ship placement.
 *
 * \author kkoltunski
 * \date   April 2020
***********************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
#include "settings.h"
#include "field.h"
#include "shipyard.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class userDataInterface;
class ship;

/**
* Board is class which allow to place ships. It include (\ref boardRows x \ref boardColumns) field addresses.
* It stored each ship address which is placed on it.
*/
class board
{
private:
	void assignFieldAdresses();
	void makeColumnsAssigment();

	string upperBranchDefinition;
	field *beginingOfAlocatedArea {nullptr};
	vector<vector<field*>> fieldAdresses;
	mutable vector<ship*> createdShips;
		
public:
	///Default constructor.
	board();
	///Copy constructor (for training purposes).
	board(const board &In1);
	///Destructor.
	virtual ~board();
	
	///Show created ship addresses.
	void showShipsAddresses() const noexcept(true);
	///Show board state.
	void drawBoard() const noexcept(true);

	///Board and interface communication.
	friend struct iBoard;

	///Operator =;
	board& operator=(board&);
};

#endif
