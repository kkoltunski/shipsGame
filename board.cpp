#include "board.h"

board::board(){
	try {
		beginingOfAlocatedArea = new field[boardRows * boardColumns];
		assignFieldAdresses();
	}
	catch (std::bad_alloc& _exBadAll) {
		cout << "One of board allocation failed.  " << _exBadAll.what() << " occured\n";
	}
}	

board::board(const board& In1) {												//This constructor is not necessary (just for training)
	try {
		beginingOfAlocatedArea = new field[boardRows * boardColumns];
		for (int x = 0; x < (boardRows * boardColumns); x++) beginingOfAlocatedArea[x] = In1.beginingOfAlocatedArea[x];
		assignFieldAdresses();
	}
	catch (std::bad_alloc& _exBadAll) {
		cout << "One of board allocation failed.  " << _exBadAll.what() << " occured\n";
	}
}

board::~board() {
	std::for_each(createdShips.begin(), createdShips.end(), [](const ship* pToShip) {delete pToShip; });
	delete[] beginingOfAlocatedArea;
}

void board::assignFieldAdresses() {
	vector<field*> helpRow{};

	for (int actualRowNumber = 0; actualRowNumber < boardRows; actualRowNumber++) {								
		for (int actualColumnNumber = 0; actualColumnNumber < boardColumns; actualColumnNumber++) {
			helpRow.push_back(&beginingOfAlocatedArea[(actualRowNumber * boardColumns) + actualColumnNumber]);
		}

		fieldAdresses.push_back(helpRow);
		helpRow.clear();
	}
}

void board::showShipsAddresses(){												//Help Function for check if constructors work correct
	for(int x = 0; x < boardRows; x++){
		for(int y = 0; y < boardColumns; y++){
			cout << "Net[" << x << "][" << y << "] = " << fieldAdresses[x][y] << endl;
		}
	}
}

void board::drawBoard(){
	std::stringstream helpRow("");
	cout << makeColumnsAssigment() << endl;

	for(int x = 0; x < boardRows; x++){		
		helpRow << std::setw(3) << std::left << (x+1);
		for(int y = 0; y < boardColumns; y++){																
			if(fieldAdresses[x][y]->occupiedByShip) helpRow << "[X]  ";
			else helpRow << "[ ]  ";
		}
		cout << helpRow.str() << "\n\n";
		helpRow.str("");
	}
}

string board::makeColumnsAssigment() {
	string alphabet{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	short alphabetSize = alphabet.size();
	short spaceBetweenColumns{};
	char columnIngridient1{ 64 }, columnIngridient2{ 64 };
	std::stringstream Row("");

	for (int actualColumnNumber = 0; actualColumnNumber < boardColumns; actualColumnNumber++) {
		spaceBetweenColumns = (actualColumnNumber > alphabetSize ? 3 : 4);

		if ((actualColumnNumber % alphabetSize) || (actualColumnNumber == 0)) ++columnIngridient1;		//OR statement is necessary because expression "0 % ..." is 0
		else {
			++columnIngridient2;
			columnIngridient1 = 'A';
		}

		Row << std::setw(spaceBetweenColumns) << "";
		if (actualColumnNumber < alphabetSize) Row << columnIngridient1;
		else Row << columnIngridient2 << columnIngridient1;
	}

	return Row.str();
}
