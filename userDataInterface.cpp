#include "userDataInterface.h"

//iBoard interface methods
inline bool iBoardField::isTypedPositionValid() noexcept(true) {
	bool result{ true };
	if (userTypedPosition.find_first_of(columnsDefinitions) == string::npos) result = false;
	if (userTypedPosition.find_first_of(rowsDefinitions) == string::npos) result = false;

	return result;
}

void iBoardField::calculateColumnAbsoluteValue() noexcept(true) {
	size_t columnPosition = userTypedPosition.find_first_of(columnsDefinitions);
	char nextChar = userTypedPosition[columnPosition + 1];

	absoluteColumn = (userTypedPosition[columnPosition] - 'A');

	if (boardColumns > 26)
		if ((nextChar >= 'A') && (nextChar <= 'Z')) absoluteColumn += (nextChar - 39);				//e.g column position AA => for 1'st digit (A) absoluteColumn = 0, for 2'nd digit (A) absoluteColumn = (65-39) = 26 

	absoluteColumn = (absoluteColumn > (boardColumns - 1) ? (boardColumns - 1) : absoluteColumn);
}

void iBoardField::calculateRowAbsoluteValue() noexcept(true) {
	size_t rowPosition = userTypedPosition.find_first_of(rowsDefinitions);
	string help = userTypedPosition.substr(rowPosition, 2);

	absoluteRow = (std::stoi(help) - 1);
	absoluteRow = (absoluteRow > (boardRows - 1) ? (boardRows - 1) : absoluteRow);
}

bool iBoardField::isUserTypeCorrect() noexcept(false) {
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

void iBoardField::getDirection() noexcept(true) {
	char typedDirection;

	do {
		cout << "Type direction.\nh - horizontal, v - vertical.\nYour type: ";

		cin.get(typedDirection);
		cin.ignore();

		typedDirection = toupper(typedDirection);
	} while (!((typedDirection == 'H') || (typedDirection == 'V')));

	Dir = (typedDirection == 'V' ? true : false);
}

bool iBoardField::isFieldOccupied(short _row, short _column) const noexcept(true) {
	return objectAddress->fieldAdresses[absoluteRow + _row][absoluteColumn + _column]->occupiedByShip;
}

field* iBoardField::returnFieldAddress() const noexcept(true) {
	return objectAddress->fieldAdresses[absoluteRow][absoluteColumn];
}

void iBoardField::addShip(ship* _pToShip) noexcept(true) {
	objectAddress->createdShips.push_back(_pToShip);
}
///////////////////////////////////////////////////////////////////////////////////

//iPlayer interface methods
string iPlayer::returnPlayerName() const noexcept(true) {
	return objectAddress->ID;
}

void iPlayer::updatePoints(short _pointToUpdate) noexcept(true) {
	objectAddress->points -= _pointToUpdate;
}

int iPlayer::returnPoints() const noexcept(true) {
	return objectAddress->points;
}
///////////////////////////////////////////////////////////////////////////////////

//iShip interface methods
void iShip::calculatePossibleShips(bool _direction, const iBoardField& _boardInterface, const iPlayer& _playerInterface) noexcept(true) {

	if (_direction) calculateVerticalPossibilities(_boardInterface);
	else calculateHorizontalPossibilities(_boardInterface);

	adjustPossibleShipValue(_playerInterface.returnPoints());
}

void iShip::calculateVerticalPossibilities(const iBoardField& _boardInterface) {
	verticalDistanceToBorder = (boardRows - _boardInterface.returnAbsoluteRow());

	for (possibleShips = 0; possibleShips < verticalDistanceToBorder; possibleShips++) {
		if (_boardInterface.isFieldOccupied(possibleShips, 0))	break;
	}
}

void iShip::calculateHorizontalPossibilities(const iBoardField& _boardInterface) {
	horizontalDistanceToBorder = (boardColumns - _boardInterface.returnAbsoluteColumn());

	for (possibleShips = 0; possibleShips < horizontalDistanceToBorder; possibleShips++) {
		if (_boardInterface.isFieldOccupied(0, possibleShips))	break;
	}
}

void iShip::adjustPossibleShipValue(short _points) noexcept(true) {
	possibleShips = ((possibleShips > highestPossibleShipType) ? highestPossibleShipType : possibleShips);
	possibleShips = ((possibleShips > _points) ? _points : possibleShips);
}

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

		cin.clear(0);														//VisualStudio bug??????? - have to introduce value 2 times
		cin.ignore();
		cin >> typedShip;
		if (cin.fail()) cout << "Wrong type." << endl;

	} while ((typedShip > possibleShips) || (typedShip < 0) || cin.fail());
	cin.ignore();

	shipType = typedShip;
}

ship* iShip::shipyard(const iBoardField& _boardInterface) noexcept(true) {
	ship* pToShip{ nullptr };
	try {
		switch (shipType) {
		case (static_cast<short>(shipType::Aircraft_carrier)):
			pToShip = new aircraft_carrier(_boardInterface.returnFieldAddress(), _boardInterface.returnTypedDirection(), shipType::Aircraft_carrier);
			break;
		case (static_cast<short>(shipType::Destroyer)):
			pToShip = new destroyer(_boardInterface.returnFieldAddress(), _boardInterface.returnTypedDirection(), shipType::Destroyer);
			break;
		case (static_cast<short>(shipType::Hybrid)):
			pToShip = new hybrid(_boardInterface.returnFieldAddress(), _boardInterface.returnTypedDirection(), shipType::Hybrid);
			break;
		case (static_cast<short>(shipType::Ubot)):
			pToShip = new u_bot(_boardInterface.returnFieldAddress(), _boardInterface.returnTypedDirection(), shipType::Ubot);
			break;
		case (static_cast<short>(shipType::Scout)):
			pToShip = new scout(_boardInterface.returnFieldAddress(), _boardInterface.returnTypedDirection(), shipType::Scout);
			break;
		defaul:
			break;
		}
	}
	catch (std::bad_alloc& exception) {
		cout << exception.what() << endl;
		terminate();
	}

	return pToShip;
}
///////////////////////////////////////////////////////////////////////////////////

//userDataInterface - main interface methods
void userDataInterface::initialize() noexcept(true) {
	boardInterface.initialize();
	playerInterface.initialize();
	shipInterface.initialize();

	initialized = true;
}

bool userDataInterface::manageUserTypedPosition() noexcept(false) {
	bool typedPositionValid = false;

	try {
		getUserType();
		if (boardInterface.isUserTypeCorrect()) {
			if (!boardInterface.isFieldOccupied()) {
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

void userDataInterface::showAvailableShipsInConsole() noexcept(false) {
	cout << "You have " << playerInterface.returnPoints() << " points.\n"
		<< "Possible ships in this area with your points : \n";

	for (int shipType = shipInterface.returnPossibleShips(); shipType > 0; shipType--) {
		cout << shipType << ") " << stringUserType[shipType] << " (" << shipType << " field)" << endl;
	}
}

void userDataInterface::shipPlacement() noexcept(false) {
	ship* pToShip = shipInterface.shipyard(boardInterface);
	boardInterface.addShip(pToShip);
}

bool userDataInterface::pointsControll() noexcept(true) {
	playerInterface.updatePoints(shipInterface.returnChoosenShipType());
	return playerInterface.returnPoints();
}

void userDataInterface::reloadReferences(board* _board, fleet* _player) noexcept(true) {
	playerInterface.addressAssigment(_player);
	boardInterface.addressAssigment(_board);
}