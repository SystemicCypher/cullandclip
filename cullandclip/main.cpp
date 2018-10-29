#include "single-include.h"


Kind kindID_to_enum(int ID) {
	Kind enuID;
	switch (ID) {
	case 0:
		enuID = Kind::MODEL;
		break;
	case 1:
		enuID = Kind::BAG;
		break;
	case 3:
		enuID = Kind::TRIANGLE;
		break;
	case 9:
		enuID = Kind::CAMERA;
		break;
	default:
		enuID = Kind::NONE;
		break;
	}
	return enuID;
}

int enum_to_kindID(Kind ID) {
	int kindID;
	switch (ID) {
	case Kind::MODEL:
		kindID = 0;
		break;
	case Kind::BAG:
		kindID = 1;
		break;
	case Kind::TRIANGLE:
		kindID = 3;
		break;
	case Kind::CAMERA:
		kindID = 9;
		break;
	default:
		kindID = -1;
		break;
	}
	return kindID;
}


int main(){
	std::string line, locals, kid_loc;
	int objID, KindID;
	float reg1, reg2, reg3;
	std::stringstream stream;
	while (getline(std::cin, line)) {
		stream.str(line);
		stream >> objID >> KindID >> reg1 >> reg2 >> reg3 >> locals >> kid_loc; // only accepts one at a time at the moment
		
		Kind enuID = kindID_to_enum(KindID);
		vec3  vect(reg1, reg2, reg3);
		Object test(objID, enuID, vect);
		vec3 output = test.getRegPt();
		std::cout << enum_to_kindID(enuID) << " " << output[0] << " " << output[1] << " " << output[2];


	}
    return 0;
}