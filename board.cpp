#include "board.h"

/**
 * Trying to allocate necessary memory for board. If allocation is successed then allocated area is partitioning
 * as fields and assigning to vector with these \ref field addresses. Constructor also preparing board upper branch columns definition.
 */
board::board(){
	try {
		beginingOfAlocatedArea = new field[boardRows * boardColumns];
		assignFieldAdresses();
		makeColumnsAssigment();
	}
	catch (std::bad_alloc& _exBadAll) {
		cout << "One of board allocation failed.  " << _exBadAll.what() << " occured\n";
	}
}	

/**
* The same what default constructor but parameter ocupation from fields in original board are copied to new created board.
 * @param[in] const board& originalBoard Reference to original board.
 */
board::board(const board& _originalBoard) {
	try {
		beginingOfAlocatedArea = new field[boardRows * boardColumns];
		for (int x = 0; x < (boardRows * boardColumns); x++) beginingOfAlocatedArea[x] = _originalBoard.beginingOfAlocatedArea[x];
		assignFieldAdresses();
		makeColumnsAssigment();
	}
	catch (std::bad_alloc& _exBadAll) {
		cout << "One of board allocation failed.  " << _exBadAll.what() << " occured\n";
	}
}

/**
 * It dealocate memory which was allocated for ships () and fields(alocated by board() or
 * board(const board& originalBoard)). 
 * First dealocated are ships, then board fields.
 */
board::~board() {
	std::for_each(createdShips.begin(), createdShips.end(), [](const ship* pToShip) {delete pToShip; });
	delete[] beginingOfAlocatedArea;
}

/**
 * Assigning vector<field*> to vector<vector<field*>> fieldAdresses allocated by board() or
 * board(const board& originalBoard)
 */
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

/**
 * Method used for preparation upper branch columns definitions which is necessary to show correct board.
 * Method result is based on boardColumns defined in settings.h header.
 */
void board::makeColumnsAssigment() {
	char columnIngridient1{ 64 }, columnIngridient2{ 64 };
	std::stringstream Row("");

	for (int actualColumnNumber = 0; actualColumnNumber < boardColumns; actualColumnNumber++) {
		short spaceBetweenColumns = (actualColumnNumber > alphabetSize ? 3 : 4);

		if ((actualColumnNumber % alphabetSize) || (actualColumnNumber == 0)){			//OR statement is necessary because expression "0 % ..." is 0
			++columnIngridient1;
		}
		else {
			++columnIngridient2;
			columnIngridient1 = 'A';
		}

		Row << std::setw(spaceBetweenColumns) << "";
		if (actualColumnNumber < alphabetSize) {
			Row << columnIngridient1;
		}
		else {
			Row << columnIngridient2 << columnIngridient1;
		}
	}

	upperBranchDefinition = Row.str();
}

/** 
 * Method used for showing players boards. Method is also usefull while commissioning and software maintanence.
 */
void board::drawBoard() const noexcept(true) {
	std::stringstream helpRow("");
	cout << upperBranchDefinition << endl;

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

/**
 * Method usefull while commissioning and software maintanence.
 */
void board::showShipsAddresses() const noexcept(true) {
	for (int x = 0; x < boardRows; x++) {
		for (int y = 0; y < boardColumns; y++) {
			cout << "Net[" << x << "][" << y << "] = " << fieldAdresses[x][y] << endl;
		}
	}
}

/**
* The same what copy constructor but parameter ocupation from fields in original board are copied to new created board.
 * @param[in] const board& originalBoard Reference to original board.
 */
board& board::operator=(board& _orginalBoard) {
	try {
		if (&_orginalBoard != this) {
			beginingOfAlocatedArea = new field[boardRows * boardColumns];
			for (int x = 0; x < (boardRows * boardColumns); x++) beginingOfAlocatedArea[x] = _orginalBoard.beginingOfAlocatedArea[x];
			assignFieldAdresses();
			makeColumnsAssigment();
		}
	}
	catch (std::bad_alloc& _exBadAll) {
		cout << "One of board allocation failed.  " << _exBadAll.what() << " occured\n";
	}

	return *this;
}
