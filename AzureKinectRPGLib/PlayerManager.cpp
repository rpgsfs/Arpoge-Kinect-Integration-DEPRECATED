#pragma comment(lib, "Winmm.lib")
#include "pch.h"
#include "PlayerManager.h"
#include "VectorGestureManager.h"
#include "Gestures.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <k4a/k4a.h>
#include <k4abt.h>
#include <cmath>
#include <windows.h>

//#define K4ABT_INVALID_BODY_ID   0xFFFFFFFF; 
#define VERIFY(result, error)                                                                            \
    if(result != K4A_RESULT_SUCCEEDED)                                                                   \
    {                                                                                                    \
        printf("%s \n - (File: %s, Function: %s, Line: %d)\n", error, __FILE__, __FUNCTION__, __LINE__); \
        exit(1);                                                                                         \
    }                                                                                                    \

void print_body_information(k4abt_body_t body)
{
	printf("Body ID: %u\n", body.id);
	for (int i = 0; i < (int)K4ABT_JOINT_COUNT; i++)
	{
		k4a_float3_t position = body.skeleton.joints[i].position;
		k4a_quaternion_t orientation = body.skeleton.joints[i].orientation;
		printf("Joint[%d]: Position[mm] ( %f, %f, %f ); Orientation ( %f, %f, %f, %f) \n",
			i, position.v[0], position.v[1], position.v[2], orientation.v[0], orientation.v[1], orientation.v[2], orientation.v[3]);
	}
}
PlayerManager::PlayerManager() {
}


void PlayerManager::updateData(k4abt_frame_t body_frame) {


	currentPlayers = k4abt_frame_get_num_bodies(body_frame);
	cout << "Current players" << currentPlayers << endl;
	if (currentPlayers > 0) {
		newTrackedPlayers = updatePlayerBase(body_frame);
		if (isPlayerDoingTPose(newTrackedPlayers)) {
			trackingId = playerIdDoingTPose(newTrackedPlayers);
			//	cout << "tpose trigger switch" << endl;
				//PlaySound("C:\\Users\\nicho\\source\\repos\\AzureKinectRPG\\AzureKinectRPG\\found.wav", NULL, SND_FILENAME);

		}
		if (!PlayerMatchesId(newTrackedPlayers)) {
			cout << "leader lost!" << endl;
			trackingId = newTrackedPlayers[0].skeletonID;
		}
	}


}
Gestures PlayerManager::createGestureFromFrame(k4abt_frame_t body_frame, size_t i) {
	k4abt_body_t body;
	VERIFY(k4abt_frame_get_body_skeleton(body_frame, i, &body.skeleton), "Get body from body frame failed!");
	body.id = k4abt_frame_get_body_id(body_frame, i);
	return Gestures(body);
}


vector<Gestures> PlayerManager::updatePlayerBase(k4abt_frame_t body_frame) {
	vector<Gestures> playersFoundInFrame = vector<Gestures>();
	for (size_t i = 0; i < currentPlayers; i++) {
		playersFoundInFrame.push_back(createGestureFromFrame(body_frame, i));
	}
	return playersFoundInFrame;
}
bool PlayerManager::PlayerMatchesId(vector<Gestures> playerBase) {
	for (int i = 0; i < playerBase.size(); i++) {
		if (trackingId == playerBase[i].skeletonID)
			return true;
	}
	return false;
}
Gestures PlayerManager::returnLeadingPlayer() {
	for (int i = 0; i < newTrackedPlayers.size(); i++) {
		Gestures playersTrackedMember = newTrackedPlayers[i];
		uint32_t pID = playersTrackedMember.skeletonID;
		if (trackingId == pID) {
			//		cout << "leading playerID" << pID << endl;
			return playersTrackedMember;
		}
	}

}
uint32_t PlayerManager::playerIdDoingTPose(vector<Gestures> playerBase) {
	for (int i = 0; i < playerBase.size(); i++) {
		Gestures g = playerBase[i];
		if (g.tPose())
			return g.skeletonID;
	}

}
bool PlayerManager::isPlayerDoingTPose(vector<Gestures> playerBase) {
	for (int i = 0; i < playerBase.size(); i++) {
		Gestures g = playerBase[i];
		if (g.tPose())
			return true;
	}
	return false;
}
void PlayerManager::printAll() {
	for (size_t i = 0; i < newTrackedPlayers.size(); i++) {
		//		cout << i << endl;
				//newTrackedPlayers[i].averageEyesPosition().disp();
	}
}
void PlayerManager::checkTPose() {
	for (int i = 0; i < newTrackedPlayers.size(); i++) {
		if (newTrackedPlayers[i].tPose()) {
			cout << "tpose state" << newTrackedPlayers[i].tPose() << endl;
		}
	}
}