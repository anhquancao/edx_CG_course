// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3 &axis)
{
	// YOUR CODE FOR HW1 HERE
	mat3 K = mat3(0, axis[2], -axis[1], -axis[2], 0, axis[0], axis[1], -axis[0], 0);

	//here we write the matrices in row major form
	//because the main program automatically transpose
	//the matrix
	// mat3 K = mat3(0, -axis[2], axis[1], axis[2], 0,  -axis[0], -axis[1], axis[0], 0);
	// K = glm::transpose(K);
	
	mat3 I(1.0), R;
	// You will change this return call

	// rodrigues rotation formula
	R = I + ((float)sin(degrees / 180 * pi)) * K + ((float)(1 - cos(degrees / 180 * pi))) * K * K;
	return R;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3 &eye, vec3 &up)
{
	// YOUR CODE FOR HW1 HERE
	mat3 R = Transform::rotate(degrees, up);
	eye = R * eye;
	// up = glm::normalize(R * up);
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3 &eye, vec3 &up)
{
	// YOUR CODE FOR HW1 HERE
	vec3 axis = glm::normalize(glm::cross(eye, up));
	mat3 R = Transform::rotate(degrees, axis);
	eye = R * eye;
	up = glm::normalize(R * up);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up)
{
	// YOUR CODE FOR HW1 HERE
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 T(
		1, 0, 0, -eye.x,
		0, 1, 0, -eye.y,
		0, 0, 1, -eye.z,
		0, 0, 0, 1);
	

	mat4 R = mat4(
		u.x, u.y, u.z, 0,
		v.x, v.y, v.z, 0,
		w.x, w.y, w.z, 0,
		0, 0, 0, 1);
	

	// You will change this return call
	return glm::transpose(T * R);
}

Transform::Transform()
{
}

Transform::~Transform()
{
}
