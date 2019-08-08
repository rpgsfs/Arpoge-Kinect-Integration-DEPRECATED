#include "pch.h"
#include "VectorGestureData.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
VectorGestureData::VectorGestureData() {
	scanTextFile("startorbit.txt", orbitPoseStart);
	scanTextFile("neworbit.txt", orbitPoseEnd);
	scanTextFile("xpose.txt", xpose);
	scanTextFile("explode.txt", explode);
}
float VectorGestureData::weightData(int start, int end, int index, float f) {
	if (index >= start && index <= end) {
		std::cout << "index of weight" << index << std::endl;
		return f * 100; //remember to change the other weight if changed
	}
	return f;
}

void VectorGestureData::scanTextFile(std::string str, float arr[]) {

	std::ifstream wormfile(str);
	std::string wormline;
	int index = 0;
	int start = 3 * 4 + 1;
	int end = 12 * 3;
	while (!wormfile.eof())
	{
		getline(wormfile, wormline);
		//	std::cout << wormline << std::endl;

		float f = ::atof(wormline.c_str());
		f = weightData(start, end, index, f);
		if (str == "neworbit.txt") {
			std::cout << "index " << index << " " << f << std::endl;
		}
		arr[index] = f;
		index++;

	}

	wormfile.close();
}