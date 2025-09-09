#include "mine/camera.h"

/*
namespace rose{
    class Camera {
public:
glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 cameraUp;

virtual glm::mat4 view() = 0;

    };

    class FlyCam{
public:
glm::mat4 view();
    };
}
*/

namespace rose{

FlyCam::FlyCam(){}
void FlyCam::set_init_cam(glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp){
  glm::vec3  cameraPos = camPos;
  glm::vec3  cameraFront = camFront;
  glm::vec3  cameraUp = camUp;
}
glm::mat4 FlyCam::view(){

    glm::mat4 cam = glm::mat4(1.0f);
    cam = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov), 800.0f/600.0f, 0.1f, 100.0f);
    return projection * cam;
}
FlyCam::~FlyCam(){}



}