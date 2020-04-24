#include "fleet.h"

int fleet::playerNumber = 1;

/**
 * Assigning points and name.
 * 
 * \param _points [in] Should be used global variable \ref fleetPoints.
 * \param _name [in] Alleged parameter is "Player X". In the future there will be possibilities to define your own name.
 */
fleet::fleet(int _points, string&& _name) : points(_points), ID(_name)
{
}

/**
 * Principle of operation is similar to copy "byte by byte" but player number is increased.
 * \param [in[ orginalFleet Reference to original fleet.
 * \return Address to copy.
 */
fleet& fleet::operator=(const fleet& orginalFleet){
	if(this != &orginalFleet){
		points = orginalFleet.points;
		ID = orginalFleet.ID;
		
		ID[(ID.size()) - 1] = ID[(ID.size()) - 1] + 1;
	}
	
	return *this;
}

