#include "app.h"
chem::App::App(std::string title_a, float width_a, float height_a) : chem::Window(title_a, width_a , height_a){
setup();
}
chem::App::~App(){
    destroyWindow();
    glfwTerminate();
}

void chem::App::setup(){
   if(!glfwInit()){
    std::cout<<"failed to initialize glfw "<<std::endl;
   }
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   is_window_ready = createWindow();

   
   
}
void chem::App::run(){
    chem::Render*  main_r = new Render();
    chem::Mesh * mesh_test_glass = new Mesh();
  
    
    while(!glfwWindowShouldClose(window_g)){
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glClearColor(0.040f,0.084f,0.072f,1.0f);

mesh_test_glass->useProgram(mesh_test_glass->program_mesh);
mesh_test_glass->renderMesh();

          glfwPollEvents();
          glfwSwapBuffers(window_g);          
         
    }


    delete mesh_test_glass;
    delete main_r;

}