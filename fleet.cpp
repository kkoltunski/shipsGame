#include "fleet.h"

int fleet::playerNumber = 1;

fleet& fleet::operator=(const fleet& In1){						//This constructor is not necessary (just for training - not so special bc type has no pointer/ref)
	if(this != &In1){
		points = In1.points;
		ID = In1.ID;
		
		ID[(ID.size()) - 1] = ID[(ID.size()) - 1] + 1;			//Increment player number (incrementing last char before termination)
	}
	
	return *this;
}

