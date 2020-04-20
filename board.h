#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
#include "settings.h"
#include "userDataInterface.h"
#include "field.h"
#include "shipyard.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

struct userDataInterface;

class board
{
private:	
	void assignFieldAdresses();
	string makeColumnsAssigment();

	field *beginingOfAlocatedArea {nullptr};
	vector<vector<field*>> fieldAdresses;
	mutable vector<ship*> createdShips;
		
public:
	board();
	board(const board &In1);	
	~board();

	void showShipsAddresses();
	void drawBoard();

	friend class iBoardField;
};

#endif
