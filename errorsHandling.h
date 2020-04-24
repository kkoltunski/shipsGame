/*****************************************************************//**
 * \file   errorsHandling.h
 * \brief  Exceptions management
 * 
 * \author kkoltunski
 * \date   April 2020
***********************************************************************/

#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <iostream>
#include <string>

using std::string;

/**
 * Exception to throw when user type incorrect postion.
 */
struct incorrectPosition : std::exception
{
	incorrectPosition() {
		MSG = "Your type is not correct.\nInsert Column in range from A to ";
		MSG += ('@' + boardColumns);
		MSG += "\nInsert row in range from 1 - ";
		MSG += std::to_string(boardRows);
		MSG += "\nExample: A1 (ColumnRow)";
	}

	/// \return Exception description.
	virtual const char* what() const noexcept override {
		return MSG.c_str();
	}

private:
	string MSG;
};

/**
 * Exception to throw when user type position which field is already occupied.
 */
struct positionOcupied : std::exception
{
	positionOcupied() {
		MSG = "This position is occupied by other ship.";
	}

	/// \return Exception description.
	virtual const char* what() const noexcept override {
		return MSG.c_str();
	}

private:
	string MSG;
};

/**
 * Exception to throw when user type wrong ship type.
 */
struct wrongShipType : std::exception
{
	wrongShipType() {
		MSG = "Your type is wrong.";
	}

	/// \return Exception description.
	virtual const char* what() const noexcept override {
		return MSG.c_str();
	}

private:
	string MSG;
};

#endif // !ERRORHANDLING_H