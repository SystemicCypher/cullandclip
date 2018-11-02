#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"

class Rectangle {
public:
	Rectangle() {}
	Rectangle(float x, float y, float z, float w, float h) :
		_x(x), _y(y), _z(z), _w(w), _h(h) 
	{}

	///  Might be wrong if the rectangle is rotated?

	const float getTop() const { return _z; }
	
	const float getBot() const { return _z + _h; }

	const float getLeft()  const { return _y; }
	
	const float getRight() const { return _y + _w; }

private:
	float _x;   // . (point towards you)
	float _y;	// -
	float _z;   // |
	float _w;
	float _h;
};

class Camera : public Object {
public:
	Camera() {}
	Camera(float w, float h, float dmin, float dmax, int objID, Kind type, vec3 pt) : 
		Object(objID, type, pt),
		_width(w), 
		_height(h),
		_dMin(dmin),
		_dMax(dmax)
	{
		// Center the rectangle (probably wrong if factoring of rotation)
		float nx = pt[0] + dmin;
		float ny = pt[1] - (h / 2);
		float nz = pt[2] - (w / 2);

		_nearPlane = Rectangle(nx, ny, nz, w, h);

		_ptMinSub = vec3(nx, ny, nz);
	}

	vec3 getEye() { 
		return _ptReg; 
	}



private:
	float _width;
	float _height;
	float _dMin;
	float _dMax;

	vec3 _ptMinSub;
	Rectangle _nearPlane;
	//Rectangle _farPlane;  Might need a far plane saved
};

#endif