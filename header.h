#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include <functional>
#include "userDataInterface.h"
#include "settings.h"
#include "field.h"
#include "board.h"
#include "fleet.h"
#include "shipyard.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

//Boards for players
board Board1;
board Board2 = Board1;
board *BoardAddressTab [2] {&Board1, &Board2};				//These addresses will be used in first step - filling boards
//Tboard Board1, Board2;									//This is correct way to create boards, above is version to run copy construcor

//Players creation
fleet Player1(fleetPoints), Player2(fleetPoints);			//In the future, points can be used for dificult level
fleet *PlayerAddressTab[2] {&Player1, &Player2};
//Player2 = Player1;										//This is how Tfleet::operator= could run

std::ostream& operator<<(std::ostream& In1, field &In2){
	return In1 << In2;
}

#endif // !HEADER_H