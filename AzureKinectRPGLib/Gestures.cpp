#include "pch.h"
#include "Gestures.h"
#include <stdio.h>
#include <stdlib.h>
#include <k4a/k4a.h>
#include <k4abt.h>
#include <cmath>
#include "vector3d.h"
#include <vector>
#include "VectorGestureManager.h"

//class Gestures {

	//k4abt_skeleton_t skeleton;
	//k4abt_joint_t head = skeleton.joints[K4ABT_JOINT_HEAD];
	//k4abt_joint_t wristRight = skeleton.joints[K4ABT_JOINT_WRIST_RIGHT];
	//k4abt_joint_t wristLeft = skeleton.joints[K4ABT_JOINT_WRIST_LEFT];
	//k4abt_joint_t elbowRight = skeleton.joints[K4ABT_JOINT_ELBOW_RIGHT];
	//k4abt_joint_t elbowLeft = skeleton.joints[K4ABT_JOINT_ELBOW_LEFT];

	////joint point data
	//float headY = head.position.xyz.y;
	//float wristRightY = wristRight.position.xyz.y;
	//float wristRightY = wristLeft.position.xyz.y;
	//float elbowRightY = elbowRight.position.xyz.y;
	//float elbowLeftY = elbowLeft.position.xyz.y;
	//float tolerance = 200;
//public:
Gestures::Gestures(k4abt_body_t body) {
	skeleton = body.skeleton;
	skeletonID = body.id;
	vectorGestureManager = VectorGestureManager(skeleton);
	head = skeleton.joints[K4ABT_JOINT_HEAD];
	neck = skeleton.joints[K4ABT_JOINT_NECK];
	wristRight = skeleton.joints[K4ABT_JOINT_WRIST_RIGHT];
	wristLeft = skeleton.joints[K4ABT_JOINT_WRIST_LEFT];
	elbowRight = skeleton.joints[K4ABT_JOINT_ELBOW_RIGHT];
	elbowLeft = skeleton.joints[K4ABT_JOINT_ELBOW_LEFT];
	eyeRight = skeleton.joints[K4ABT_JOINT_EYE_RIGHT];
	eyeLeft = skeleton.joints[K4ABT_JOINT_EYE_RIGHT];


	headY = head.position.xyz.y;
	neckY = neck.position.xyz.y;
	wristRightY = wristRight.position.xyz.y;
	wristLeftY = wristLeft.position.xyz.y;
	elbowRightY = elbowRight.position.xyz.y;
	elbowLeftY = elbowLeft.position.xyz.y;
	shouldFollow = false;
	tolerance = 100;


}

bool Gestures::rightArmLevelWithHead() {
	float average = (elbowRightY + wristRightY + neckY) / 3;
	return (abs(average - neckY) < tolerance && abs(wristRightY - elbowRightY) < tolerance);
}
bool Gestures::leftArmLevelWithHead() {
	float average = (elbowLeftY + wristLeftY + neckY) / 3;
	return (abs(average - neckY) < tolerance && abs(wristLeftY - elbowLeftY) < tolerance);
}
bool Gestures::rightWristOverHead()
{
	return (wristRightY < headY);
}
bool Gestures::leftWristOverHead()
{
	return (wristRightY < headY);
}
bool Gestures::tPose() {//checks if the user has head at same level as both wrists
	float average = (headY + wristRightY + wristRightY) / 3;
	return (abs(average - headY) < tolerance && abs(wristRightY - wristRightY) < tolerance && rightArmLevelWithHead() && leftArmLevelWithHead());
}
/*	void Gestures :: addOldSkeletonData(vector<k4abt_skeleton_t> oldSkeletonVector) {
		oldSkeletons = oldSkeletonVector;
		cout << "success withen gesturemethodBEFORE" << oldSkeletons.size() << endl;
		oldSkeletons.push_back(skeleton);
		cout << "success withen gesturemethod" << oldSkeletons.size() << endl;
	}*/

vector3d Gestures::globeHandsPosition() {
	vector3d handRightVector = vector3d(wristRight);
	vector3d handLeftVector = vector3d(wristLeft);
	vector3d returnd = vector3d();
	return (handRightVector - handLeftVector).normalization();

}


vector3d Gestures::averageEyesPosition() {
	vector3d eyeRightVector = vector3d(eyeRight);
	vector3d eyeLeftVector = vector3d(eyeLeft);
	vector3d eyeAverage = (eyeRightVector + eyeLeftVector) / 2;
	return eyeAverage;

}
bool Gestures::closeEnough(k4abt_joint_t a, k4abt_joint_t b, int i) {
	if (i > -1 && i < 3)
		return (abs(a.position.v[i] - b.position.v[i]) > tolerance);
	else {
		cout << "out of index at closeEnough" << endl;
		return false;
	}

}
float Gestures::armElbowLeftVector() {
	vector3d vectorWristRight = vector3d(wristRight);
	vector3d vectorElbowRight = vector3d(elbowRight);
	float o = vectorWristRight.cosine(vectorElbowRight);
	//	cout << o << endl;
	return acos(o);
}
VectorGestureManager Gestures::getVectorGestureManager() {

	return vectorGestureManager;
}
vector3d Gestures::orbitPoseVector() {
	return vector3d(wristRight) - vector3d(wristLeft);
}
float Gestures::explodeDistance() {
	return vector3d(wristRight).distance(wristLeft);
}
float Gestures::jointBend(int a, int b,  int c){
	auto vecA =vector3d(skeleton.joints[a]);
	auto vecB = vector3d(skeleton.joints[b]);
	auto vecC = vector3d(skeleton.joints[c]);

	/*cout << "Starting joint prints" << endl;
	vecA.disp();
	vecB.disp();
	vecC.disp();
	cout << "Ending joint prints" << endl;*/

	vector3d ba = vecA - vecB;
	vector3d cb = vecB - vecC;
	return 1 - ba.cosine(cb);
	
}
float Gestures::armRightBend() {
	return jointBend(K4ABT_JOINT_WRIST_RIGHT, K4ABT_JOINT_ELBOW_RIGHT, K4ABT_JOINT_SHOULDER_RIGHT);
}
float Gestures::armLeftBend() {
	return jointBend(K4ABT_JOINT_WRIST_LEFT, K4ABT_JOINT_ELBOW_LEFT, K4ABT_JOINT_SHOULDER_LEFT);
}
bool Gestures::gestureExplode() {
	extern bool performingGesture;
	if (abs(armRightBend() - 1) < .2 && abs(armLeftBend() - 1) < .2) {
		performingGesture = true;
		return true;
	}
	return false;
}
bool Gestures::cancelGesture() {
	extern void wipeSlate();
	float pelvisY = skeleton.joints[K4ABT_JOINT_PELVIS].position.xyz.y - 100;
	if (wristLeftY > pelvisY && wristRightY > pelvisY) {
		if (abs(armRightBend()) > .2 && abs(armLeftBend()) > .2) {
			cout << "CANCEL" << endl;
			wipeSlate();
			return true;
		}
	}
	return false;
}
