#pragma once
#include <iostream>
#include <vector>
#include "Gestures.h"
#include <k4a/k4a.h>
#include <k4abt.h>
class PlayerManager
{
private:
	size_t currentPlayers = 0; //size_t, which should be got from the bodyframe, should always sync with the size of the player array.
	uint32_t trackingId = 0;
	vector<Gestures> oldTrackedPlayers;
	vector<Gestures> newTrackedPlayers;
public:
	PlayerManager();
	//Gestures returnLeadingPlayer();
	void updateData(k4abt_frame_t body_frame);
	Gestures createGestureFromFrame(k4abt_frame_t body_frame, size_t i);
	Gestures returnLeadingPlayer();
	vector<Gestures> updatePlayerBase(k4abt_frame_t body_frame);
	uint32_t playerIdDoingTPose(vector<Gestures> playerBase);
	void printAll();
	bool PlayerMatchesId(vector<Gestures> playerBase);
	bool isPlayerDoingTPose(vector<Gestures> playerBase);
	void checkTPose();

};
