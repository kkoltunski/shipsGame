#include "Tship.h"
#include "settings.h"

Tship::Tship(Tfield *_pos, int _type, bool _dir){
	if(!_pos->Occupied){												//if field is not occupied then mark it as occupied 
		if(_type > MaxType )	_type = MaxType;						//maxium of enum Type (member)
		else if(_type < MinType)	_type = MinType;					//maxium of enum Type (member)
			
		Begining = _pos;												//information for Tship 
		Direction = _dir;
		Name = static_cast<Type>(_type);								
		
		int Multiplier = (_dir ? BoardColumns : 1);						//If true then multiplier is equivalent of columns, if false then multiplier checking next cell
		
		for(int x = 0; x < _type; x++){									//information to Field
			_pos[x * Multiplier].Occupied = true;
			_pos[x * Multiplier].Typ = Name;
			_pos[x * Multiplier].pToShip = this;
		}
	}
}
