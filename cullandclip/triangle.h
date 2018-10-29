#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"
#include "vec3.h"


class Triangle : public Object {
public:
    Triangle();

    Triangle(int objID, vec3 pos, vec3 A, vec3 B, vec3 C);



private:
	vec3 vertices[3];
};

#endif