#include <iostream>
#include <vector>

#include <k4a/k4a.h>
#include <k4abt.h>
#include "Gestures.h"
#include "vector3d.h"
// #include "PlayerHolder.h"
#include "PlayerManager.h"
#include "VectorGestureManager.h"
#include "VectorGestureData.h"

#include <windows.h>

#include "Global.h"
//these two headers are already included in the <Windows.h> header
#include "Gestures.h"
#include "vector3d.h"
// #include "PlayerHolder.h"
#include "PlayerManager.h"
#include "VectorGestureManager.h"
#include "VectorGestureData.h"

//#include <windows.h>

#include "Global.h"
#define VERIFY(result, error)																		   	 \
    if(result != K4A_RESULT_SUCCEEDED)                                                                   \
    {                                                                                                    \
        printf("%s \n - (File: %s, Function: %s, Line: %d)\n", error, __FILE__, __FUNCTION__, __LINE__); \
        exit(1);                                                                                         \
    }	\




/*void print_body_information(k4abt_body_t body)
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
*/

extern bool test;
int main()
{
	bool printout = false;
	k4a_device_configuration_t device_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	device_config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;

	k4a_device_t device;
	VERIFY(k4a_device_open(0, &device), "Open K4A Device failed!");
	VERIFY(k4a_device_start_cameras(device, &device_config), "Start K4A cameras failed!");

	k4a_calibration_t sensor_calibration;

	VERIFY(k4a_device_get_calibration(device, device_config.depth_mode, device_config.color_resolution, &sensor_calibration),
		"Get depth camera calibration failed!");
	k4abt_tracker_t tracker = NULL;
	VERIFY(k4abt_tracker_create(&sensor_calibration, &tracker), "Body tracker initialization failed!");
	

	int frame_count = 0;
	std::string input;
	bool madeFirstPlayer = false;

	PlayerManager playerManager = PlayerManager();
//	VectorGestureData vectorGestureData = VectorGestureData();
	vector3d originalHandsPosition = vector3d(0, 0, 0);
	bool setOriginalVector = true;
	do
	{
		
		//std::cout << g_y; // should print 2

		k4a_capture_t sensor_capture;
		k4a_wait_result_t get_capture_result = k4a_device_get_capture(device, &sensor_capture, K4A_WAIT_INFINITE);
		if (get_capture_result == K4A_WAIT_RESULT_SUCCEEDED)
		{
			frame_count++;
			k4a_wait_result_t queue_capture_result = k4abt_tracker_enqueue_capture(tracker, sensor_capture, K4A_WAIT_INFINITE);
			k4a_capture_release(sensor_capture);
			if (queue_capture_result == K4A_WAIT_RESULT_TIMEOUT)
			{
				// It should never hit timeout when K4A_WAIT_INFINITE is set.
				printf("Error! Add capture to tracker process queue timeout!\n");
				break;
			}
			else if (queue_capture_result == K4A_WAIT_RESULT_FAILED)
			{
				printf("Error! Add capture to tracker process queue failed!\n");
				break;
			}

			k4abt_frame_t body_frame = NULL;
			k4a_wait_result_t pop_frame_result = k4abt_tracker_pop_result(tracker, &body_frame, K4A_WAIT_INFINITE);


			if (pop_frame_result == K4A_WAIT_RESULT_SUCCEEDED)
			{
				size_t num_bodies = k4abt_frame_get_num_bodies(body_frame);
				extern bool performingGesture;
				extern void wipeSlate();
				if (num_bodies == 0) {					
					wipeSlate();
					setOriginalVector = true;

					cout << "performingGestureFalse" << endl;
				}
				playerManager.updateData(body_frame);
				if (num_bodies > 0) {
					//	playerManager.returnLeadingPlayer().averageEyesPosition().disp();
					//	cout << playerManager.returnLeadingPlayer().globeHandsStart() << endl;
						//playerManager.returnLeadingPlayer().averageEyesPosition().disp();
					Gestures g = playerManager.returnLeadingPlayer();
					cout << "_START_"<< "_HEADPOSITION_ ";
						g.averageEyesPosition().disp();
						cout << "_END_" << endl;
		//			g.getVectorGestureManager().update(vectorGestureData.orbitPoseStart, vectorGestureData.orbitPoseEnd, vectorGestureData.xpose, vectorGestureData.explode, .97);
						cout << "armbendright" << g.armRightBend() << endl;
					cout << "armbendleft" << g.armLeftBend() << endl;
				/*		if (!performingGesture) {
							performingGesture = g.gestureExplode(); //ADD
							cout << performingGesture << "perfgesture" << endl;
							cout << "KAPOW" << endl;
						}*/
						if (performingGesture && g.cancelGesture()) {
							cout << "_START__PLAYSOUND_ stop_END_" << endl;
							setOriginalVector = g.cancelGesture();

						}
						extern bool gestureExplode;
						if (!gestureExplode) {
							bool activate = g.gestureExplode();
							gestureExplode = activate;
							if (activate) {
								cout << "_START__PLAYSOUND_ scale_END_" << endl;
							}
							
						}
						extern bool gestureOrbit;
						if (!gestureOrbit) {
							bool activate = g.gestureExplode();
							gestureOrbit = activate;
							if (activate) {
								cout << "_START__PLAYSOUND_ rotate_END_" << endl;
							}
						}
						
					if(performingGesture)  {
					//	cout << "PERFORMING GESTURE" << endl;
						extern bool gestureXPose;
				//		extern bool gestureExplode;
						if (gestureOrbit) {
							cout << "_START__PLAYSOUND_ scale_END_" << endl;
							if (setOriginalVector) {
								setOriginalVector = false;
							//	cout << "HI" << endl;
								originalHandsPosition = g.orbitPoseVector();
							}
							cout << "_START_";
							cout << "_ORBIT_ ";
							ShellExecute(NULL, TEXT("open"), TEXT("https://www.youtube.com/watch?v=dQw4w9WgXcQ"), NULL, NULL, 0);
							originalHandsPosition.disp();
						//	cout << "_ORBITPOSE_ ";
							cout << " ";
							g.orbitPoseVector().disp();
						
							cout << "_END_" << endl;
						}
						
						if (gestureExplode) {
							cout << "_START_";
							cout << "_EXPLODE_ " << g.explodeDistance();
							cout << "_END_" << endl;
						}
					    if (gestureXPose) {
							cout << "_WIPE_";
							setOriginalVector = true;
							wipeSlate();
						}
					

					}

				}
				//	printf("%zu bodies are detected!\n", num_bodies);


				k4abt_frame_release(body_frame);
			}
			else if (pop_frame_result == K4A_WAIT_RESULT_TIMEOUT)
			{
				//  It should never hit timeout when K4A_WAIT_INFINITE is set.
				printf("Error! Pop body frame result timeout!\n");
				break;
			}
			else
			{
				printf("Pop body frame result failed!\n");
				break;
			}
		}
		else if (get_capture_result == K4A_WAIT_RESULT_TIMEOUT)
		{
			// It should never hit time out when K4A_WAIT_INFINITE is set.
			printf("Error! Get depth frame time out!\n");
			break;
		}
		else
		{
			printf("Get depth capture returned error: %d\n", get_capture_result);
			break;
		}

		std::cout << "_KEEPALIVE_" << std::flush;
	}while (cin >> input);
//while (true);

	printf("Finished body tracking processing!\n");

	k4abt_tracker_shutdown(tracker);
	k4abt_tracker_destroy(tracker);
	k4a_device_stop_cameras(device);
	k4a_device_close(device);

	return 0;
}