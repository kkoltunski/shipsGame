#include "Tfleet.h"
#include "settings.h"

int Tfleet::Player = 1;

Tfleet& Tfleet::operator=(const Tfleet& In1){							//This constructor is not necessary (just for training - not so special bc type has no pointer/ref)
	if(this != &In1){
		Points = In1.Points;
		Name = In1.Name;
		
		Name[(Name.size()) - 1] = Name[(Name.size()) - 1] + 1;			//Increment player number (incrementing last char before termination)
	}
	
	return *this;
}

void Tfleet::UserDataHandshake(UserData &UI, int Mode) const{			//Simple data exchange
	if(!Mode){															//Player data => UserInterface flow								
		UI.Name = Name;
		UI.AvailablePoints = Points;
	}	
	else{																//UserInterface => Player data flow
		Points = UI.AvailablePoints;
	}
}
