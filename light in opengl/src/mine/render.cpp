#include "mine/render.h"
#include "mine/mesh.h"

namespace rose{
    Cube * cube_1 = new Cube();
    Pyramid* pyramid_1 = new Pyramid();
    Render::Render(){}
    void Render::initRenderer(int width, int height, std::string win_ttl){  
        Window::createWin(width, height, win_ttl);   
if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
std::cout<<"Failed to load the f'ing glad..."<<std::endl;
}
    
    cube_1 -> set_c();
    pyramid_1 -> set_c();

    glEnable(GL_DEPTH_TEST);

    }
    void Render::render(){
glfwPollEvents();

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.0,0.0,0.0,1.0f);

cube_1->draw_c();
pyramid_1->draw_c();

glfwSwapBuffers(window);
    }
    void Render::destroyRenderer(){
     Window::destroyWin();
     cube_1->clean();
     pyramid_1->clean();

     delete pyramid_1;
     delete cube_1;
    }
    Render::~Render(){}
};