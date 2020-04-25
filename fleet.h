/*****************************************************************//**
 * \file   fleet.h
 * \brief  Player representation class
 * 
 * \author kkoltunski
 * \date   April 2020
***********************************************************************/

#ifndef TFLEET_H
#define TFLEET_H

#include <iostream>
#include "userDataInterface.h"

using std::string;
using std::cout;
using std::endl;

/**
 * Fleet is class representing single player.
 */
class fleet
{
private:
	static int playerNumber;
	mutable int points;
	string ID;
		
public:
	///Constructor.
	explicit fleet(int _points, string&& _name = "Player" + std::to_string(playerNumber++));

	///Copy operator (training purposes).
	fleet& operator=(const fleet& In1);

	///Player and interface communication.
	friend struct iPlayer;
	///Main interface communication
	friend class userDataInterface;
};

#endif
