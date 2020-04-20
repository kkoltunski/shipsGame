#include "shipyard.h"
#include "settings.h"

void ship::allocator() {
	for (int x = 0; x < static_cast<int>(type); x++) {
		initialFieldAddress[x * multiplier].occupiedByShip = true;
		initialFieldAddress[x * multiplier].shipDirection = placementDirection;
		initialFieldAddress[x * multiplier].pToShip = this;
	}
}

