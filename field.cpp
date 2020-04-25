#include "field.h"
#include "shipyard.h"

/**
 * \brief Copy operator (Training purposes).
 * 
 * It copy only ocupation.
 * 
 * \param [in] _originalField Reference to original field.
 * \return Copy address.
 */
field& field::operator=(field& _originalField) {
	if (this != &_originalField){
		if (pToShip != nullptr)	delete pToShip;

		occupiedByShip = _originalField.occupiedByShip;
        pToShip = nullptr;
	}
	return *this;
}

field::~field(){

}