#include "ViewFrustrum.h"
#include "single-include.h"

//===============================================================================
// View Frustrum::Plane Functions
//===============================================================================

ViewFrustrum::Plane::Plane() {}

ViewFrustrum::Plane::Plane(vec3 tl, vec3 tr, vec3 bl, vec3 br) :
	_tl(tl),
	_tr(tr),
	_bl(bl),
	_br(br)
{}

//===============================================================================
// View Frustrum Functions
//===============================================================================
ViewFrustrum::ViewFrustrum()
{}

ViewFrustrum::ViewFrustrum(float width, float height, float dMin, float dMax, vec3 eyePt, vec3 d, vec3 u, vec3 r)
{
	setUpPlanes(width, height, dMin, dMax, eyePt, d, u, r);
}

ViewFrustrum::~ViewFrustrum()
{}

void ViewFrustrum::setUpPlanes(float width, float height, float dMin, float dMax, vec3 eyePt, vec3 d, vec3 u, vec3 r) {
	float halfWidth  = width / 2;
	float halfHeight = height / 2;

	// Near plane points
	vec3 ntl = eyePt + (d * dMin) + (u * halfHeight)  + (r * -halfWidth);
	vec3 ntr = eyePt + (d * dMin) + (u * halfHeight)  + (r * halfWidth);
	vec3 nbl = eyePt + (d * dMin) + (u * -halfHeight) + (r * -halfWidth);
	vec3 nbr = eyePt + (d * dMin) + (u * -halfHeight) + (r * halfWidth);

	// Far plane points
	vec3 ftl = (d * dMin) + (u * halfHeight) + (r * -halfWidth);
	ftl = eyePt + (ftl * (dMax / dMin));

	vec3 ftr = (d * dMin) + (u * halfHeight) + (r * halfWidth);
	ftr = eyePt + (ftr * (dMax / dMin));
	
	vec3 fbl = (d * dMin) + (u * -halfHeight) + (r * -halfWidth);
	fbl = eyePt + (fbl * (dMax / dMin));

	vec3 fbr = (d * dMin) + (u * -halfHeight) + (r * halfWidth);
	fbr = eyePt + (fbr * (dMax / dMin));


	_nearPlane  = ViewFrustrum::Plane(ntl, ntr, nbl, nbr);

	_farPlane   = ViewFrustrum::Plane(ntl, ntr, nbl, nbr);

	//// Not necessary? Can construct planes from near and far planes. 
	//_topPlane   = ViewFrustrum::Plane(ftl, ftr, ntl, nbr);

	//_botPlane   = ViewFrustrum::Plane(fbl, fbr, nbl, nbr);

	//_leftPlane  = ViewFrustrum::Plane(ftl, ntl, fbl, nbl);
 //
	//_rightPlane = ViewFrustrum::Plane(ftr, ntr, fbr, nbr);
}

vec3 ViewFrustrum::getPoint(Locations dist, Locations v) {
	// Return near points
	if (dist == Locations::NEAR) {
		switch (v) {
		case BOT_LEFT:  return _nearPlane._bl;
			break;
		case BOT_RIGHT: return _nearPlane._br;
			break;
		case TOP_LEFT:  return _nearPlane._tl;
			break;
		case TOP_RIGHT: return _nearPlane._tr;
			break;
		}
	}

	// Return far points
	if (dist == Locations::FAR) {
		switch (v) {
		case BOT_LEFT:  return _farPlane._bl;
			break;
		case BOT_RIGHT: return _farPlane._br;
			break;
		case TOP_LEFT:  return _farPlane._tl;
			break;
		case TOP_RIGHT: return _farPlane._tr;
			break;
		}
	}

	printf("Error. No results found. Possibly wrong input.");
	return vec3();

}

bool ViewFrustrum::isInsideViewFrustrum(vec3 pt) {
	// Will return early once one of these are false
	if (isOnSameSide(_nearPlane._bl - _nearPlane._br, _nearPlane._tl - _nearPlane._bl, pt) &&
		isOnSameSide(_farPlane._tl  - _farPlane._tr,  _farPlane._bl  - _farPlane._tl, pt)  &&
		isOnSameSide(_farPlane._tr  - _farPlane._tl,  _farPlane._tl  - _nearPlane._tl, pt) &&
		isOnSameSide(_farPlane._bl  - _farPlane._br,  _nearPlane._bl - _farPlane._bl, pt)  &&
		isOnSameSide(_farPlane._bl  - _nearPlane._bl, _farPlane._tl  - _farPlane._bl, pt)  &&
		isOnSameSide(_nearPlane._tr - _nearPlane._br, _farPlane._tr  - _nearPlane._tr, pt))
		return true;

	return false; 
}

bool ViewFrustrum::isOnSameSide(vec3 norm, vec3 pt) {
	return (norm * pt < 0) ? false : true;
}

bool ViewFrustrum::isOnSameSide(vec3 v1, vec3 v2, vec3 pt) {
	vec3 norm = v2.cross(v1);
	return (norm * pt < 0) ? false : true;
}

vec3 ViewFrustrum::getNormal(Locations plane) {
	switch (plane) {
	case NEAR: 
		vec3 v1 = _nearPlane._bl - _nearPlane._br;
		vec3 v2 = _nearPlane._tl - _nearPlane._bl;
		return v2.cross(v1);
		break;

	case FAR:
		vec3 v1 = _farPlane._tl - _farPlane._tr;
		vec3 v2 = _farPlane._bl - _farPlane._tl;
		return v2.cross(v1);
		break;

	case TOP:
		vec3 v1 = _farPlane._tr - _farPlane._tl;
		vec3 v2 = _farPlane._tl - _nearPlane._tl;
		return v2.cross(v1);
		break;

	case BOT:
		vec3 v1 = _farPlane._bl - _farPlane._br;
		vec3 v2 = _nearPlane._bl - _farPlane._bl;
		return v2.cross(v1);
		break;

	case LEFT:
		vec3 v1 = _farPlane._bl - _nearPlane._bl;
		vec3 v2 = _farPlane._tl - _farPlane._bl;
		return v2.cross(v1);
		break;

	case RIGHT:
		vec3 v1 = _nearPlane._tr - _nearPlane._br;
		vec3 v2 = _farPlane._tr - _nearPlane._tr;
		return v2.cross(v1);
		break;

	default:
		printf("Error. Wrong plane selected.\n");
		return vec3();
	}
}

// Reuse this to return normals later in a function 
/*
// At any point of failure return false

// Check near plane
vec3 v1 = _nearPlane._bl - _nearPlane._br;
vec3 v2 = _nearPlane._tl - _nearPlane._bl;
vec3 norm = v2.cross(v1);

if (norm * pt < 0) // repetitive
	return false;

// Check far plane
vec3 v1 = _farPlane._tl - _farPlane._tr;
vec3 v2 = _farPlane._bl - _farPlane._tl;
vec3 norm = v2.cross(v1);

if (norm * pt < 0)
	return false;

// Check top plane
vec3 v1 = _farPlane._tr - _farPlane._tl;
vec3 v2 = _farPlane._tl - _nearPlane._tl;
vec3 norm = v2.cross(v1);

if (norm * pt < 0)
	return false;

// Check bot plane
vec3 v1 = _farPlane._bl - _farPlane._br;
vec3 v2 = _nearPlane._bl - _farPlane._bl;
vec3 norm = v2.cross(v1);

if (norm * pt < 0)
	return false;

// Check left plane
vec3 v1 = _farPlane._bl - _nearPlane._bl;
vec3 v2 = _farPlane._tl - _farPlane._bl;
vec3 norm = v2.cross(v1);

if (norm * pt < 0)
	return false;

// Check right plane
vec3 v1 = _nearPlane._tr - _nearPlane._br;
vec3 v2 = _farPlane._tr - _nearPlane._tr;
vec3 norm = v2.cross(v1);

if (norm * pt < 0)
	return false;

// Point on the same side of all planes
return true;
*/