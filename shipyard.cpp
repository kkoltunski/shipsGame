#include "shipyard.h"
#include "settings.h"

/**
 * Basic ship parameters initialization. 
 * \param [in] _pos Address of field where ship should be placed.
 * \param [in] _dir Direction in which ship should be allocated.
 * \param [in] _type Type of ship. Because of enum class, it can be translate to int.
 */
ship::ship(field* _pos, bool _dir, shipType _type) : initialFieldAddress{ _pos }, placementDirection{ _dir }, type{ _type }{
	multiplier = (_dir ? boardColumns : 1);
}

void ship::allocator() {
	for (int x = 0; x < static_cast<int>(type); x++) {
		initialFieldAddress[x * multiplier].occupiedByShip = true;
		initialFieldAddress[x * multiplier].shipDirection = placementDirection;
		initialFieldAddress[x * multiplier].pToShip = this;
	}
}

/**
 * Initialize inherited part and then alocate ship.
 * \param [in] _initialFieldAddress Address of field where ship should be placed.
 * \param [in] _shipDirection Direction in which ship should be allocated.
 * \param [in] _type Type of ship. Because of enum class, it can be translate to int.
 */
scout::scout(field* _initialFieldAddress, bool _shipDirection, shipType _type) : ship(_initialFieldAddress, _shipDirection, _type) {
	allocator();
}

/**
 * Initialize inherited part and then alocate ship.
 * \param [in] _initialFieldAddress Address of field where ship should be placed.
 * \param [in] _shipDirection Direction in which ship should be allocated.
 * \param [in] _type Type of ship. Because of enum class, it can be translate to int.
 */
u_bot::u_bot(field* _initialFieldAddress, bool _shipDirection, shipType _type) : ship(_initialFieldAddress, _shipDirection, _type) {
	allocator();
}

/**
 * Initialize inherited part and then alocate ship.
 * \param [in] _initialFieldAddress Address of field where ship should be placed.
 * \param [in] _shipDirection Direction in which ship should be allocated.
 * \param [in] _type Type of ship. Because of enum class, it can be translate to int.
 */
hybrid::hybrid(field* _initialFieldAddress, bool _shipDirection, shipType _type) : ship(_initialFieldAddress, _shipDirection, _type) {
	allocator();
}

/**
 * Initialize inherited part and then alocate ship.
 * \param [in] _initialFieldAddress Address of field where ship should be placed.
 * \param [in] _shipDirection Direction in which ship should be allocated.
 * \param [in] _type Type of ship. Because of enum class, it can be translate to int.
 */
destroyer::destroyer(field* _initialFieldAddress, bool _shipDirection, shipType _type) : ship(_initialFieldAddress, _shipDirection, _type) {
	allocator();
}

/**
 * Initialize inherited part and then alocate ship.
 * \param [in] _initialFieldAddress Address of field where ship should be placed.
 * \param [in] _shipDirection Direction in which ship should be allocated.
 * \param [in] _type Type of ship. Because of enum class, it can be translate to int.
 */
aircraft_carrier::aircraft_carrier(field* _initialFieldAddress, bool _shipDirection, shipType _type) : ship(_initialFieldAddress, _shipDirection, _type) {
	allocator();
}