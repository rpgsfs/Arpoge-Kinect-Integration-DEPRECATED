#pragma once
#define vector3d_H
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<math.h>
#include<assert.h>
#include <k4a/k4a.h>
#include <k4abt.h>
#include "vector3d.h"
using namespace std;
typedef float f;
class vector3d {
public:
	f x, y, z;
	vector3d();
	vector3d(f x1, f y1, f z1 = 0);
	vector3d(const vector3d& vec);    //copy constructor
	vector3d(k4abt_joint_t joint);
	vector3d operator+(const vector3d& vec);    //addition
	vector3d& operator+=(const vector3d& vec);  ////assigning new result to the vector
	vector3d operator-(const vector3d& vec);    //substraction
	vector3d& operator-=(const vector3d& vec);  //assigning new result to the vector
	vector3d operator*(f value);    //multiplication
	vector3d& operator*=(f value);  //assigning new result to the vector.
	vector3d operator/(f value);    //division
	vector3d& operator/=(f value);  //assigning new result to the vector
	vector3d& operator=(const vector3d& vec);
	f dot_product(const vector3d& vec) const; //scalar dot_product
	vector3d cross_product(const vector3d& vec);    //cross_product
	f magnitude() const;  //magnitude of the vector
	vector3d normalization();   //nor,malized vector
	f square() const; //gives square of the vector

	f distance(const vector3d& vec);    //gives distance between two vectors
	f cosine(const vector3d& vec) const;
	f show_X(); //return x
	f show_Y(); //return y
	f show_Z(); //return z
	void disp();    //display value of vectors

};