#include "header.h"

int main(){
	int queueCounter {0};
																			//counter to pointers tables of fleet and board
	cout << "*****FIRST STAGE - PLACE YOUR SHIP*****\n"
		 <<"\nBoard overview\n";
		 BoardAddressTab[0]->DrawBoard();		 							//Show example - doesnt matter which board will be shown
	
	do{																		//I Stage - put ships on players board and check their points
		fflush(stdin);														//before/after use istream - make clereance of istream
		UI = Empty;															//initialize before every use
		
		PlayerAddressTab[queueCounter]->UserDataHandshake(UI, 0);			//Player data => UserInterface flow
		cout << endl << UI.Name << "\nType your position (ex. A1) : ";
		bool CheckPoints = (BoardAddressTab[queueCounter]->CheckPos(UI.UserToAbs(getline(std::cin, UI.Relative))) > 0 ? true : false);	//If result of CheckPos func. is > 0 then check points
		PlayerAddressTab[queueCounter]->UserDataHandshake(UI, 1);			//UserInterface => Player data flow
		
		if(CheckPoints && !(UI.AvailablePoints > 0)) ++queueCounter;		//If ship was created and player doesn't have points then increase queueCounter
			
	}
	while(queueCounter < 2);
	
	cout << "\nPlayer1 borard : \n";
	BoardAddressTab[0]->DrawBoard();
	cout << "\nPlayer2 borard : \n";
	BoardAddressTab[1]->DrawBoard();
	
	cout << "\n*****FIRST STAGE IS OVER - PREPARE TO BATTLE*****\n" << endl;
	return 0;
}
