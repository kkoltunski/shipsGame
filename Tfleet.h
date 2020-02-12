#ifndef TFLEET_H
#define TFLEET_H

/*This class is used as player data*/
#include <iostream>

using std::string;
using std::cout;
using std::endl;

struct UserData;

class Tfleet
{
	private:
		static int Player;
		mutable int Points;
		string Name;
		
	public:
		Tfleet(int _points, string _name = "Player" + std::to_string(Player++)) : Points(_points), Name(_name)
		{
		}
	
		Tfleet& operator=(const Tfleet& In1);
		void UserDataHandshake(UserData &UI, int Mode) const;					//Mode 0 = Fleet -> UserData, Mode 1 = UserData -> Fleet;
};

#endif
