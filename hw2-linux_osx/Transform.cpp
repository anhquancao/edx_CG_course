// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.
mat3 Transform::rotate(const float degrees, const vec3 &axis)
{
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

void Transform::left(float degrees, vec3 &eye, vec3 &up)
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
  mat3 R = Transform::rotate(degrees, up);
  eye = R * eye;
}

void Transform::up(float degrees, vec3 &eye, vec3 &up)
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
  vec3 axis = glm::normalize(glm::cross(eye, up));
  mat3 R = Transform::rotate(degrees, axis);
  eye = R * eye;
  up = glm::normalize(R * up);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
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

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  float radians = glm::radians(fovy/2);
  float d = 1 / glm::tan(radians);

  float A = -(zFar + zNear) / (zFar - zNear);
  float B = -(2 * zFar * zNear) / (zFar - zNear);
  mat4 ret = mat4(
      d / aspect, 0, 0, 0,
      0, d, 0, 0,
      0, 0, A, B,
      0, 0, -1.0, 0);
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.
  return glm::transpose(ret);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  mat4 ret = mat4(
      sx, 0, 0, 0,
      0, sy, 0, 0,
      0, 0, sz, 0,
      0, 0, 0, 1);
  ;
  // YOUR CODE FOR HW2 HERE
  // Implement scaling
  return glm::transpose(ret);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
  mat4 ret = mat4(
      1, 0, 0, tx,
      0, 1, 0, ty,
      0, 0, 1, tz,
      0, 0, 0, 1);
  ;
  // YOUR CODE FOR HW2 HERE
  // Implement translation
  return glm::transpose(ret);
}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

vec3 Transform::upvector(const vec3 &up, const vec3 &zvec)
{
  vec3 x = glm::cross(up, zvec);
  vec3 y = glm::cross(zvec, x);
  vec3 ret = glm::normalize(y);
  return ret;
}

Transform::Transform()
{
}

Transform::~Transform()
{
}
