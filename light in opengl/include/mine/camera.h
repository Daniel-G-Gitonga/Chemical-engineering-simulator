#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/*

camera object that can fly over through control
camera obj 2 can follow specific object ....

camera pos 1 _______ camera location
camera looking at __ mostly centre (difference of pos - looking at)
camera up direction_  mostly y direction

for now lets look at fly over camera.
____________________________________
all objects must have the camera(view) matrix


*/

namespace rose{
    class Camera {
public:
float fov;

virtual void set_init_cam(glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp) = 0;
virtual glm::mat4 view() = 0;

    };

    class FlyCam : public Camera{
public:
FlyCam();
glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 cameraUp;

void set_init_cam(glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp);
glm::mat4 view();
~FlyCam();
    };
}