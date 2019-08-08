#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
class VectorGestureData
{

public:

	float orbitPoseStart[26 * 3];
	float orbitPoseEnd[26 * 3];
	float xpose[26 * 3];
	float explode[26 * 3];
	//	float orbitPoseStart[8 * 3];
	VectorGestureData();
	void  scanTextFile(std::string str, float arr[]);
	float weightData(int start, int end, int index, float f);

};