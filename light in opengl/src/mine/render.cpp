#include "mine/render.h"

namespace rose{
    Render::Render(){}
    void Render::initRenderer(int width, int height, std::string win_ttl){  
        Window::createWin(width, height, win_ttl);   
if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
std::cout<<"Failed to load the f'ing glad..."<<std::endl;
}
    }
    void Render::render(){
glfwPollEvents();
glfwSwapBuffers(window);
glClear(GL_COLOR_BUFFER_BIT);
glClearColor(0.0,0.0,0.0,1.0f);
    }
    void Render::destroyRenderer(){
     Window::destroyWin();
    }
    Render::~Render(){}
};