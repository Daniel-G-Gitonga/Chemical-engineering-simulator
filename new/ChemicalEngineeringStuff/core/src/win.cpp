#include "win.h"

void CHEM_ENG_ROSE chem::mess(std::string message){
std::cout<<" message ==> "<<message<<std::endl;
}

bool chem::Window::createWindow(){
    if(width==0 || height == 0 || title == ""){
       std::cout<<"ERROR , NO INITIALIZED ARGUMENTS FOR THE FUNCTION CREATE WINDOW:: ERR ::ERR "<<std::endl;
       printf("tilte -> %s ", title.c_str());
       printf("width -> %3f ", width);
       printf(" height -> %4f ",height);
    }
    window_g= glfwCreateWindow(width, height, title.c_str(), NULL, NULL );
    if(!window_g){
        std::cout<<"Error creating the window..."<<std::endl;
        return false;
    }     
    int width_lamb = width;
    int height_lamb = height;
    glfwMakeContextCurrent(window_g);

   // glfwSetFramebufferSizeCallback(window_g,[](GLFWwindow* window, int width, int height){glViewport(0,0,width, height);});
    return true;
}
void chem::Window::destroyWindow(){
    glfwDestroyWindow(window_g);
}

chem::Window::Window(std::string title_a, float width_a, float height_a){
this->title = title_a;
this->width = width_a;
this->height = height_a;
if(!glfwInit()){
    std::cout<<"failed to initialize glfw "<<std::endl;
   }

}
chem::Window::~Window(){
 chem::Window::destroyWindow();
}