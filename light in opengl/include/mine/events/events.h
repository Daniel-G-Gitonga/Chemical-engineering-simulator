#pragma once
#include <GLFW/glfw3.h>
#include "mine/src.h"
#include "mine/src.h"
#include "mine/camera.h"

namespace rose{
class Events {
public:
Events();
void events(GLFWwindow* window);
~Events();
};

class CameraF_Evs : public FlyCam{
public:
CameraF_Evs();
void fly_cam_events(GLFWwindow* window);
~CameraF_Evs();

};
}
