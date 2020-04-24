#include "userDataInterface.h"

//iBoard interface methods
/**
 * Checking is basing on board columns and rows definition.
 * \return Result of checking (true - position is correct, false - position is not correct).
 */
inline bool iBoard::isTypedPositionValid() noexcept(true) {
	bool result{ true };
	if (userTypedPosition.find_first_of(columnsDefinitions) == string::npos) result = false;
	if (userTypedPosition.find_first_of(rowsDefinitions) == string::npos) result = false;

	return result;
}

/**
 * Translating user column type to absolute values. 
 */
void iBoard::calculateColumnAbsoluteValue() noexcept(true) {
	size_t columnPosition = userTypedPosition.find_first_of(columnsDefinitions);
	char nextChar = userTypedPosition[columnPosition + 1];

	absoluteColumn = (userTypedPosition[columnPosition] - 'A');

	if (boardColumns > 26)
		if ((nextChar >= 'A') && (nextChar <= 'Z')) absoluteColumn += (nextChar - 39);				//e.g column position AA => for 1'st digit (A) absoluteColumn = 0, for 2'nd digit (A) absoluteColumn = (65-39) = 26 

	absoluteColumn = (absoluteColumn > (boardColumns - 1) ? (boardColumns - 1) : absoluteColumn);
}

/**
 * Translating user row type to absolute values.
 */
void iBoard::calculateRowAbsoluteValue() noexcept(true) {
	size_t rowPosition = userTypedPosition.find_first_of(rowsDefinitions);
	string help = userTypedPosition.substr(rowPosition, 2);

	absoluteRow = (std::stoi(help) - 1);
	absoluteRow = (absoluteRow > (boardRows - 1) ? (boardRows - 1) : absoluteRow);
}

/**
 * Main method to check if user typed position is correct. 
 * \throw incorrectPosition While user type is not correct.
 * \return Result of position checking (true - user type is correct, false - user type is not correct).
 */
bool iBoard::isUserTypeCorrect() noexcept(false) {
	bool result;

	try {
		if (initialized) initialized = false;

		convertRelativePositionCasesSize();
		if (isTypedPositionValid()) {
			calculateColumnAbsoluteValue();
			calculateRowAbsoluteValue();
		}
		else throw(incorrectPosition());

		result = true;
	}
	catch (incorrectPosition& Exception) {
		cout << Exception.what() << endl;
		result = false;
	}

	return result;
}

/**
 * Ask user to type direction in which future ship will be places.
 */
void iBoard::getDirection() noexcept(true) {
	char typedDirection;

	do {
		cout << "Type direction.\nh - horizontal, v - vertical.\nYour type: ";

		cin.get(typedDirection);
		cin.ignore();

		typedDirection = toupper(typedDirection);
	} while (!((typedDirection == 'H') || (typedDirection == 'V')));

	Dir = (typedDirection == 'V' ? true : false);
}

/**
 * Method is using pointer to actual board and asking about field occupation.
 * \param [in] _row Row offset from absolute row value.
 * \param [in] _column column offset from absolute column value.
 * \return Information if field is occupied (true - field is occupied, false - field is free).
 */
bool iBoard::getFieldOccupation(short _row, short _column) const noexcept(true) {
	return objectAddress->fieldAdresses[absoluteRow + _row][absoluteColumn + _column]->occupiedByShip;
}

/**
 * Method is using pointer to actual board and geting typed field address.
 * \return Information of user typed field address.
 */
field* iBoard::getFieldAddress() const noexcept(true) {
	return objectAddress->fieldAdresses[absoluteRow][absoluteColumn];
}

/**
 * Method is using pointer to actual board to give order to add a ship.
 * \param [in] _pToShip Ship addres which should be added to board.
 */
void iBoard::addShip(ship* _pToShip) noexcept(true) {
	objectAddress->createdShips.push_back(_pToShip);
}
///////////////////////////////////////////////////////////////////////////////////

//iPlayer interface methods
/**
 * Method is using pointer to actual player to get name information.
 * \return Player name.
 */
string iPlayer::returnPlayerName() const noexcept(true) {
	return objectAddress->ID;
}

/**
 * \param [in] _pointsToUpdate Number of which actual points number has to be decreased.
 */
void iPlayer::updatePoints(short _pointsToUpdate) noexcept(true) {
	objectAddress->points -= _pointsToUpdate;
}

/**
 * Method is using pointer to actual player to get actual points information.
 * \return Player available points..
 */
int iPlayer::returnPoints() const noexcept(true) {
	return objectAddress->points;
}
///////////////////////////////////////////////////////////////////////////////////

//iShip interface methods
/**
 * Main method to manage possible ships calculation depend on placement direction and player possible points.
 * \param [in] _direction Ship placement direction.
 * \param [in] _boardInterface Reference to iBoard interface.
 * \param [in] _playerInterface Reference to iPlayer interface.
 */
void iShip::calculatePossibleShips(bool _direction, const iBoard& _boardInterface, const iPlayer& _playerInterface) noexcept(true) {

	if (_direction) calculateVerticalPossibilities(_boardInterface);
	else calculateHorizontalPossibilities(_boardInterface);

	adjustPossibleShipValue(_playerInterface.returnPoints());
}

/**
 * Method which calculate possible ships in vertical direction.
 * \param [in] _boardInterface Reference to iBoard interface.
 */
void iShip::calculateVerticalPossibilities(const iBoard& _boardInterface) {
	verticalDistanceToBorder = (boardRows - _boardInterface.returnAbsoluteRow());

	for (possibleShips = 0; possibleShips < verticalDistanceToBorder; possibleShips++) {
		if (_boardInterface.getFieldOccupation(possibleShips, 0))	break;
	}
}

/**
 * Method which calculate possible ships in horizontal direction.
 * \param [in] _boardInterface Reference to iBoard interface.
 */
void iShip::calculateHorizontalPossibilities(const iBoard& _boardInterface) {
	horizontalDistanceToBorder = (boardColumns - _boardInterface.returnAbsoluteColumn());

	for (possibleShips = 0; possibleShips < horizontalDistanceToBorder; possibleShips++) {
		if (_boardInterface.getFieldOccupation(0, possibleShips))	break;
	}
}

/**
 * Method which make corrections of possible ships depend on \ref highestPossibleShipType and possible player points.
 * \param [in] _boardInterface Reference to iBoard interface.
 */
void iShip::adjustPossibleShipValue(short _points) noexcept(true) {
	possibleShips = ((possibleShips > highestPossibleShipType) ? highestPossibleShipType : possibleShips);
	possibleShips = ((possibleShips > _points) ? _points : possibleShips);
}

/**
 * Method which manage user ship type. \warning Position have to be type two times. It is strange behavior which should not appear
 * but anyway it appear and i dont know why because on other compiler it works fine.
 */
void iShip::getUserTypedShip() noexcept(true) {
	short typedShip{ 0 };

	do {
		cout << "Type " << possibleShips << " - 1 to chose ship you want to place\n"
			 << "Type 0 to discard choosen field\nYour type: ";

		//do {
		//	cin.clear();
		//	cin.sync();
		//	cin >> typedShip;
		//	if (cin.fail()) cout << "fail" << endl;
		//} while (!cin);

		cin.clear();														//VisualStudio bug??????? - have to introduce value 2 times
		cin.ignore();
		cin >> typedShip;
		if (cin.fail()) cout << "Wrong type." << endl;

	} while ((typedShip > possibleShips) || (typedShip < 0) || cin.fail());
	cin.ignore();

	shipType = typedShip;
}

/**
 * Method which is factory of ships. It used \ref shipType to define which ship type should be created by ::new operator. 
 * \throw bad_alloc When there is not enough memory to allocate choosen ship.
 * \param [in] _boardInterface Reference to iBoard interface.
 * \return Address of created ship. 
 */
ship* iShip::shipyard(const iBoard& _boardInterface) noexcept(true) {
	ship* pToShip{ nullptr };
	try {
		switch (shipType) {
		case (static_cast<short>(shipType::Aircraft_carrier)):
			pToShip = new aircraft_carrier(_boardInterface.getFieldAddress(), _boardInterface.returnTypedDirection(), shipType::Aircraft_carrier);
			break;
		case (static_cast<short>(shipType::Destroyer)):
			pToShip = new destroyer(_boardInterface.getFieldAddress(), _boardInterface.returnTypedDirection(), shipType::Destroyer);
			break;
		case (static_cast<short>(shipType::Hybrid)):
			pToShip = new hybrid(_boardInterface.getFieldAddress(), _boardInterface.returnTypedDirection(), shipType::Hybrid);
			break;
		case (static_cast<short>(shipType::Ubot)):
			pToShip = new u_bot(_boardInterface.getFieldAddress(), _boardInterface.returnTypedDirection(), shipType::Ubot);
			break;
		case (static_cast<short>(shipType::Scout)):
			pToShip = new scout(_boardInterface.getFieldAddress(), _boardInterface.returnTypedDirection(), shipType::Scout);
			break;
		defaul:
			break;
		}
	}
	catch (std::bad_alloc& exception) {
		cout << exception.what() << endl;
		std::terminate();
	}

	return pToShip;
}
///////////////////////////////////////////////////////////////////////////////////

//userDataInterface - main interface methods
/**
 * Assigning addresses of referenced objects and give iBoard interface order to prepare columns definition.
 * \param [in] _board Real board address.
 * \param [in] _player Real player address.
 */
userDataInterface::userDataInterface(board* _board, fleet* _player) {
	boardInterface.addressAssigment(_board);
	playerInterface.addressAssigment(_player);

	boardInterface.makeColumnsDefinition();
}

/**
 * Other interfaces initialize() method calls and initialize itself.
 */
void userDataInterface::initialize() noexcept(true) {
	boardInterface.initialize();
	playerInterface.initialize();
	shipInterface.initialize();

	initialized = true;
}

/**
 * Main method to manage user typed position. Position is typed, then checked if is valid, then checked if field is valid
 * and at the end user have to type direction.
 * \throw positionOcupied When \ref getFieldOccupation() method result is true.
 * \return Correctness state (true - position and direction typed correct, false - position is occupied).
 */
bool userDataInterface::manageUserTypedPosition() noexcept(false) {
	bool typedPositionValid = false;

	try {
		getUserType();
		if (boardInterface.isUserTypeCorrect()) {
			if (!boardInterface.getFieldOccupation()) {
				boardInterface.getDirection();

				typedPositionValid = true;
			}
			else throw(positionOcupied());
		}
	}
	catch (positionOcupied& exception) {
		cout << exception.what() << endl;
	}

	return typedPositionValid;
}

void userDataInterface::possibleShipsCalculation() {
	bool directionPlacement = boardInterface.returnTypedDirection();
	shipInterface.calculatePossibleShips(directionPlacement, boardInterface, playerInterface);
}

/**
 * Method is used to show player ships options to choose.
 */
void userDataInterface::showAvailableShipsInConsole() noexcept(false) {
	cout << "You have " << playerInterface.returnPoints() << " points.\n"
		<< "Possible ships in this area with your points : \n";

	for (int shipType = shipInterface.returnPossibleShips(); shipType > 0; shipType--) {
		cout << shipType << ") " << stringUserType[shipType] << " (" << shipType << " field)" << endl;
	}
}

/**
 * Method call \ref shipyard() to try place ship and if placement is succesfull 
 * then give order to board (through iBoard interface) to add it's address to vector.
 */
void userDataInterface::shipPlacement() noexcept(false) {
	ship* pToShip = shipInterface.shipyard(boardInterface);
	if (pToShip != nullptr) {
		boardInterface.addShip(pToShip);
	}
}

/**
 * Method used to update player point value after successfull ship placement process.
 * \return Feedback if player has still points (true - player has points, false - player points are 0).
 */
bool userDataInterface::pointsControll() noexcept(true) {
	playerInterface.updatePoints(shipInterface.returnChoosenShipType());
	return playerInterface.returnPoints();
}

/**
 * Method used to update references to real object stored in interfaces.
 * \param [in] _board Board address which should be assign as new object reference.
 * \param [in] _player Player address which should be assign as new object reference.
 */
void userDataInterface::reloadReferences(board* _board, fleet* _player) noexcept(true) {
	playerInterface.addressAssigment(_player);
	boardInterface.addressAssigment(_board);
}