//====================================
// Names:
// Austin Loza austinloza@csu.fullerton.edu
// Richard Ung rung921@csu.fullerton.edu
//====================================


#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
#include "vecpt.h"

class Camera : public Object {
public:
	Camera();

	// Vec3 d and u are unit vectors view direction and up
	Camera(int objID, Vecpt eye, float w, float h, int minSubPt, int dmax);

	float get_width();

	float get_height();

	int get_minSubPt();

	int get_dMax();



private:
	float _width;
	float _height;

	int _minSubPt;
	int _dMax;
};

#endif