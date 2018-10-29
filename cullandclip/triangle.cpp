#include "triangle.h"

Triangle::Triangle() : Object(){
	
	vertices[0] = vec3();
	vertices[1] = vec3();
	vertices[2] = vec3();
	
}

Triangle::Triangle(int objID, vec3 pos, vec3 A, vec3 B, vec3 C) : Object(objID, Kind::TRIANGLE, pos) {
        vertices[0] = A;
        vertices[1] = B;
        vertices[2] = C;
    }
