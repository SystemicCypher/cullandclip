#include "Object.h"

Object::Object() : _objID(-1), _kID(Kind::NONE), _ptReg() {}

Object::Object(int objID, Kind type, vec3 pos) : _objID(objID), _kID(type), _ptReg(pos) {}

Object::~Object() {
	//for (auto data : _localData) {
	//	for (auto &obj : data.second) {
	//		delete obj;
	//	}
	//	_localData.erase(data);
	//}
}

const Kind Object::getKindID() const {
	return _kID;
}

const int Object::getObjectID() const {
	return _objID;
}

const vec3 Object::getRegPt() const {
	return _ptReg;
}

void Object::addSubObject(KidLoc kl, std::shared_ptr<Object> &data) {
	Kind id = data->getKindID();

	// If no sub-objects of that kind were stored, create an entry for that kind
	if (_localData.count(id) == 0) {
		_localData[id] = ObjectVec();
	}

	// Add data to that Kind's vector
	_localData[id].push_back(data);

	// Space inside this object
	vec3 posInSpace = _ptReg + data->getRegPt();
	 _subObjectPos.emplace_back(data->getObjectID(), Placement(posInSpace, 0.0f, 0.0f));
}

std::shared_ptr<Object> Object::getObject(Kind kID, int objID) {
	return (_localData.count(kID) > 0) ?
		_localData[kID][objID] :
		nullptr;
}