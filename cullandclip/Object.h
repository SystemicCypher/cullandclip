#ifndef OBJECT_H
#define OBJECT_H

#include "Placement.h"
#include "vec3.h"

#include <unordered_map>
#include <vector>
#include <memory>

//=======================================================================================
// OBJECT CLASS 
// ======================================================================================
// Base class object for all KINDS of objects (model space, triangles, bag, camera)
// Can dynamic_cast down to sub classes
//=======================================================================================

enum Kind { MODEL, BAG, TRIANGLE = 3, CAMERA = 9, NONE = -1 };

typedef int KidID;

class Object {
	typedef std::vector < std::shared_ptr<Object> > ObjectVec;
	typedef std::unordered_map< Kind, ObjectVec > LocalData;
	typedef std::pair<KidID, Placement> KidLoc;

public:
	Object();

	Object(int objID, Kind type, vec3 pos);

	~Object();

	void addSubObject(KidLoc kl, std::shared_ptr<Object> &data);

	std::shared_ptr<Object> getObject(Kind kID, int objID);

	const Kind getKindID() const;

	const int getObjectID() const;

	const vec3 getRegPt() const;

	// SEE PAGE 44 for near plane points

protected:
	int _objID;  // Object ID
	Kind _kID;   // Kind ID 
	vec3 _ptReg; // Offset from objects origin

	LocalData _localData; // stores the objects in this objects space
	std::vector<KidLoc> _subObjectPos;
};


#endif