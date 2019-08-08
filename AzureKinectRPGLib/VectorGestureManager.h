#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <k4a/k4a.h>
#include <k4abt.h>
#include "vector3d.h"


#include <vector>
class VectorGestureManager {
private:
	vector3d pelvis;
	float skeletonMegaVector[26 * 3];
	float poseStart[26 * 3];
	int	skeletonMegaVectorLength = 26 * 3;
	bool orbitPose = false;
	float cosineOrbit;
	float cosineXPose;
	float cosineExplode;

	//float skeletonMegaVector[8 * 3];
	//float poseStart[8 * 3];
	//int	skeletonMegaVectorLength = 8 * 3;

public:
	VectorGestureManager(k4abt_skeleton_t skeleton);

	vector3d subtractPelvis(_k4abt_joint_t joint);
	vector3d weightVector(vector3d vector); //weights joints 4 through 11, inclusive
	float vectorComponentFromVector(vector3d vector, int index);
	float megaMagnitude(float arr[]);
	float megaDotProduct(float arr[]);
	float cosineSimalarity(float arr[]);
	void update(float orbitStart[], float orbitEnd[], float xPose[], float explode[],float accuracy);
	void updateOrbit(float orbitStart[], float orbitEnd[], float accuracy);
	void updateXPose(float xPose[], float accuracy);
	void updateExplode(float explode[], float accuracy);
	void updatePerformingGesture(); //this method modifies the performingGesture bool
	void conflictResolve(); //this method makes sure only one gesture is being done
};