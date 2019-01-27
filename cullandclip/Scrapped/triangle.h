//====================================
// Names:
// Austin Loza austinloza@csu.fullerton.edu
// Richard Ung rung921@csu.fullerton.edu
//====================================

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vecpt.h"
#include "Object.h"

class Triangle : public Object {
public:
    Triangle();

    Triangle(int objID, Vecpt pos, Vecpt A, Vecpt B, Vecpt C);

	Vecpt get_normal();

	Vecpt operator[](const int i);

	void operator=(Triangle tri);

	Vecpt get_vertex(int vert);

private:
	Vecpt vertices[3];
};

#endif
