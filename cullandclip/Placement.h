#ifndef PLACEMENT_H
#define PLACEMENT_H

#include "vec3.h"

struct Placement {
	Placement() : ptReg(), azimuth(0.0f), elevation(0.0f) { }

	// Takes an object ID, azimuth, and elevation of the kid
	Placement(vec3 ptReg, float az, float ele) : ptReg(ptReg), azimuth(az), elevation(ele) { }

	vec3 ptReg;
	float azimuth;
	float elevation;
};

#endif