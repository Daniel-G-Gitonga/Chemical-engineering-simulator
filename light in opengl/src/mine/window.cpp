#include "mine/window.h"

namespace rose{
    
    Window::Window(){}
    void Window::createWin(int width, int height, std::string win_ttl){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFWwindow* win = glfwCreateWindow(width, height, win_ttl.c_str(),NULL,NULL);
        window  = win;
        glfwMakeContextCurrent(window);
    }
    bool Window::closeWin(){
        return glfwWindowShouldClose(window);
        }
    void Window::destroyWin(){
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    Window::~Window(){
    
    }
}