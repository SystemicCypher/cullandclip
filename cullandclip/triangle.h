#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vecpt.h"
#include "Object.h"

class Triangle : public Object {
public:
    Triangle();

    Triangle(int objID, Vecpt pos, Vecpt A, Vecpt B, Vecpt C);

	Vecpt get_normal();

private:
	Vecpt vertices[3];
};

#endif