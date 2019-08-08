#include "pch.h"
#include "Global.h"
/*This is the global fields class. Often, use of globals is highly discouraged. However, this is cool because there will be only one leading player (one set of states to keep track of), and the use of voice recognition can be put into a seperate, independant class.*/
extern bool gestureOrbit(0); // external linkage by default, so this extern is redundant and ignored
extern bool gestureXPose(0); //if this is true, the x pose has been performed.
extern bool gestureExplode(0);//manages the "Explode" gesture state.
extern bool performingGesture(0); //if this is true, a gesture is being performed. 
extern void wipeSlate() {
	gestureOrbit = false;
	gestureXPose = false;
	gestureExplode = false;
	performingGesture = false;
}