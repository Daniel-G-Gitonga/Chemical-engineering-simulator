#include "app.h"
chem::App::App(std::string title_a, float width_a, float height_a) : chem::Window(title_a, width_a , height_a){
setup();
}
chem::App::~App(){
    destroyWindow();
    glfwTerminate();
}

void chem::App::setup(){
   
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   is_window_ready = createWindow();

   
   
}
void chem::App::run(){
    chem::Render*  main_r = new Render();
    chem::Model* test_rectangle = new Model("../../Assets/model/abcd.gltf");

float timer = 0;
glm::mat4 model = glm::translate(glm::rotate(glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f)), glm::radians(0.0f) , glm::vec3(0.5)), glm::vec3(2.0f));


    while(!glfwWindowShouldClose(window_g)){
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glClearColor(1.00f,1.00f,1.00f,1.0f);

timer = static_cast<float>(glfwGetTime()) ;

test_rectangle->drawModel(model);

          glfwPollEvents();
          glfwSwapBuffers(window_g);          
         
    }

    
    delete test_rectangle;
    delete main_r;

}