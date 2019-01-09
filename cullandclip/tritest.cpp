#include <stdlib.h>
#include <time.h>
#include <vector>

#include "triangle.h"
#include "vecpt.h"

// Check if the result is a triangle
// Avoid cases where a linear line is generated
bool isTriangle(const std::vector<Vecpt> &vertices) {
	float ax = vertices[0].get_value(0);
	float ay = vertices[0].get_value(1);
	float az = vertices[0].get_value(2);

	float bx = vertices[1].get_value(0);
	float by = vertices[1].get_value(1);
	float bz = vertices[1].get_value(2);

	float cx = vertices[2].get_value(0);
	float cy = vertices[2].get_value(1);
	float cz = vertices[2].get_value(2);

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

bool isCCW(Vecpt refPt, const std::vector<Vecpt> &vertices) {
	Vecpt a = vertices[0];
	Vecpt b = vertices[1];
	Vecpt c = vertices[2];

	Vecpt AB = b - a;
	Vecpt BC = c - b;

	Vecpt norm = AB.cross(BC);
	Vecpt d = refPt - a;

	float result = d.dot(norm);

	printf("ax: %f, ay: %f, az: %f\n", a.get_value(0), a.get_value(1), a.get_value(2));
	printf("bx: %f, by: %f, bz: %f\n", b.get_value(0), b.get_value(1), b.get_value(2));
	printf("cx: %f, cy: %f, cz: %f\n\n", c.get_value(0), c.get_value(1), c.get_value(2));

	return (result >= 0) ? true : false;
}

std::vector<Triangle> generateTriangles(Vecpt refPt, float dMin, float dMax, float range, int numTriangles, bool randSeed) {
	// Use a seed
	(randSeed ? srand(time(NULL)) : srand(0));

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
				float rx = ((float)(rand()) / float(RAND_MAX)) * abs(lo - hi) + lo + x;
				float ry = ((float)(rand()) / float(RAND_MAX)) * abs(lo - hi) + lo + y;
				float rz = ((float)(rand()) / float(RAND_MAX)) * abs(lo - hi) + lo + z;

				Vecpt pt(REAL_3D, POINT);
				pt.set_dim_val(0, rx);
				pt.set_dim_val(1, ry);
				pt.set_dim_val(2, rz);

				vertices.push_back(pt);
			}
		} while (!isTriangle(vertices) || !isCCW(refPt, vertices));

		triangles.emplace_back(i, refPt, vertices[0], vertices[1], vertices[2]);
	}

	return triangles;
}

int main() {
	// Test counter clockwise 
	Vecpt a = Vecpt(REAL_3D, false);
	a.set_dim_val(0, 5);
	a.set_dim_val(1, 9);
	a.set_dim_val(2, 2);

	Vecpt b = Vecpt(REAL_3D, false);
	b.set_dim_val(0, 3);
	b.set_dim_val(1, 8);
	b.set_dim_val(2, -1);

	Vecpt c = Vecpt(REAL_3D, false);
	c.set_dim_val(0, -12);
	c.set_dim_val(1, 7);
	c.set_dim_val(2, -5);

	Vecpt ref = Vecpt(REAL_3D, false);
	ref.set_dim_val(0, 0);
	ref.set_dim_val(1, 0);
	ref.set_dim_val(2, 0);

	std::vector<Vecpt> cw{ a, b, c };
	std::vector<Vecpt> ccw{ a, c, b };

	bool bCW = isCCW(ref, cw);
	bool bCCW = isCCW(ref, ccw);

	std::vector<Triangle> temp = generateTriangles(ref, 10.0f, 20.0f, 50.0f, 50, false);

	return 0;
}