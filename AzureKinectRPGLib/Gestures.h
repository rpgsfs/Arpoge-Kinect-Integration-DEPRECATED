#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <k4a/k4a.h>
#include <k4abt.h>
#include "vector3d.h"
#include <vector>
#include "VectorGestureManager.h"

class Gestures {
private:

	//joints
	k4abt_joint_t head = skeleton.joints[K4ABT_JOINT_HEAD];
	k4abt_joint_t neck = skeleton.joints[K4ABT_JOINT_NECK];
	k4abt_joint_t wristRight = skeleton.joints[K4ABT_JOINT_WRIST_RIGHT];
	k4abt_joint_t wristLeft = skeleton.joints[K4ABT_JOINT_WRIST_LEFT];
	k4abt_joint_t elbowRight = skeleton.joints[K4ABT_JOINT_ELBOW_RIGHT];
	k4abt_joint_t elbowLeft = skeleton.joints[K4ABT_JOINT_ELBOW_LEFT];
	k4abt_joint_t eyeRight = skeleton.joints[K4ABT_JOINT_EYE_RIGHT];
	k4abt_joint_t eyeLeft = skeleton.joints[K4ABT_JOINT_EYE_RIGHT];

	//joint point data
	float headY = head.position.xyz.y;
	float neckY = neck.position.xyz.y;
	float wristRightY = wristRight.position.xyz.y;
	float wristLeftY = wristLeft.position.xyz.y;
	float elbowRightY = elbowRight.position.xyz.y;
	float elbowLeftY = elbowLeft.position.xyz.y;
	bool shouldFollow = false;
	float tolerance = 100;
	VectorGestureManager vectorGestureManager = VectorGestureManager(skeleton);

public:
	k4abt_skeleton_t skeleton;

	vector<k4abt_skeleton_t> oldSkeletons;
	Gestures(k4abt_body_t body);

	uint32_t skeletonID;
	bool rightArmLevelWithHead();
	bool leftArmLevelWithHead();
	bool rightWristOverHead();
	bool leftWristOverHead();
	bool tPose();

	bool closeEnough(k4abt_joint_t a, k4abt_joint_t b, int i);
	//	void addOldSkeletonData(vector<k4abt_skeleton_t> oldSkeletonVector);
	vector3d averageEyesPosition();
	vector3d globeHandsPosition();
	//methods that may be added to VectorGestureManager later
	float armElbowLeftVector();
	VectorGestureManager getVectorGestureManager();
	vector3d orbitPoseVector();
	float explodeDistance();
	float jointBend(int a, int b, int c);
	float armRightBend();
	float armLeftBend();
	bool gestureExplode();
	bool cancelGesture();
};