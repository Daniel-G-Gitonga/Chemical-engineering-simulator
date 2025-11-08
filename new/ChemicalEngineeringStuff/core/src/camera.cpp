#include "camera.h"


glm::mat4 ROSES_EYE::Camera::camera_setUp(GLFWwindow* window, float delta_time){
float speed = 0.25f;
glfwGetCursorPos(window, &xpos, &ypos);
mouse_camera(window, xpos, ypos);


if(glfwGetKey(window,  GLFW_KEY_W) == GLFW_PRESS/*W in glfw*/){
   camera_position +=  where_rose_looks * speed;
   printf("CAMERA POSITION ==> (%.5f,%.5f,%.5f) ",camera_position.x, camera_position.y, camera_position.z);
}
if(glfwGetKey(window,  GLFW_KEY_A) == GLFW_PRESS/*A in glfw*/){
   camera_position -= glm::normalize(glm::cross(where_rose_looks ,camera_up));
   printf("CAMERA POSITION ==> (%.5f,%.5f,%.5f) ",camera_position.x, camera_position.y, camera_position.z);
}
if(glfwGetKey(window,  GLFW_KEY_S) == GLFW_PRESS/*S in glfw*/){
    camera_position -= where_rose_looks  * speed;
    printf("CAMERA POSITION ==> (%.5f,%.5f,%.5f) ",camera_position.x, camera_position.y, camera_position.z);

}

if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS/*D in glfw*/){
    camera_position += glm::normalize(glm::cross(where_rose_looks , camera_up));
    printf("CAMERA POSITION ==> (%.5f,%.5f,%.5f) ",camera_position.x, camera_position.y, camera_position.z);
}
if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS/*D in glfw*/){
    camera_position = glm::vec3(0.0f,2.0f,0.0f);///reset position to y = 2
    where_rose_looks.y = 2.0f;///reseting the position and
    where_rose_looks.z = -2.0f;///camera front
    printf("CAMERA POSITION ==> (%.5f,%.5f,%.5f) ",camera_position.x, camera_position.y, camera_position.z);
    speed = 0.85f;
}
if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS/*D in glfw*/){
    speed += speed;
}

if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS){
glm::vec3 looking_at = camera_position + where_rose_looks;
printf(" POSITION BEING LOOKED AT ==> (%.6f, %.6f, %.6f) ",looking_at.x ,looking_at.y, looking_at.z);
}


glm::mat4 camera = glm::lookAt(
   camera_position,
   camera_position + where_rose_looks,//camera
   camera_up
);

return camera;

}

glm::mat4 ROSES_EYE::Debug_cam::debug_camera_1(view view_passed, GLFWwindow* window, float delta_time){

if(view_passed == orthographic){
    return glm::ortho(0.0f ,800.0f ,0.0f ,600.0f ,0.1f, 100.0f) * camera_setUp(window, delta_time);
}else{
    return glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f) * camera_setUp(window, delta_time);
}
}   
void ROSES_EYE::Camera::mouse_camera(GLFWwindow* window, double xPosition, double yPosition){
//call in glfwcursor or smt in app,,, 
glm::vec3 direction;
if(first_access){
    last_x_pos = xPosition;//center for a normal 800 width screen
    last_y_pos = yPosition;//center for a normal 600 height screen

first_access = false;
}




//use offsets to do calculations
//    offset| position_collected_from_mouse | last_position recorded
float xOffset = static_cast<float>(xPosition) - static_cast<float>(last_x_pos);
float yOffset = static_cast<float>(last_y_pos) - static_cast<float>(yPosition);


last_x_pos = xPosition;
last_y_pos = yPosition;


float sensitivity = 0.1f;
xOffset = xOffset * sensitivity;
yOffset = yOffset * sensitivity;



yaw += xOffset;
pitch += yOffset;


if(pitch >= 90.0f){
pitch = 90.0f;
}if(pitch <= -90.0f){
pitch = -90.0f;    
}

direction.y =  glm::sin(glm::radians(pitch)) ;
direction.x = glm::cos(glm::radians(yaw)) + glm::cos(glm::radians(pitch));
direction.z = glm::cos(glm::radians(pitch)) + glm::sin(glm::radians(yaw));


where_rose_looks = glm::normalize(direction);
}