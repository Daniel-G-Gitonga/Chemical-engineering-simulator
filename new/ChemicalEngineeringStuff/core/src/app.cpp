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
    main_r->initRenderer();//called here and not in constructor
                           //as before to avoid re calling it
                           //every time we have a new mesh calling
                           //it through the constructor
                           //the App constructor creates the contex for use 
    std::vector<Model> test_rectangle;//vector to store the loaded models for later draw calls

    
    for(int i = 0; i < paths.size(); i++){
     test_rectangle.push_back(Model(paths[i]));
     //load each model and pass that model to a vector that can later be accessed
     //the draw call is to draw per vector
    }
    
float timer ;


    while(!glfwWindowShouldClose(window_g)){
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glClearColor(1.00f,1.00f,1.00f,1.0f);




   for(int i = 0; i<test_rectangle.size() ; i++){
   glm::mat4 model = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f , 100.0f) * glm::translate(glm::rotate(glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.3f)), timer * glm::radians(45.0f)  , glm::vec3(0.0,0.0f,1.0f)), positions[i]);
   timer = static_cast<float>(glfwGetTime()) ;
    test_rectangle[i].drawModel(model);
   }
          glfwPollEvents();
          glfwSwapBuffers(window_g);          
         
    }


    for(int i = 0; i < test_rectangle.size(); i++){
        test_rectangle[i].clean();

}
    delete main_r;

}
void chem::App::set_model_array(std::vector<std::string> path_specified, std::vector<glm::vec3> pos_specified){

paths  = path_specified;
positions = pos_specified;

}



/*
notes
_____
no memory released in anything, opt later
..added:: clean func
       ::manual render call to init gilad 
;););)
*/