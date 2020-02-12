#include "Tboard.h"
#include "settings.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;

Tboard::Tboard()
{																				//Board of addresses to fields - creation
	try{
		Area = new Tfield[BoardRows * BoardColumns];							//When there will be no space to allocate boards - i except bad::alloc
	}
	catch(std::bad_alloc &_exBadAll){
		cout << "One of board allocation failed.  " << _exBadAll.what() << " occured\n";
	}
	
	vector<Tfield*> TempVec {};
	
	for(int x = 0; x < BoardRows; x++){											//vector elements (pointers) assigment										
		for(int y = 0; y < BoardColumns; y++){
			if(x < 1)	TempVec.push_back(new (&Area[y]) Tfield);				//First teen
			else	TempVec.push_back(new (&Area[(x * BoardColumns) + y]) Tfield);	//Others teens		
		}
		
		Net.push_back(TempVec);
		TempVec.clear();
	}
}	

Tboard::Tboard(const Tboard &In1){												//This constructor is not necessary (just for training)
	vector<Tfield*> TempVec {};
	delete [] Area;
	
	try{
		Area = new Tfield[BoardRows * BoardColumns];							//When there will be no space to allocate boards - i except bad::alloc
	}
	catch(std::bad_alloc &_exBadAll){
		cout << "One of board allocation failed.  " << _exBadAll.what() << " occured\n";
	}
	
	for(int x = 0; x < (BoardRows * BoardColumns); x++){						//Fields of board1 should be the same like fields in board2								
		Area[x].Occupied = In1.Area[x].Occupied;
		//name
	}

	for(int x = 0; x < BoardRows; x++){
		for(int y = 0; y < BoardColumns; y++){
			if(x < 1)	TempVec.push_back(new (&Area[y]) Tfield);				//First teen
			else	TempVec.push_back(new (&Area[(x * BoardColumns) + y]) Tfield);		//Others teens
		}
		
		Net.push_back(TempVec);
		TempVec.clear();
	}
}

Tboard::~Tboard(){																//First dealocate memory allocated for ships, then dealocate memory allocated for fields (fields keeps info about ships)												
																				//Release allocated memory for each created ships on board (or better prepare function which call specified destructor?)
	std::for_each(Ships.begin(), Ships.end(), [](const Tship *pToShip){(pToShip->Begining->Typ < MaxType ? delete pToShip : delete static_cast<const Taircraft_carrier*>(pToShip));});
	delete [] Area;																//Board of addresses to fields - destruction
}

void Tboard::showAddresses(){													//Function for check if constructors work correct
	for(int x = 0; x < BoardRows; x++){
		for(int y = 0; y < BoardColumns; y++){
			cout << "Net[" << x << "][" << y << "] = " << Net[x][y] << endl;
		}
	}
}

void Tboard::DrawBoard(){														//Function for board overwiev
	string Row {};
	int ingredientCounter {64};													//set counter on '@' char
	
	for(int x = 0; x < BoardColumns; x++){										//A - (defined columns) upper branch
		int space = (x >= 26 ? 3 : 4);											//calculating space between columns 
		char ingredient1 = (x % 26 ? ingredientCounter : ++ingredientCounter);	//every whole alphabet increase digit of "base" column (example: AZ -> BA, BZ -> CA)															
		char ingredient2 = (x % 26 ? ++ingredient2 : 0);						//every whole alphabet reset digit of second column (example: AZ -> BA, BZ -> CA)
		
		string temp (space, ' ');												//space between columns
		
		if(x<26) temp += ingredient1 + ingredient2;								//Columns A - Z
		else{																	//Columns AA - ZZ
			temp += (ingredient1 - 1);											//-1 is necessary bc AA column
			temp += 'A' + ingredient2;											//From 'A" offset
		}
		
		Row += temp;
	}
	cout << Row + "\n";
	
	for(int x = 0; x < BoardRows; x++){	
		Row = std::to_string(x+1);												//Rows of board preparation
		for(int y = 0; y < BoardColumns; y++){		
			if((y == 0) && (x < 9)) Row += "  [";								//1-9 rows have double spaces for make table look organized
			else Row += " [";													//+10th row has one space bc 10 = '1''0' (2digits) - if someone set +99rows then table will look bad
			if(Net[x][y]->Occupied) Row += "X] ";								//checking info of current field
			else Row += " ] ";
		}
		cout << Row + "\n\n";
		Row.clear();															//if all columns are ready clear this string and start again for next row
	}
}

bool Tboard::CheckPos(const UserData &UI){	
	int PossibleShips {}, MaxHor {BoardColumns - UI.ColumnAbs}, MaxVer {BoardRows - UI.RowAbs};	//MaxHor / MaxVer are variables to define how much fields - from typed field - are to border
	int RetVal;	
									
	if((UI.ColumnAbs >= 0) && (UI.RowAbs >= 0)){									//if1 - position parameters are OK try to create ship
		const Tfield *pToField = RetPosAddr(*this, UI.RowAbs, UI.ColumnAbs);

		if(!pToField->Occupied){													//if2 - check field, if ok try to create ship
			if(!UI.Dir){															//if3 - if horizontal dir then calculate options in horizontal dir
				for(PossibleShips = 0; PossibleShips < MaxHor; PossibleShips++){	//Checking what type of ship can be place on this field in horizontal dir 
					if(pToField[PossibleShips].Occupied)	break;
				}
			}
			else{																	//if3 - if vertical dir then calculate options in vertical dir
				for(PossibleShips = 0; PossibleShips < MaxVer; PossibleShips++){	//Checking what type of ship can be place on this field in horizontal dir 
					if(pToField[PossibleShips * BoardRows].Occupied)	break;		//Multipling by BoardRows bc we need to reach next row in the same column
				}
			}
			
			PossibleShips = (PossibleShips > UI.AvailablePoints ? UI.AvailablePoints : PossibleShips);
			
			try{																	//CreateShip f. is using new operator so i expect that exception can be thrown
				RetVal = CreateShip(pToField,ShipSelector(UI, PossibleShips), UI.Dir);	
				UI.AvailablePoints -= (RetVal == true ? UI.Type : 0);				//Depend on RetVal after CreateShip update points value
			}
			catch(std::bad_alloc &_exBadAll){
				cout << "Ship creation failed. " << _exBadAll.what() << " occured\n";
				RetVal = -1;
			}
		}
		else{																		//if2 - field is occupied
			cout << "This position is occupied by other ship\n";
			RetVal = 0;
		}	
	}																				//if1 - Parameters were wrong
	else RetVal	= -1;														
	return RetVal;																	
}

int Tboard::ShipSelector(const UserData &UI, int Selector){
	if(Selector > MaxType)	Selector = MaxType;
	int UserType {}, HigherSelector = Selector;										//Remember first selector value
	
	cout << "You have " << UI.AvailablePoints << " points.\n"
		 << "Possible ships in this area with your points : \n";
	
	for(int x = Selector; x > 0; x--){												//Use global array of strings which contain types names
		cout << x << ") " << stringUserType[x] << " (" << x << " field)" << endl;
	}

	do{
		cout << "Type " << HigherSelector << " - 1 to chose ship you want to place\n"
		 << "Type 0 to discard choosen field\n"
		 << "Your type: ";
		 cin >> UI.Type;
		 fflush(stdin);																//before/after use istream - make clereance of istream
	}
	while((UI.Type > HigherSelector) || (UI.Type < 0));
	
	return UI.Type;
}

bool Tboard::CreateShip(const Tfield *_pos, int Type, bool _dir){
	if(Type){
		cout << "selected Type = " << Type << endl;
		if(Type < MaxType)	Ships.push_back(static_cast<Tship*>(new Tship (const_cast<Tfield*>(_pos), Type, _dir)));
		else	Ships.push_back(static_cast<Tship*>(new Taircraft_carrier (const_cast<Tfield*>(_pos), Type, _dir))); //Polimorphism is not possible for Taircraft_carrier type when address will be retrieved (?)
		return 1;
	}
	else{
		cout << "Position is going to be denied\n";
		return 0;
	}
}
