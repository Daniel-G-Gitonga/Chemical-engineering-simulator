#pragma once
#include "pch.h"
#include "GLFW/glfw3.h"

namespace ROSES_EYE{

class Camera{
private:
bool first_access = true;
double last_x_pos;
double last_y_pos;
double xpos;
double ypos;

float yaw = 0.0f;
float pitch = 0.0f;
float roll = 0.0f;

protected:
glm::vec3 camera_position = glm::vec3(2.0f,2.0f, 2.0f);
glm::vec3 where_rose_looks = glm::vec3(2.0f,0.0f, -2.0f);
glm::vec3 camera_up = glm::vec3(0.0f,1.0f,0.0f);


public:
glm::mat4 camera_setUp(GLFWwindow* window, float delta_time);
void      mouse_camera(GLFWwindow* window, double xPosition, double yPosition);

};
class Debug_cam : public Camera{
    public:
glm::mat4 debug_camera_1(view  view_passed, GLFWwindow* window, float delta_time);    

};
class Scene_cam : public Camera{

};

};