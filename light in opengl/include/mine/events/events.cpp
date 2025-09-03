#include "events.h"

namespace rose{
 
Events::Events(){}
void Events::events(GLFWwindow* window){
if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
   glfwSetWindowShouldClose(window, true);  
}
}
Events::~Events(){}

CameraF_Evs::CameraF_Evs(){}
void CameraF_Evs::fly_cam_events(GLFWwindow* window){
if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
float speed = 0.25f;
cameraPos -= cameraFront * speed;
}
}
CameraF_Evs::~CameraF_Evs(){}
}