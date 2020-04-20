#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <iostream>
#include <string>
#include "settings.h"

using std::string;

struct incorrectPosition : std::exception
{
	incorrectPosition() {
		MSG = "Your type is not correct.\nInsert Column in range from A to ";
		MSG += ('@' + boardColumns);
		MSG += "\nInsert row in range from 1 - ";
		MSG += std::to_string(boardRows);
		MSG += "\nExample: A1 (ColumnRow)";
	}

	virtual const char* what() const noexcept override {
		return MSG.c_str();
	}

private:
	string MSG;
};

struct positionOcupied : std::exception
{
	positionOcupied() {
		MSG = "This position is occupied by other ship.";
	}

	virtual const char* what() const noexcept override {
		return MSG.c_str();
	}

private:
	string MSG;
};

struct wrongShipType : std::exception
{
	wrongShipType() {
		MSG = "Your type is wrong.";
	}

	virtual const char* what() const noexcept override {
		return MSG.c_str();
	}

private:
	string MSG;
};

#endif // !ERRORHANDLING_H