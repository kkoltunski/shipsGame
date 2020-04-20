#ifndef TFLEET_H
#define TFLEET_H

/*This class is used as player data*/
#include <iostream>
#include "settings.h"
#include "userDataInterface.h"

using std::string;
using std::cout;
using std::endl;

class fleet
{
private:
	static int playerNumber;
	mutable int points;
	string ID;
		
public:
	fleet(int _points, string &&_name = "Player" + std::to_string(playerNumber++)) : points(_points), ID(_name)
	{
	}
	
	fleet& operator=(const fleet& In1);

	friend class iPlayer;
	friend class userDataInterface;
};

#endif
