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
//
//=======================================================================================

enum Kind { MODEL = 0, BAG = 1, TRIANGLE = 3, CAMERA = 9, NONE = -1 };

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
protected:
	vec3 _ptReg; // Offset from objects origin

private:
	int _objID;  // Object ID
	Kind _kID;   // Kind ID 

	LocalData _localData; // stores the objects in this objects space
	std::vector<KidLoc> _subObjectPos;
};


#endif