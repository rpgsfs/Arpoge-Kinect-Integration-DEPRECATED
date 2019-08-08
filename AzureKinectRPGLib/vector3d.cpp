#include "pch.h"
#include "vector3d.h"
#include<iostream>
#include<math.h>
#include <k4a/k4a.h>
#include <k4abt.h>
#include<assert.h>
#include <cmath>

using namespace std;
typedef float f;

vector3d::vector3d()  //constructor
{
	x = 0;
	y = 0;
	z = 0;
}
vector3d::vector3d(const vector3d& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

vector3d::vector3d(f x1, f y1, f z1)     //initializing object with values.
{
	x = x1;
	y = y1;
	z = z1;
}
vector3d::vector3d(k4abt_joint_t joint)
{
	x = joint.position.v[0];
	y = joint.position.v[1];
	z = joint.position.v[2];
}

//addition

vector3d vector3d ::operator+(const vector3d& vec)
{
	return vector3d(x + vec.x, y + vec.y, z + vec.z);
}

vector3d& vector3d ::operator+=(const vector3d& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}
//substraction//
vector3d vector3d ::operator-(const vector3d& vec)
{
	return vector3d(x - vec.x, y - vec.y, z - vec.z);
}

vector3d& vector3d::operator-=(const vector3d& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

//scalar multiplication

vector3d vector3d ::operator*(f value)
{
	return vector3d(x * value, y * value, z * value);
}



vector3d& vector3d::operator*=(f value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

//scalar division
vector3d vector3d ::operator/(f value)
{
	assert(value != 0);
	return vector3d(x / value, y / value, z / value);
}

vector3d& vector3d ::operator/=(f value)
{
	assert(value != 0);
	x /= value;
	y /= value;
	z /= value;
	return *this;
}


vector3d& vector3d::operator=(const vector3d& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}

//Dot product
f vector3d::dot_product(const vector3d& vec) const
{
	return x * vec.x + vec.y * y + vec.z * z;
}

//cross product
vector3d vector3d::cross_product(const vector3d& vec)
{
	f ni = y * vec.z - z * vec.y;
	f nj = z * vec.x - x * vec.z;
	f nk = x * vec.y - y * vec.x;
	return vector3d(ni, nj, nk);
}

f vector3d::magnitude() const
{
	return sqrt(square());
}

f vector3d::square() const
{
	return x * x + y * y + z * z;
}

vector3d vector3d::normalization()
{
	assert(magnitude() != 0);
	*this /= magnitude();
	return *this;
}

f vector3d::distance(const vector3d& vec)
{
	vector3d dist = *this - vec;
	return dist.magnitude();
}
f vector3d::cosine(const vector3d& vec) const {
	f magnitude = this->magnitude();
	f vecMagnitude = vec.magnitude();
	f dot_product = this->dot_product(vec);
	f cos = dot_product / (magnitude * vecMagnitude);
	return cos;
}

f vector3d::show_X()
{
	return x;
}

f vector3d::show_Y()
{
	return y;
}

f vector3d::show_Z()
{
	return z;
}

void vector3d::disp()
{
	cout << x << " " << y << " " << z;
//cout << x << y << z << endl;
  /*  cout << x << endl;
	cout << y << endl;
	cout << z << endl;*/


}
