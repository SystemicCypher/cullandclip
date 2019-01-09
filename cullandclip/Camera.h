#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
#include "ViewFrustrum.h"

class Rectangle {
public:
	Rectangle() {}
	Rectangle(float x, float y, float z, float w, float h) :
		_x(x), _y(y), _z(z), _w(w), _h(h) 
	{}

	const float getTop() const { return _z; }
	
	const float getBot() const { return _z + _height; }

	const float getLeft()  const { return _y; }
	
	const float getRight() const { return _y + _width; }

private:
	float _x;   // . (point towards you)
	float _y;	// -
	float _z;   // |
	float _width;
	float _height;
	float _halfWidth;
	float _halfHeight;
};

class Camera : public Object {
public:
	Camera() {}

	// Vec3 d and u are unit vectors view direction and up
	Camera(vec3 eye, float w, float h, float dmin, float dmax, 
		vec3 d, vec3 u, int objID) :
		Object(objID, Kind::CAMERA, eye),
		_width(w), 
		_height(h),
		_halfWidth(w / 2),
		_halfHeight(h / 2),
		_dMin(dmin),
		_dMax(dmax)
	{
		// Create the right vector 
		vec3 r = d.cross(u);

		// d is a unit vector centered at the eye point. 
		// Multiply it by dMin and dMax to get the near/far plane centers
		vec3 _minSubPt = eye + (d * _dMin);
		vec3 _maxSubPt = eye + (d * _dMax);

		//// Center the rectangle (probably wrong if factoring of rotation)
		//float nx = pt[0] + dmin;
		//float ny = pt[1] - (h / 2);
		//float nz = pt[2] - (w / 2);
		//_nearPlane = Rectangle(nx, ny, nz, w, h);
		//_ptMinSub = vec3(nx, ny, nz);

		// Set up view frustrum points
		_viewFrustrum = ViewFrustrum(w, h, dmin, dmax, eye, d, u, r);
	}

	vec3 getEye() { 
		return _ptReg; 
	}

private:
	float _width;
	float _height;
	float _halfWidth;   
	float _halfHeight;

	float _dMin;
	float _dMax;

	vec3 _d;
	vec3 _u;
	vec3 _r;

	vec3 _ptMinSub; // point for min-plane
	vec3 _ptMaxSub; // point for max-plane

	ViewFrustrum _viewFrustrum;
};

#endif