/*****************************************************************//**
 * \file   header.h
 * \brief  Main header with included libraries
 * 
 * \author kkoltunski
 * \date   April 2020
***********************************************************************/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include "userDataInterface.h"
#include "settings.h"
#include "field.h"
#include "board.h"
#include "fleet.h"
//#include "shipyard.h"

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

/**
 * \brief Operator to make possible showing field information.
 * 
 * \param [in] _inStream
 * \param [in] _inField
 * \return Reference to used _inStream
 */
std::ostream& operator<<(std::ostream& _inStream, const field &_inField){
    _inStream << "Field address = " << _inField.pToShip << "is ";
    _inStream << (_inField.occupiedByShip ? "occupied in " : "not occupied.\n");

    if(_inField.shipDirection) {
        _inStream << "vertical direction.\n";
    }
    else {
        _inStream << "horizontal direction.\n";
    }

    return _inStream;
}

#endif // !HEADER_H