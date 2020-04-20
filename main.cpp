#include "header.h"

int main(){
	int counter {0};
	userDataInterface UI(BoardAddressTab[counter], PlayerAddressTab[counter]);

	cout << "*****FIRST STAGE - PLACE YOUR SHIP*****\n"
		 <<"\nBoard overview\n";
		 BoardAddressTab[0]->drawBoard();
	
	do{	
		UI.initialize();
		UI.setUserTypedPositionRequest();
		if (UI.manageUserTypedPosition()) {
			UI.possibleShipsCalculation();
			UI.showAvailableShipsInConsole();
			UI.setShipTypeRequest();
			UI.shipPlacement();
			if(!UI.pointsControll()) {
				if(++counter < 2) UI.reloadReferences(BoardAddressTab[counter], PlayerAddressTab[counter]);
			}
		}
	}
	while(counter < 2);
	
	cout << "\nPlayer1 borard : \n";
	BoardAddressTab[0]->drawBoard();
	cout << "\nPlayer2 borard : \n";
	BoardAddressTab[1]->drawBoard();
	
	cout << "\n*****FIRST STAGE IS OVER - PREPARE TO BATTLE*****\n" << endl;
	return 0;
}
