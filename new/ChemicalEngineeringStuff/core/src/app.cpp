#include "app.h"
chem::App::App(std::string title_a, float width_a, float height_a) : chem::Window(title_a, width_a , height_a){
 
}
void chem::App::setup(){
   
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
   is_window_ready = createWindow();
   main_r->initRenderer();//called here and not in constructor
                           //as before to avoid re calling it
                           //every time we have a new mesh setUp() func being called
                           //it through the constructor
                           //the App constructor creates the contex for use 
   
   glfwSetFramebufferSizeCallback(window_g, frameBufferSizeCallback);
   glfwSetInputMode(window_g, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   for(int i = 0; i < paths.size(); i++){
     loaded_model.push_back(Model(paths[i]));
     //load each model and pass that model to a vector that can later be accessed
     //the draw call is to draw per vector
    }
   
}
void chem::App::set_model_array(std::vector<std::string> path_specified, std::vector<glm::vec3> pos_specified, std::vector<std::string> id_o_model){

paths  = path_specified;
positions = pos_specified;
id = id_o_model;
}
chem::App::~App(){
      for(int i = 0; i < loaded_model.size(); i++){
        loaded_model[i].clean();

}
      delete main_r;
      delete cam_1;
      destroyWindow();
      glfwTerminate();
}


void chem::App::run(){
    current_frame_time = glfwGetTime();  
    while(!glfwWindowShouldClose(window_g)){
          last_frame_time  = current_frame_time;
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glClearColor(1.00f,1.00f,1.00f,1.0f);
  
   last_frame_time = current_frame_time;
   delta_time =  current_frame_time - last_frame_time;

   
   key =   ROSES_HANDS::key_pressed(window_g);//return key pressed per frame___bad habit__ pls correct;;;)))
   glm::mat4 camera  = cam_1->debug_camera_1(perspective, window_g, delta_time);//function must be checked every loop updating

//un updated loop to loop through the lOADED MODELS and draw them
   for(int i = 0; i<loaded_model.size() ; i++){
   model =  glm::translate(glm::rotate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)), timer * glm::radians(45.0f)  , glm::vec3(1.0,1.0f,1.0f)), positions[i]);
   timer = static_cast<float>(glfwGetTime()) ;
   loaded_model[i].drawModel(model, camera);
   }
          
            
         
          glfwPollEvents();
          glfwSwapBuffers(window_g);  
               
         
    }
  

}
void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
if(first_resize){
glViewport(0, 0, width, height);
first_resize = true;
}
}

void chem::App::mini_window(int width, int height, std::string title, bool share_context_with_main_win ){

if(share_context_with_main_win){
mini_win = glfwCreateWindow(width, height, title.c_str(), NULL, window_g);
}else{

mini_win = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
glfwMakeContextCurrent(mini_win);
}

while(!glfwWindowShouldClose(mini_win)){
glfwPollEvents();
glfwSwapBuffers(mini_win);

if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
glClear(GL_COLOR_BUFFER_BIT);
glClearColor(0.0f,0.0f,0.0f,1.0f);
}else{
    std::cout<<"GLAD ERROR"<<std::endl;
    glfwSetWindowShouldClose(mini_win, true);
}
}
glfwDestroyWindow(mini_win);
//will be used for gui and stuff
}
/*
notes
_____
\\
       ::manual render call to init gilad 
;););)

NB//TEXTURES SHOULD GO IN THE TEXTURE FOLDER, IF EXPORTED WITH A FOLDER CONTAINING HEM,
COPY THAT FOLDER INTO THE TEXTURE FOLDER
ENSURE NO SPACING BETWEEN THE TEXTURE NAMING EXISTS

//create an asset manager that manages how everthing is rendered using its specific id
model loaded and stored in vector, model initial position, model id
loaded models are sored in test_rectangle
create a model manager func... id, move according to pisition, render... with new pos ///
*/