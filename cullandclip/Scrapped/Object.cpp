//====================================
// Names:
// Austin Loza austinloza@csu.fullerton.edu
// Richard Ung rung921@csu.fullerton.edu
//====================================

#include "Object.h"


Object::Object() : _objID(-1), _kID(Kind::NONE), _ptReg() {}

Object::Object(int objID, Kind type, Vecpt pos) : _objID(objID), _kID(type), _ptReg(pos) {}

Object::~Object() {

}

const Kind Object::getKindID() const {
	return _kID;
}

const int Object::getObjectID() const {
	return _objID;
}

const Vecpt Object::getRegPt() const {
	return _ptReg;
}


void Object::setRegPt(Vecpt ptReg){
	_ptReg = ptReg;
}

void Object::setSubObjects(std::vector<KidLoc> kids){
	_subObjectPos = kids;
}

std::vector<KidLoc> Object::getKidsVec(){
	return _subObjectPos;
}
