#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include <functional>
#include "settings.h"
#include "Tfield.h"
#include "Tboard.h"
#include "Tfleet.h"
#include "Tship.h"
#include "Tairport.h"
#include "Taircraft_carrier.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

//Boards for players
Tboard Board1;
Tboard Board2 = Board1; 											//One way to run copy constructor
Tboard *BoardAddressTab [2] {&Board1, &Board2};						 //These addresses will be used in first step - filling boards
//Tboard Board1, Board2;											//This is correct way to create boards, above is version to run copy construcor

//Players creation
const Tfleet Player1(FleetPoints), Player2(FleetPoints);			//In the future, points can be used for dificult level
const Tfleet *PlayerAddressTab[2] {&Player1, &Player2};
UserData UI, Empty;													//Player interface
//Player2 = Player1;												//This is how Tfleet::operator= could run

std::ostream& operator<<(std::ostream& In1, Tfield &In2){
	return In1 << In2;
}

UserData& UserData::UserToAbs(std::istream &UserType){
	fflush(stdin);																			//before/after use istream - make clereance of istream	
	
	string ColumnsAssigment, RowsAssigment {"0123456789"}, tempString {};					//Doesnt matter how much rows are set - all numbers need 0-9 digit
	int ColumnPos, RowPos, RowNb, ColumnNb;

	for(int x = 0; x < BoardColumns; x++){													//Preparing pack to check in delivered string (Columns)
		ColumnsAssigment += 'A' + x;
	}

	for(auto &x : Relative){																//convert string to upper cases
		x = toupper(x);
	}
	
	ColumnPos = Relative.find_first_of(ColumnsAssigment);																
	RowPos = Relative.find_first_of(RowsAssigment);
	
	if((ColumnPos == string::npos) || (RowPos == string::npos) /*|| ColumnPos > RowPos*/){	//If one parametr of prepared packages were not found then show msg
		tempString = "Your type is not correct.\nInsert Column in range from A to ";
		tempString += ('@' + BoardColumns);													//65 is 'A' in ASCII 
		tempString += "\nInsert row in range from 1 - ";
		tempString += std::to_string(BoardRows);
		tempString += "\nExample: A1 (ColumnRow)\n";
		
		ColumnAbs = -1;																		//-1 is value that mean it was wrong
		RowAbs = -1;
		
		cout << tempString;
	}
	else{																					//If parameters were found then convert them to absolute values 
																							//doesnt matter what was first (columns or rows) im taking first found matching
		{																					//column calculation - for 2 digits max (that mean CW)
			char toCheck = Relative[ColumnPos + 1];
			
			ColumnNb = (Relative[ColumnPos] - 'A');											//translation from ASCII to absolute
			if((toCheck >= 65) && (toCheck <= 90)) ColumnNb += (toCheck - 39);				//translation from ASCII to absolute - check if next pos is digit or letter (result have to be at least 65 which mean column AA)
											
			ColumnNb = (ColumnNb > (BoardColumns - 1) ? (BoardColumns - 1) : ColumnNb);		//Recalculating for program ansolute value
		}
		{																					//Row calculation - for 2 digits max (that mean 99max)
			tempString = Relative[RowPos];
			tempString += Relative[RowPos + 1];	
			
			RowNb = stoi(tempString);
			RowNb = (RowNb > (BoardRows - 1) ? (BoardRows - 1) : (RowNb - 1));				//Recalculating for program ansolute value
		}
		do{																					
			cout << "Type direction.\nh - horizontal, v - vertical.\nYour type: ";			//Direction checking
			cin >> std::setw(1) >> tempString;
			fflush(stdin);																	//before/after use istream - make clereance of istream
			
			tempString = toupper(tempString[0]);
		}
		while(!((tempString == "H") || (tempString == "V")));
		
		ColumnAbs = ColumnNb;																//Ready parameters										
		RowAbs = RowNb;
		Dir = (tempString == "V" ? true : false);		
	}

	return *this;
}
