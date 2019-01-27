//====================================
// Names:
// Austin Loza austinloza@csu.fullerton.edu
// Richard Ung rung921@csu.fullerton.edu
//====================================

#include "triangle.h"

Triangle::Triangle() : Object(){
	
	vertices[0] = Vecpt();
	vertices[1] = Vecpt();
	vertices[2] = Vecpt();
	
}

Triangle::Triangle(int objID, Vecpt pos, Vecpt A, Vecpt B, Vecpt C) : Object(objID, Kind::TRIANGLE, pos) {
        vertices[0] = A;
        vertices[1] = B;
        vertices[2] = C;
 }

Vecpt Triangle::get_normal() {
	Vecpt v1 = vertices[1] - vertices[0];
	Vecpt v2 = vertices[2] - vertices[1];

	return v2.cross(v1);
}

Vecpt Triangle::operator[](const int i) {
	if (i >= 0 && i < 3) {
		return vertices[i];
	}

	throw std::out_of_range("Out of bounds access on triangle");
	
}

void Triangle::operator=(Triangle tri){
	vertices[0] = tri.get_vertex(0);
	vertices[1] = tri.get_vertex(1);
	vertices[2] = tri.get_vertex(2);
	_objID = tri.getObjectID();
	_kID = tri.getKindID();
	_ptReg = tri.getRegPt();	
}

Vecpt Triangle::get_vertex(int vert){
	return vertices[vert];
}
