#include "key.h"

int ROSES_HANDS::key_pressed(GLFWwindow* window){

int key_p;
for(int key = GLFW_KEY_SPACE ; key <= GLFW_KEY_LAST ; key++){
 if(glfwGetKey(window, key) == GLFW_PRESS){
    std::cout<<"KEY PRESSED "<<key<<std::endl;
    key_p = key;
 }else{
    key_p = 0;
 }
}
return key_p;
}
