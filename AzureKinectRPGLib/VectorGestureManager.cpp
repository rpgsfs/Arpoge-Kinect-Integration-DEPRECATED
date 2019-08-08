#include "pch.h"
#include "VectorGestureManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <k4a/k4a.h>
#include <k4abt.h>
#include "vector3d.h"

#include <vector>
#include "Global.h"
#include <Windows.h>

VectorGestureManager::VectorGestureManager(k4abt_skeleton_t skeleton) {
	pelvis = vector3d(skeleton.joints[K4ABT_JOINT_PELVIS]);

	vector<vector3d> allJoints;
//	cout << "BEGIN POSITION PRINT" << endl;
	for (int i = 0; i < 26; i++) {
		allJoints.push_back(subtractPelvis(skeleton.joints[i]));
		if (i > 3 && i < 12) {
			allJoints[i] = weightVector(allJoints[i]); //these joints are the wrists, elbows, and shoulders. https://docs.microsoft.com/en-us/azure/kinect-dk/body-joints for documentation.
		}
//			subtractPelvis(skeleton.joints[i]).disp();
	}
	int index = 0;
	for (int i = 0; i < 26; i++) {
		//for(int i = 4; i < 12;i++){

		for (int j = 0; j < 3; j++) {

			skeletonMegaVector[index] = vectorComponentFromVector(allJoints[i], j);
			index++;
		}

	}
//	cout << "END POSITION PRINT" << endl;


}

vector3d VectorGestureManager::subtractPelvis(_k4abt_joint_t joint) {
	vector3d jointVector = vector3d(joint);
	return jointVector - pelvis;
}
vector3d VectorGestureManager::weightVector(vector3d vector) {
	float weight = 100; //remember to change in both locations
	vector.x = vector.x * weight;
	vector.y = vector.y * weight;
	vector.z = vector.z * weight;
	return vector;
}


float VectorGestureManager::vectorComponentFromVector(vector3d vector, int index) {
	if (index == 0)
		return vector.show_X();
	if (index == 1)
		return vector.show_Y();
	if (index == 2)
		return vector.show_Z();
	else {
		cout << "BAD INPUT" << endl;
		return -1;
	}
}
float VectorGestureManager::megaMagnitude(float arr[]) {
	float square = 0;
	for (int i = 0; i < skeletonMegaVectorLength; i++) {
		square += arr[i] * arr[i];
	}
	return sqrt(square);
}
float VectorGestureManager::megaDotProduct(float arr[]) {
	float sum = 0;
	for (int i = 0; i < skeletonMegaVectorLength; i++) {
		sum += arr[i] * skeletonMegaVector[i];
	}
	//	cout << "sum" << sum << endl;
	return sum;
}
float VectorGestureManager::cosineSimalarity(float arr[]) {
	float f = megaDotProduct(arr) / (megaMagnitude(arr) * megaMagnitude(skeletonMegaVector));
	cout << "cosine" << f << endl;

	return f;
}
void VectorGestureManager::updateOrbit(float orbitStart[], float orbitEnd[], float accuracy) {
	extern bool gestureOrbit;
	cosineOrbit = cosineSimalarity(orbitStart);
	cout << "orbit" << cosineSimalarity(orbitStart) << endl;
	if (cosineOrbit > accuracy) {
		orbitPose = true;
		gestureOrbit = true;
	}

}
void VectorGestureManager::updateXPose(float xPose[], float accuracy) {
	extern bool gestureXPose;
	cosineXPose = cosineSimalarity(xPose);
//	cout << "xpose" << cosineSimalarity(xPose) << endl;
	if (cosineXPose > accuracy) {
		gestureXPose = true;
		//PlaySound("C:\\Users\\nicho\\source\\repos\\AzureKinectRPGFinal\\AzureKinectRPGFinal\\found.wav", NULL, SND_FILENAME);

	}
}
void VectorGestureManager::updateExplode(float explode[], float accuracy) {
	extern bool gestureExplode;
	cosineExplode = cosineSimalarity(explode);
	bool temp = gestureExplode;
	cout << "explode" << cosineSimalarity(explode) << endl;
	if (cosineExplode > accuracy) {
		gestureExplode = true;
	}
	if (!temp && gestureExplode) {
	//	PlaySound("found.wav", NULL, SND_FILENAME);
	}
}
void VectorGestureManager::updatePerformingGesture() {//GB
	extern bool gestureOrbit;
	extern bool gestureExplode;
	extern bool performingGesture;
	
	if (gestureOrbit || gestureExplode) {
	//	cout << "UPDATEPERFORMINGGESTURESETTRUE" << endl;
		performingGesture = true;
	}
}
void VectorGestureManager::update(float orbitStart[], float orbitEnd[], float xPose[], float explode[], float accuracy) {
	updateOrbit(orbitStart, orbitEnd, accuracy);
	updateXPose(xPose, accuracy);
	updateExplode(explode, accuracy);
	updatePerformingGesture();

}
void VectorGestureManager::conflictResolve() {//GB
	extern bool gestureOrbit;
	extern bool gestureXPose;
	extern bool gestureExplode;
	int amt = gestureOrbit + gestureXPose + gestureExplode;
	if (amt > 1) {
		float max = max(gestureOrbit, max(gestureXPose, gestureExplode));
	}
	

}

