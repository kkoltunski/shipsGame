#include <string>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

constexpr int BoardRows = 10;						//Board parameters
constexpr int BoardColumns = 10;						//Board parameters	- 47 is max console resolution (on my laptop)

constexpr int FleetPoints = 10;						//Points per fleet

constexpr const char* stringUserType [6] {"Discard" ,"Scout", "Ubot", "Hybrid", "Destroyer", "Aircraft_carrier"};		//This array will be used for showing user options (Tboard f.ShipSelector)
constexpr int MaxType = 5;							//Higher possible type in Tship			
constexpr int MinType = 1;							//Lower possible type in Tship

struct UserData{									//This structure is used as user inputs
	string Relative, Name;							//This is input from istream and actual Player name
	int RowAbs, ColumnAbs; 							//Values for program
	bool Dir;
	mutable int Type, AvailablePoints;				//introduced type of ship & points number which are able to use
	
	UserData& UserToAbs(std::istream &UserType);	//Function to prevent wrong values & translation from user types to program (filing structure)
};

