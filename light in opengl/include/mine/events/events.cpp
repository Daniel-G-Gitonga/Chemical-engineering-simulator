#include "events.h"

namespace rose{
 
Events::Events(){}
void Events::events(GLFWwindow* window){
if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
   glfwSetWindowShouldClose(window, true);
   
}

}
Events::~Events(){}
}