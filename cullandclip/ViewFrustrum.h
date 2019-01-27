#ifndef VIEW_FRUSTRUM_H
#define VIEW_FRUSTRUM_H

#include "vec3.h"
#include "vecpt.h"

/// Still using vec3. Can change it to VecPt later

// Can be used to specify the points we want  Ex: getPoint(TOP_LEFT, NEAR)
// Can also be used to get a plane            Ex: getPlane(TOP); or getPlane(Near);
enum Locations { TOP_LEFT, TOP_RIGHT, BOT_LEFT, BOT_RIGHT, TOP, BOT, LEFT, RIGHT, NEAR, FAR };

class ViewFrustrum {
private:
	// Defines a plane for the view frustrum
	// Assuming plane will only really be used by view frustrum so just make it a private class
	struct Plane {
	public:
		Plane(); 
		Plane(vec3 tl, vec3 tr, vec3 bl, vec3 br);

		vec3 _tl;
		vec3 _tr;
		vec3 _bl;
		vec3 _br;
	};

public:
	ViewFrustrum();

	ViewFrustrum(float width, float height, float dMin, float dMax, vec3 eyePt, vec3 d, vec3 u, vec3 r);

	~ViewFrustrum();

	// Returns a point 
	// Dist is near or far
	// V is the vertex location
	vec3 getPoint(Locations dist, Locations v); 

	// Checks if a point is inside the view frustrum
	bool isInsideViewFrustrum(vec3 pt);

	// Returns the normal of the specified plane
	// Normal will point inward towards view frustrum
	vec3 getNormal(Locations plane);


private:
	// Helper function to set up near and far plane
	void setUpPlanes(float width, float height, float dMin, float dMax, vec3 eyePt, vec3 d, vec3 u, vec3 r);

	// Checks if a point is on the same side of a plane
	bool isOnSameSide(vec3 norm, vec3 pt);

	bool isOnSameSide(vec3 v1, vec3 v2, vec3 pt);

	Plane _nearPlane;
	Plane _farPlane;

	// Not necessary? Can just calculate based off near and far points
	//Plane _topPlane;
	//Plane _botPlane;
	//Plane _leftPlane;
	//Plane _rightPlane;
};

#endif