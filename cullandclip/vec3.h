#ifndef VEC3_H
#define VEC3_H

#include <stdexcept>

class vec3 {
public:
	vec3() : x(0.0f), y(0.0f), z(0.0f) {}

	vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	vec3 operator+(const vec3& v) {
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	vec3 operator-(const vec3& v) {
		return vec3(x - v.x, y - v.y, z - v.z);
	}

	void operator=(const vec3 &v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	float operator*(const vec3 &v) {
		return x * v.x + y * v.y + z * v.z;
	}

	vec3 cross(const vec3 &v) {
		float i = y * v.z - z * v.y;
		float j = z * v.x - x * v.z;
		float k = x * v.y - y * v.x;

		return vec3(i, j, k);
	}

	
	float& operator[](int i) {
		switch (i) {
		case 0: return x;
			break;
		case 1: return y;
			break;
		case 2: return z;
			break;
		default:
			throw std::out_of_range("Out of bounds accessing element of vec3.\n");
		}
	}

private:
	float x;
	float y;
	float z;
};

#endif