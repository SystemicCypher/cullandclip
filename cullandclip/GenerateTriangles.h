#include <stdlib.h>
#include <time.h>
#include <vector>

#include "single-include.h"

// Haven't tested yet. Getting some errors in other files. Will check that out when I can.

// Check if the result is a triangle
// Avoid cases where a linear line is generated
bool isTriangle(const std::vector<Vecpt> &vertices) {
	float ax = vertices[0].get_value(0);
	float ay = vertices[0].get_value(1);
	float az = vertices[0].get_value(2);

	float bx = vertices[1].get_value(0);
	float by = vertices[1].get_value(1);
	float bz = vertices[1].get_value(2);

	float cx = vertices[3].get_value(0);
	float cy = vertices[3].get_value(1);
	float cz = vertices[3].get_value(2);

	int count = 0;

	if (ax == bx && ax == cx && bx == cx) {
		count++;
	}
	if (ay == by && ay == cy && by == cy) {
		count++;
	}
	if (az == bz && az == cz && bz == cz) {
		count++;
	}

	return (count >= 2) ? false : true;
}

// Check if points are stored in counter clock wise order.
// Works only checks the first three Vecpts in vector.
bool isCCW(Vecpt refPt, const std::vector<Vecpt> &vertices) {
	Vecpt a = vertices[0];
	Vecpt b = vertices[1];
	Vecpt c = vertices[2];

	Vecpt AB = b - a;
	Vecpt BC = c - b;

	Vecpt norm = AB.cross(BC);
	Vecpt d = refPt - a;

	float result = d.dot(norm);

	return (result >= 0) ? true : false;
}

// Reference point is generally the eye position. Used for determining if the triangle is CCW. 
// dMin is the minimum distance from the reference point. dMax is the max distance from the reference point.
// range is the range in which the triangles will be generated in.
// numTriangles is the number of output triangles to generate.
// randSeed determines if a random seed is used. A static seed would be better for testing purposes.
std::vector<Triangle> generateTriangles(Vecpt refPt, float dMin, float dMax, float range, int numTriangles, bool randSeed) {
	// Use a seed
	(randSeed ? srand(unsigned int(time(NULL))) : srand(0));

	// Point centered in view frustrum
	float x = refPt.get_value(0);
	float y = refPt.get_value(1) + dMin + dMax / 2;
	float z = refPt.get_value(2);

	float lo = -range * 2;
	float hi = range * 2;

	std::vector<Triangle> triangles;

	for (int i = 0; i < numTriangles; i++) {

		std::vector<Vecpt> vertices;

		do {
			vertices.clear();

			for (int j = 0; j < 3; j++) {
				float rx = x + lo + (float)rand() / (float(RAND_MAX / (x + hi - x + lo)));
				float ry = y + lo + (float)rand() / (float(RAND_MAX / (y + hi - y + lo)));
				float rz = z + lo + (float)rand() / (float(RAND_MAX / (z + hi - z + lo)));

				vertices.emplace_back(rx, ry, rz, REAL_3D, POINT);
			}
		} while (!isTriangle(vertices) || !isCCW(refPt, vertices));

		triangles.emplace_back(i, refPt, vertices[0], vertices[1], vertices[2]);
	}

	return triangles;
}