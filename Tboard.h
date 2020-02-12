#ifndef TBOARD_H
#define TBOARD_H

/*This class is used as whole board*/
#include "Tfield.h"
#include "Tship.h"
#include "Taircraft_carrier.h"
#include <vector>

using std::vector;
struct UserData;

class Tboard
{
	private:		
		Tfield *Area {nullptr};									//Beggining of allocated area for field addresser
		vector<vector<Tfield*>> Net;							//Fields addresses in board
		vector<Tship*> Ships;									//Vector of pointers to created ships on this board
		
		int ShipSelector(const UserData &UI, int Selector);		//Function to show possibilities on console
		bool CreateShip(const Tfield *_pos, int Type, bool _dir);		
		
		
	public:
		Tboard();
		Tboard(const Tboard &In1);
		
		~Tboard();
		
		void showAddresses();
		void DrawBoard();
		bool CheckPos(const UserData &UI);						//function to check if it is possible to put ship on typed position
		static inline const Tfield* RetPosAddr(Tboard &ref, int X, int Y){
			return  ref.Net[X][Y];
		}
		
		friend class Tfleet;
		friend class Tship;
		//friend class Taircraft_carrier;
};

#endif
