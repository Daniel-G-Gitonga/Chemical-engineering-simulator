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
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
   is_window_ready = createWindow();

   
   
}
void chem::App::run(){
    chem::Render*  main_r = new Render();
    main_r->initRenderer();//called here and not in constructor
                           //as before to avoid re calling it
                           //every time we have a new mesh calling
                           //it through the constructor
                           //the App constructor creates the contex for use 
    glViewport(0,0,width, height);
    std::vector<Model> test_rectangle;//vector to store the loaded models for later draw calls
    glfwSetInputMode(window_g, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    for(int i = 0; i < paths.size(); i++){
     test_rectangle.push_back(Model(paths[i]));
     //load each model and pass that model to a vector that can later be accessed
     //the draw call is to draw per vector
    }
    
float timer ;

glm::mat4 model = glm::mat4(1.0f);///model per The obj that to extract mesh from, basically posittions initial, but may change on adding phyc
                ///also transformations like scale


float delta_time = 0;
float current_frame_time = 0;
float last_frame_time = 0;

int key;
std::unique_ptr<ROSES_EYE::Debug_cam> cam_1 = std::make_unique<ROSES_EYE::Debug_cam>();//camera


    while(!glfwWindowShouldClose(window_g)){
          last_frame_time  = current_frame_time;
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glClearColor(1.00f,1.00f,1.00f,1.0f);
  
   
   delta_time =  current_frame_time - last_frame_time;



   key =   ROSES_HANDS::key_pressed(window_g);//return key pressed per frame___bad habit__ pls correct;;;)))
   glm::mat4 camera  = cam_1->debug_camera_1(perspective, window_g, delta_time);//function must be checked every loop updating

   for(int i = 0; i<test_rectangle.size() ; i++){
   model =  glm::translate(glm::rotate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)), timer * glm::radians(0.0f)  , glm::vec3(0.0,0.0f,1.0f)), positions[i]);
   timer = static_cast<float>(glfwGetTime()) ;
    test_rectangle[i].drawModel(model, camera);
   }
          
          
         
          glfwPollEvents();
          glfwSwapBuffers(window_g);  
           current_frame_time = glfwGetTime();        
         
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

NB//TEXTURES SHOULD GO IN THE TEXTURE FOLDER, IF EXPORTED WITH A FOLDER CONTAINING HEM,
COPY THAT FOLDER INTO THE TEXTURE FOLDER
ENSURE NO SPACING BETWEEN THE TEXTURE NAMING EXISTS
*/