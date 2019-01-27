#include "Placement.h"

Placement::Placement() : ptReg(), azimuth(0.0f), elevation(0.0f) { }

// Takes an object ID, azimuth, and elevation of the kid
Placement::Placement(Vecpt ptReg, float az, float ele) : ptReg(ptReg), azimuth(az), elevation(ele) { }