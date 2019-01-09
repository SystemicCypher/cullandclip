//====================================
// Names:
// Austin Loza austinloza@csu.fullerton.edu
// Richard Ung rung921@csu.fullerton.edu
//====================================

#ifndef OBJECT_H
#define OBJECT_H

#include "Placement.h"
#include "vecpt.h"
#include <vector>


//=======================================================================================
// OBJECT CLASS 
// ======================================================================================
// Base class object for all KINDS of objects (model space, triangles, bag, camera)
// Can dynamic_cast down to sub classes
//=======================================================================================

enum Kind { MODEL, BAG = 1, TRIANGLE = 3, CAMERA = 9, NONE = -1 };

typedef int KidID;


typedef std::pair<KidID, Placement> KidLoc;

class Object {
public:
	Object();

	Object(int objID, Kind type, Vecpt pos);

	~Object();


// Getters
	virtual void nothing(){};
	const Kind getKindID() const;

	const int getObjectID() const;

	const Vecpt getRegPt() const;

	std::vector<KidLoc> getKidsVec();
// Setters
	void setRegPt(Vecpt ptReg);

	void setSubObjects(std::vector<KidLoc> kids);

protected:
	int _objID;  // Object ID
	Kind _kID;   // Kind ID 
	Vecpt _ptReg; // Offset from objects origin

	std::vector<KidLoc> _subObjectPos;
};


#endif
