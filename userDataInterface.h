#ifndef USERDATAINTERFACE_H
#define USERDATAINTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include <functional>
#include "settings.h"
#include "board.h"
#include "fleet.h"
#include "shipyard.h"
#include "errorsHandling.h"

class fleet;
class board;

struct iInitializer
{
protected:
	bool initialized;
public:
	virtual void initialize() noexcept(true) = 0;
};

template<typename T>
struct iAssigner
{
protected:
	const T* objectAddress;
public:
	virtual void addressAssigment(T* _in) noexcept(true) {
		objectAddress = _in;
	}
};

struct iBoardField : public iInitializer, public iAssigner<board>
{
protected:
	inline void convertRelativePositionCasesSize() noexcept(true) {
		for (auto& x : userTypedPosition) x = toupper(x);
	}
	void calculateRowAbsoluteValue() noexcept(true);
	void calculateColumnAbsoluteValue() noexcept(true);
	bool isTypedPositionValid() noexcept(true);

	string rowsDefinitions{ "123456789" };
	string columnsDefinitions{};
	string userTypedPosition;
	int absoluteRow;
	int	absoluteColumn;
	bool Dir;										//1 - vertical, 0 - horizontal	

public:
	inline string& setUserTypedPosition() noexcept(true) {
		return userTypedPosition;
	}
	inline void makeColumnsDefinition() noexcept(true) {
		for (int x = 0; x < boardColumns; x++) columnsDefinitions += 'A' + x;
	}
	inline bool returnTypedDirection() const noexcept(false) {
		return Dir;
	}
	inline int returnAbsoluteRow() const noexcept(true) {
		return absoluteRow;
	}
	inline int returnAbsoluteColumn() const noexcept(true) {
		return absoluteColumn;
	}
	void addShip(ship* _pToShip) noexcept(true);
	bool isUserTypeCorrect() noexcept(false);
	void getDirection() noexcept(true);
	bool isFieldOccupied(short _row = 0, short _column = 0) const noexcept(true);
	field* returnFieldAddress() const noexcept(true);


	virtual inline void initialize() noexcept(true) override {
		userTypedPosition = "";
		absoluteRow = 0;
		absoluteColumn = 0;
		Dir = false;
		initialized = true;
	}
};

struct iPlayer : public iInitializer, public iAssigner<fleet>
{
protected:
public:
	string returnPlayerName() const noexcept(true);
	void updatePoints(short _pointToUpdate) noexcept(true);
	int returnPoints() const noexcept(true); 

	virtual inline void initialize() noexcept(true) override {
		initialized = true;
	}
};

struct iShip : public iInitializer
{
protected:
	void calculateHorizontalPossibilities(const iBoardField&);
	void calculateVerticalPossibilities(const iBoardField&);
	void adjustPossibleShipValue(short _points) noexcept(true);

	mutable short shipType;
	short possibleShips;
	short horizontalDistanceToBorder;
	short verticalDistanceToBorder;

public:
	inline short returnPossibleShips() noexcept(true) {
		return possibleShips;
	}
	inline short returnChoosenShipType() noexcept(true) {
		return shipType;
	}
	void calculatePossibleShips(bool, const iBoardField&, const iPlayer&) noexcept(true);
	void getUserTypedShip() noexcept(true);
	ship* shipyard(const iBoardField& _boardInterface) noexcept(true);

	virtual inline void initialize() noexcept(true) override {
		shipType = 0;
		possibleShips = 0;
		horizontalDistanceToBorder = 0;
		verticalDistanceToBorder = 0;
		initialized = true;
	}
};

struct userDataInterface : public iInitializer
{
private:
	void inline getUserType() noexcept(true) {
		getline(std::cin, boardInterface.setUserTypedPosition(), '\n');
	}

	iBoardField boardInterface;
	iPlayer playerInterface;
	iShip shipInterface;

public:
	userDataInterface(board *_board, fleet *_player) {
		boardInterface.addressAssigment(_board);
		playerInterface.addressAssigment(_player);

		boardInterface.makeColumnsDefinition();
	}

	inline void setUserTypedPositionRequest() const noexcept(true) {
		cout << endl << playerInterface.returnPlayerName() << "\nType your position (ex. A1) : ";
	}
	inline void setShipTypeRequest() noexcept(true) {
		shipInterface.getUserTypedShip();
	}
	inline bool isOccupied() noexcept(true) {
		return boardInterface.isFieldOccupied();
	}
	bool manageUserTypedPosition() noexcept(false);
	void possibleShipsCalculation();
	void showAvailableShipsInConsole() noexcept(false);
	void shipPlacement() noexcept(false);
	bool pointsControll() noexcept(true);
	void reloadReferences(board* _board, fleet* _player) noexcept(true);
	virtual void initialize() noexcept(true) override;
};

#endif // !USERDATAINTERFACE_H