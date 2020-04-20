#include "field.h"

field& field::operator=(field& _in) {
	if (this != &_in) {
		if (pToShip != nullptr)	delete pToShip;

		occupiedByShip = _in.occupiedByShip;
	}
	return *this;
}