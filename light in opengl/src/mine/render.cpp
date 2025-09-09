#include "mine/render.h"


namespace rose{
    Cube * cube_1 = new Cube();
    Pyramid* pyramid_1 = new Pyramid();
    FlyCam* cam_1 = new FlyCam();

    

    Render::Render(){}
    void Render::initRenderer(int width, int height, std::string win_ttl){  
        Window::createWin(width, height, win_ttl);   
if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
std::cout<<"Failed to load the f'ing glad..."<<std::endl;
}
     cam_1->set_init_cam(glm::vec3(0.0f,0.0f,-1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,1.0f,0.0f));
    cube_1 -> set_c();
    pyramid_1 -> set_c();
    
    

    glEnable(GL_DEPTH_TEST);

    }
    void Render::render(){
glfwPollEvents();

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.0,0.0,0.0,1.0f);

cube_1->draw_c(cam_1->view());
pyramid_1->draw_c(cam_1->view());

glfwSwapBuffers(window);
    }
    void Render::destroyRenderer(){
     Window::destroyWin();
     cube_1->clean();
     pyramid_1->clean();
      delete cam_1;
     delete pyramid_1;
     delete cube_1;
    }
    Render::~Render(){}
};