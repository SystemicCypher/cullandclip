#include "vecpt.h"
#include "triangle.h"
#include "Camera.h"
#include <cmath>

/*
* --------------------------------------------------
* Frustrum Namespace
* --------------------------------------------------
* This namespace contains several functions that can
* define the view frustrum without needing a class.
* Basically, the idea of this class is to merely take
* in the data of the classes we have defined prior
* (those being object, triangle, camera...) and
* produce the output needed for project #1.
*/

namespace frustrum {
#define PI 3.14159265
	/*
	* --------------------------------------------------
	* Definitions of Abstractions
	* --------------------------------------------------
	* ABOVE and BELOW are used to more easily understand
	* the true/false results of a couple check functions
	*/
#define ABOVE true
#define BELOW false

	/*
	* --------------------------------------------------
	* float plane_intersect
	* --------------------------------------------------
	* Description:
	* This function takes a normal vector to a plane and
	* a point/vector to do the dot product against it
	* An abstraction function.
	* --------------------------------------------------
	* Inputs
	* --------------------------------------------------
	* Vecpt normal : A normal vector to some plane
	*
	* Vecpt check : A point to dot against the normal
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* A floating point value that is the result of the dot
	* product.
	*/
	float plane_intersect(Vecpt normal, Vecpt check) {
		return normal.dot(check);
	}

	/*
	* --------------------------------------------------
	* bool above_or_below
	* --------------------------------------------------
	* Description:
	* This takes a floating point number dot product result and determines if it is
	* above or below a plane. A simple abstraction function.
	* It basically just checks if the value is greater than 0.0 (Above) or less (Below).
	* --------------------------------------------------
	* Input
	* --------------------------------------------------
	* float x : A floating point value that should be a result of
	* a dot product
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* A boolean value true (Above) or false (Below)
	*/
	bool above_or_below(float x) {
		return (x >= 0.0) ? ABOVE : BELOW;
	}

	/*
	* --------------------------------------------------
	* Vecpt point_on_line
	* --------------------------------------------------
	* Description:
	* It takes a point and vector defining a line, and a scalar value "time" t
	* in order to return a point that is on the line at that "time" t.
	* It is an n-dimensional implementation of this:
	* (a, b, c) + t*<i, j, k> = (x, y, z)
	* initial_point + t * vector = point
	* --------------------------------------------------
	* Inputs
	* --------------------------------------------------
	* Vecpt point : A point that is on the line
	*
	* Vecpt vector : A vector that determines the path/direction of the line
	*
	* float t : The value that determines where on the line this point is
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* A point that is on the previously defined line.
	*/
	Vecpt point_on_line(Vecpt point, Vecpt vector, float t) {
		if (point.is_point() && vector.is_vector()) return ((vector * t) + point);
		return Vecpt(0, POINT);
	}

	/*
	* --------------------------------------------------
	* Vecpt* line_maker
	* --------------------------------------------------
	* Description:
	* Smartass answer - it makes lines....
	* Legitimate answer - It takes in a point, a vector (which defines the line),
	* an interval that determines (approximately) how to divide up the range
	* defined by start and end.
	* --------------------------------------------------
	* Inputs
	* --------------------------------------------------
	* Vecpt point : A 3D point that is on the line
	*
	* Vecpt vector : A 3D vector that determines the path/direction of the line
	*
	* float interval : A value that determines the size of the steps to traverse the range
	*
	* float start : A value determining the start of the range to explicitly define a line
	*
	* float end : A value determining the end of the range to explicitly define a line
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* This function returns a pointer to an array of Vecpt points that are on the line defined
	* by the point and vector given.
	*/
	Vecpt* line_maker(Vecpt point, Vecpt vector, float interval, float start, float end) {
		int range = end - start;
		Vecpt* funct = new Vecpt[range];
		for (int i = 0; i < range; i++) {
			funct[i] = point_on_line(point, vector, start + interval * i);
		}
		return funct;
	}

	/*
	* --------------------------------------------------
	* Vecpt generate_point
	* --------------------------------------------------
	* Description:
	* This function generalizes the equation found in page 44 of
	* the game engine programming textbook. Given a basis set of vectors
	* to define a space and axes for it (D, U, R), the limits of the view (near)
	* plane (d, u, r), and an eye (E), this function returns the points of each of the
	* vertices of the view frustrum.
	* --------------------------------------------------
	* Inputs
	* --------------------------------------------------
	* Vecpt E : A 3D point that defines the eye/camera's location.
	*
	* float d : The maximum or minimum depth value. This determines how far
	* the frustrum extends into the "screen" (d_max) and how close the near plane
	* is to the eye (d_min).
	*
	* float u : The maximum or minimum up value. This determines the locations of the
	* top (u_max) and bottom (u_min) cutoffs of the view frustrum.
	*
	* float r : The maximum or minimum right value. This determines the left (r_min) and
	* right (r_max) borders of the view frustrum.
	*
	* Vecpt D : A basis vector in 3D that defines the depth axis.
	*
	* Vecpt U : A basis vector in 3D that defines the up axis.
	*
	* Vecpt R : A basis vector in 3D that defines the right axis.
	*
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* A 3D point that is either one of the four in the near plane or one of the four
	* in the far plane.
	*
	*/
	Vecpt generate_point(Vecpt E, float d, float u, float r, Vecpt D, Vecpt U, Vecpt R) {
		Vecpt output;
		output = E + D * d + U * u + R * r;
		return output;
	}

	/*
	* --------------------------------------------------
	* Vecpt normal_find
	* --------------------------------------------------
	* Description:
	* Given 3 3D points, this function will calculate a normal to the
	* plane that those points create. The syntax is biased toward a
	* view frustrum. Further details in the inputs section below.
	* --------------------------------------------------
	* Inputs
	* --------------------------------------------------
	* Vecpt v1 : A 3D point. Represents the point that is in
	* between the near plane point and the far plane point.
	*
	* Vecpt v2 : A 3D point. Represents the endpoint in the near
	* plane.
	*
	* Vecpt w  : A 3D point. Represents the far plane point.
	* --------------------------------------------------
	* Visual example
	* --------------------------------------------------
	*			far plane
	*       w____________
	*      /           / |
	*     /___________/  |
	*     v1         |   /
	*     |          |  /
	*     | near pln | /
	*     |__________|/
	*     v2
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* A 3D vector (Vecpt with dimension 3 and vector == VECTOR)
	* that is normal to the plane that the three input points
	* are in.
	*/
	Vecpt normal_find(Vecpt v1, Vecpt v2, Vecpt w) {
		Vecpt near, far;  // Wherever you are~
		near = v2 - v1;
		far = w - v1;

		Vecpt normal;
		normal = near.cross(far);

		return normal;
	}

	/*
	* --------------------------------------------------
	* bool ranger
	* --------------------------------------------------
	* Description:
	* An abstraction function. Allows for simple checking of a symmetric range.
	* (e.g. 0.5 to -0.5)
	* --------------------------------------------------
	* Inputs
	* --------------------------------------------------
	* float range_ends : The endpoints of the range. Basically the value that is
	* the right end of the range (positive side). The left end is -1 * range_ends.
	* This should be a positive float.
	*
	* float check : The floating point value to check. It's compared to both ends to
	* see if it fits within the range.
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* A boolean value, true if the float to check is within the range, false otherwise
	*/
	bool ranger(float range_ends, float check) {
		if (check >= -range_ends && check <= range_ends) return true;
		return false;
	}

	/*
	* --------------------------------------------------
	* Vecpt find_intersection
	* --------------------------------------------------
	* Description:
	* Determines if an intersection between a line and a point exists,
	* if so, it returns that intersection point.
	* --------------------------------------------------
	* Inputs
	* --------------------------------------------------
	* Vecpt A : A 3D point that is one point of a line - should always be the origin
	* of the line/"ray"
	*
	* Vecpt B : A 3D point that is the other end of the line
	*
	* Vecpt plane_normal: A 3D vector that is normal to some plane
	*
	* Vecpt point_on_plane : A point on the plane
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* A 3D point (Vecpt with dimension 3 and vector == POINT) that is NaN if there
	* were no intersections found or the intersection if there was one found.
	*/
	Vecpt find_intersection(Vecpt A, Vecpt B, Vecpt plane_normal, Vecpt point_on_plane) {
		float d = plane_normal.dot(point_on_plane);
		Vecpt line = B - A;
		float  parallel = plane_normal.dot(line);
		if (parallel == 0.0f) {
			return Vecpt();
		}
		float x = (d - plane_normal.dot(A)) / plane_normal.dot(line);
		Vecpt normalized_line = line / line.magnitude();
		return A + normalized_line * x;

	}

	/*
	* --------------------------------------------------
	* Triangle* triangulate
	* --------------------------------------------------
	* Description:
	* Converts a polygon into an array of triangles as a triangular fan.
	* Uses the first vertex of the polygon as a shared point for all
	* subsequently generated triangles.
	* For every other point in the array, take the vertex and its neighbor,
	* and construct an "edge" between the shared point and the neighbor to
	* form a triangle.
	* Ignores any polygon with less than 4 points and returns a nullptr.
	* (already a triangle, a line segment, or a point).
	* Checks if the triangle is already in view
	* Function assumes the polygon is planar and convex.
	* --------------------------------------------------
	* Inputs
	* --------------------------------------------------
	* ref_pt : A 3D point that is used as a reference point
	*          to determine if the polygon's points are stored CCW
	*
	* Vecpt D, U R : Basis vectors
	*
	* Vecpt* polygon: Pointer to an array of points that make up the polygon
	*
	* int num_pts : The number of points for the polygon
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* An array of newly generated triangles from the polygon.
	*/
	Triangle* triangulate(Vecpt ref_pt, Vecpt D, Vecpt U, Vecpt R, Vecpt* polygon, int num_pts) {
		if (num_pts < 4) return nullptr;

		Vecpt shared_pt = polygon[0];
		int num_triangles = num_pts - 2;
		Triangle* output = new Triangle[num_triangles];

		Vecpt norm = normal_find(polygon[1], polygon[0], polygon[2]);
		bool ccw = D.dot(norm) > 0 ? true : false;

		// TODO: Problem generating unique IDs for the triangle...
		if (ccw) {
			for (int i = 0; i < num_triangles; i++) { // CCW, iterate normally
				output[i] = Triangle(i, ref_pt, shared_pt, polygon[i + 1], polygon[i + 2]);
			}
		}
		else {
			for (int i = num_pts; i > 1; i--) { // not CCW, iterate from the back of the array
				output[i] = Triangle(i, ref_pt, shared_pt, polygon[i - 1], polygon[i - 2]);
			}
		}

		return output;
	}

	/*
	* --------------------------------------------------
	* std::vector<Triangle> clip_to_plane
	* --------------------------------------------------
	* Description:
	* Assuming no large triangles with points outside frustrum and all triangles
	* outside frustrum have been culled.
	* Clips a triangle to a view frustrum plane.
	* An array of triangles (sub-triangles) will be tested against each plane of the
	* view frustrum. Each triangle will be "sliced" up by the view frustrum at the points
	* of intersection between the plane and the triangle.
	* The polygon generated from the triangle's vertices and intersections
	* will be triangularized and new triangles will be added to the vector of
	* triangles to be further processed by the remaining planes.
	* --------------------------------------------------
	* Inputs
	* --------------------------------------------------
	* ref_pt : A 3D point that is used as a reference point
	*          to determine if the polygon's points are stored CCW
	*
	* Vecpt D, U R : Basis vectors
	*
	* Vecpt plane_normal: Normal to the frustrum plane we are clipping with
	*
	* Vecpt pt_on_plane: A point on the plane (probably a vertex of the plane)
	*
	* Triangle triangle: The triangle to clip
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* A vector of newly generated triangles after clipping.
	*/
	std::vector<Triangle> clip_to_plane(Vecpt ref_pt, Vecpt D, Vecpt U, Vecpt R,
		Vecpt plane_normal, Vecpt pt_on_plane, Triangle triangle) {
		const int NUM_TRI_EDGES = 3;
		const int MAX_POINTS = 4;

		std::vector<Triangle> input_triangles;
		input_triangles.push_back(triangle);

		int init_num_triangles = input_triangles.size();

		for (int j = 0; j < init_num_triangles; j++) { // for triangle 
			Vecpt* polygon = new Vecpt[MAX_POINTS];
			int num_points = 0;

			for (int k = 0; k < NUM_TRI_EDGES; k++) { // for every edge
				int A = k % NUM_TRI_EDGES;
				int B = (k + 1) % NUM_TRI_EDGES;

				Vecpt pt = find_intersection(input_triangles[j][A], input_triangles[j][B], plane_normal, pt_on_plane);
				float result = plane_intersect(plane_normal, input_triangles[j][A] - pt_on_plane);

				bool inside = above_or_below(result);
				if (inside) {
					polygon[num_points] = input_triangles[j][A];
					num_points++;
				}
				if (pt.get_value(0) != NAN) {
					polygon[num_points] = pt;
					num_points++;
				}
			}

			// Remove the initial triangle that was processed
			input_triangles.erase(input_triangles.begin());

			Triangle* output = triangulate(ref_pt, D, U, R, polygon, num_points);
			for (int i = 0; i < num_points - 2; i++) {
				input_triangles.push_back(output[i]);
			}
			delete[] polygon;
		}
		return input_triangles;
	}

	/*
	* --------------------------------------------------
	* Vecpt object_to_world
	* --------------------------------------------------
	* Description:
	* 
	* --------------------------------------------------
	* Inputs
	* --------------------------------------------------
	* ref_pt : A 3D point that is used as a reference point
	*          to determine if the polygon's points are stored CCW
	*
	* Vecpt D, U R : Basis vectors
	*
	* Vecpt plane_normal: Normal to the frustrum plane we are clipping with
	*
	* Vecpt pt_on_plane: A point on the plane (probably a vertex of the plane)
	*
	* Triangle triangle: The triangle to clip
	* --------------------------------------------------
	* Output
	* --------------------------------------------------
	* A vector of newly generated triangles after clipping.
	*/

	Vecpt object_to_world(Vecpt point, Vecpt new_origin, float az, float el) {
		az = az * (PI / 180.0);
		el = el * (PI / 180.0);
		float x_a, x_e, y_a, y_e, z_a, z_e, x, y, z;
		//az rotation
		x_a = cos(az)*point.get_value(0) - sin(az)*point.get_value(1);
		y_a = sin(az)*point.get_value(0) + cos(az)*point.get_value(1);
		z_a = point.get_value(2);
		//elev rotation
		x_e = cos(el)*x_a + sin(el)*z_a;
		y_e = y_a;
		z_e = -sin(el)*x_a + cos(el)*z_a;
		//translation
		x = x_e + new_origin.get_value(0);
		y = y_e + new_origin.get_value(1);
		z = z_e + new_origin.get_value(2);
		Vecpt output(3, POINT);
		output.set_dim_val(0, x);
		output.set_dim_val(1, y);
		output.set_dim_val(2, z);
		return output;
	}

	Vecpt world_to_camera(Vecpt eye, float az, float el) {
		az = az * (PI / 180.0);
		el = el * (PI / 180.0);
		Vecpt D(3, VECTOR);
		Vecpt U(3, VECTOR);
		Vecpt R(3, VECTOR);
		D.set_dim_val(0, eye.get_value(0) + cos(az));
		D.set_dim_val(1, eye.get_value(1);
		D.set_dim_val(2, eye.get_value(3) + sin(az));

	}

}

