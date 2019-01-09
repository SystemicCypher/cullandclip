
//====================================
// Names:
// Austin Loza austinloza@csu.fullerton.edu
// Richard Ung rung921@csu.fullerton.edu
//====================================

#ifndef PLACEMENT_H
#define PLACEMENT_H

#include "vecpt.h"

struct Placement {
	Placement();

	// Takes an object ID, azimuth, and elevation of the kid
	Placement(Vecpt ptReg, float az, float ele);

	Vecpt ptReg;
	float azimuth;
	float elevation;
};

#endif