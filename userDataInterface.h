/*****************************************************************//**
 * \file   userDataInterface.h
 * \brief  Interfaces used as communication between user and software
 * 
 * \author kkoltunski
 * \date   April 2020
***********************************************************************/

#ifndef USERDATAINTERFACE_H
#define USERDATAINTERFACE_H

#include "board.h"
#include "fleet.h"
#include "shipyard.h"
#include "errorsHandling.h"

class fleet;
class board;

/**
 * Partial, abstract interface which is used to initializing other interfaces.
 */
struct iInitializer
{
protected:
	///Information if interface is initialized.
	bool initialized;
public:
	///Abstract method to initialize interface.
	virtual void initialize() noexcept(true) = 0;
};

/**
 * Template interface which is used to assigning reference to real object.
 */
template<typename T>
struct iAssigner
{
protected:
	///Address of real <T> object.
	const T* objectAddress;
public:
	/**
	 * Method to make assigment of object address.
	 * \param [in] _in Address to real object.
	 */
	virtual void addressAssigment(T* _in) noexcept(true) {
		objectAddress = _in;
	}
};

/**
 * Partial interface of main interface. Is used to geting informations from real board and giving it orders.
 */
struct iBoard : public iInitializer, public iAssigner<board>
{
private:
	iBoard() {
		initialize();
	}
	///Converting string size to upper cases.
	inline void convertRelativePositionCasesSize() noexcept(true) {
		for (auto& x : userTypedPosition) x = toupper(x);
	}
	///Method to calculat absolute row value.
	void calculateRowAbsoluteValue() noexcept(true);
	///Method to calculat absolute columns value.
	void calculateColumnAbsoluteValue() noexcept(true);
	///Method to check if typed position is valid.
	bool isTypedPositionValid() noexcept(true);

	string rowsDefinitions{ "123456789" };
	string columnsDefinitions{};
	string userTypedPosition;
	int absoluteRow;
	int	absoluteColumn;
	bool Dir;										//1 - vertical, 0 - horizontal	

public:
	///Returns information about typed position.
	inline string& setUserTypedPosition() noexcept(true) {
		return userTypedPosition;
	}
	///Preparing columns definitions.
	inline void makeColumnsDefinition() noexcept(true) {
		for (int x = 0; x < boardColumns; x++) columnsDefinitions += 'A' + x;
	}
	///Returns information about typed direction.
	inline bool returnTypedDirection() const noexcept(false) {
		return Dir;
	}
	///Returns calculated absolute row.
	inline int returnAbsoluteRow() const noexcept(true) {
		return absoluteRow;
	}
	///Returns calculated absolute column.
	inline int returnAbsoluteColumn() const noexcept(true) {
		return absoluteColumn;
	}
	///Order add ship.
	void addShip(ship* _pToShip) noexcept(true);
	///Checking user typed position.
	bool isUserTypeCorrect() noexcept(false);
	///Set request about direction.
	void getDirection() noexcept(true);
	///Rate if field is occupied.
	bool getFieldOccupation(short _row = 0, short _column = 0) const noexcept(true);
	///Get address of typed field.
	field* getFieldAddress() const noexcept(true);

	///Method to initialize interface.
	virtual inline void initialize() noexcept(true) override {
		userTypedPosition = "";
		absoluteRow = 0;
		absoluteColumn = 0;
		Dir = false;
		initialized = true;
	}

	///Main interface which is allow to construct this interface.
	friend class userDataInterface;
};

/**
 * Partial interface of main interface. Is used to geting informations from real player and giving it orders.
 */
struct iPlayer : public iInitializer, public iAssigner<fleet>
{
private:
	///Default constructor.
	iPlayer() {
		initialize();
	}

public:
	///Return player name.
	string returnPlayerName() const noexcept(true);
	///Updating player points after ship placement.
	void updatePoints(short _pointToUpdate) noexcept(true);
	///Return available player points.
	int returnPoints() const noexcept(true); 

	///Method to initialize interface.
	virtual inline void initialize() noexcept(true) override {
		initialized = true;
	}

	///Main interface which is allow to construct this interface.
	friend class userDataInterface;
};

/**
 * Partial interface of main interface. Is used to manage ship placement process.
 */
struct iShip : public iInitializer
{
private:
	///Default constructor.
	iShip() {
		initialize();
	}
	///Possible ships calculation.
	void calculateHorizontalPossibilities(const iBoard&);
	///Possible ships calculation.
	void calculateVerticalPossibilities(const iBoard&);
	///Correcting possible ship value
	void adjustPossibleShipValue(short _points) noexcept(true);

	mutable short shipType;
	short possibleShips;
	short horizontalDistanceToBorder;
	short verticalDistanceToBorder;

public:
	///Return possible ships value.
	inline short returnPossibleShips() noexcept(true) {
		return possibleShips;
	}
	///Return choosen ship type.
	inline short returnChoosenShipType() noexcept(true) {
		return shipType;
	}
	///Possible ship calculation.
	void calculatePossibleShips(bool, const iBoard&, const iPlayer&) noexcept(true);
	///Type ship request.
	void getUserTypedShip() noexcept(true);
	///Ship factory.
	ship* shipyard(const iBoard& _boardInterface) noexcept(true);

	///Method to initialize interface.
	virtual inline void initialize() noexcept(true) override {
		shipType = 0;
		possibleShips = 0;
		horizontalDistanceToBorder = 0;
		verticalDistanceToBorder = 0;
		initialized = true;
	}

	///Main interface which is allow to construct this interface.
	friend class userDataInterface;
};

class userDataInterface : public iInitializer
{
	/**
	 * xxxx
	 */
private:
	///User type request.
	void inline getUserType() noexcept(true) {
		getline(std::cin, boardInterface.setUserTypedPosition(), '\n');
	}

	iBoard boardInterface;
	iPlayer playerInterface;
	iShip shipInterface;

public:
	///Default constructor.
	userDataInterface(board* _board, fleet* _player);

	///Request to type position.
	inline void setUserTypedPositionRequest() const noexcept(true) {
		cout << endl << playerInterface.returnPlayerName() << "\nType your position (ex. A1) : ";
	}
	///Request to type ship type.
	inline void setShipTypeRequest() noexcept(true) {
		shipInterface.getUserTypedShip();
	}
	///Request to iBoard interface if typed field is occupied.
	inline bool isOccupied() noexcept(true) {
		return boardInterface.getFieldOccupation();
	}
	///User typed postion request.
	bool manageUserTypedPosition() noexcept(false);
	///Possible ships calculation order.
	void possibleShipsCalculation();
	///Showing options in console.
	void showAvailableShipsInConsole() noexcept(false);
	///Main method to call ship placement process.
	void shipPlacement() noexcept(false);
	//Points managment.
	bool pointsControll() noexcept(true);
	///Object references update.
	void reloadReferences(board* _board, fleet* _player) noexcept(true);

	///Method to initialize interfaces.
	virtual void initialize() noexcept(true) override;
};

#endif // !USERDATAINTERFACE_H