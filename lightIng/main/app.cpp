#include "app.h"

glm::vec3 normalized_cursor = glm::vec3();
float normalized_cursorX = float();
float normalized_cursorY  = float();
glm::vec3 view_pos = glm::vec3(0.0f, 0.0f, -4.0f);
glm::vec3 look_dir  = glm::vec3(-0.197330f, 0.057564f, 0.978646f);
glm::vec3 world_up  = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 camera = glm::mat4(1.0f);

App::App(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
}
void App::init_window(){
    window = glfwCreateWindow(1200, 600, "light", NULL, NULL);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
    printf("Error loading GLAD \n");
    }

    glfwGetWindowSize(window, &width_win, &height_win);
    glViewport(0, 0, width_win, height_win);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height){
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        glViewport(0, 0, width, height);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y){
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        MouseEvents ev(x, y);
        app->raiseEvent(ev);
    });
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods ){
      App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
      KeyEvents ev(key, scancode, action, mods);
      app->raiseEvent(ev);
    });

}
void App::run(){
    init_window();
    if(window == nullptr){
printf("no window present \n");
glfwTerminate();
    }
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_MULTISAMPLE);
    
    cube_a->setup();
      //cube_b->texture_path = "../assets\\texture\\tm.png";
    cube_b->shader_p = "../assets\\shaders\\light_fragment.glsl";
    cube_b->setup();


while(!glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     
        if(glfwGetKey(window, GLFW_KEY_W) ==  GLFW_PRESS){
        view_pos += look_dir * 0.5f; 
        }
      
        if(glfwGetKey(window, GLFW_KEY_S) ==  GLFW_PRESS){
        view_pos -= look_dir * 0.5f;
        }
    

     

      glUseProgram(cube_a->program_C);
      cube_a->vec4_uniform = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);//color of light sent to the main obj we r analiysing
      cube_a->mod_pass = glm::rotate(glm::mat4(1.0f), static_cast<float>(sin(glfwGetTime()))   * glm::radians(10.0f), glm::vec3(1.0f, 1.0f, 1.0f));
      cube_a->draw();

      glUseProgram(cube_b->program_C);
      //glm::vec3(0.0f, 1.0f, 4.0f) light pos
      cube_b->mod_pass = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)), glm::vec3(2.0f, 0.0f, -6.0f));    
      cube_b->light_translation = cube_b->mod_pass;
      cube_b->vec4_uniform = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);//color of light
      cube_b->draw();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
  
}
void App::destroy_win(){
glfwDestroyWindow(window);
}
void App::onEvent(Event &ev){
 if(ev.eventType() == MOUSE_MOVED_EVENT){
 handled = cursorMovedEvent(dynamic_cast<MouseEvents&>(ev));
 }
 if(ev.eventType() == KEY_PRESSED_EVENT){
 handled = keyPressedEvent(dynamic_cast<KeyEvents&>(ev));
 }
}
bool App::cursorMovedEvent(MouseEvents& ev){
x_mouse = ev.x;
y_mouse = ev.y;

normalized_cursor = (glm::vec3(static_cast<float>(ev.x), static_cast<float>(ev.y), 0.0f));
if(normalized_cursor == glm::vec3(300.0f, 300.0f ,0.0f)){
normalized_cursorX = 0;
normalized_cursorY = 0;

}
if(normalized_cursor.x > 300.0f){
normalized_cursorX = (normalized_cursor.x - 300.0f)/300.0f ;//* 5.0f;
}
if(normalized_cursor.y > 300.0){
normalized_cursorY = (300.0f - normalized_cursor.y)/300.0f ;//* 5.0f;
}
if(normalized_cursor.x < 300.0){
normalized_cursorX = (normalized_cursor.x - 300.0f)/300.0f ;//* 5.0f;
}
if(normalized_cursor.y < 300.0){
normalized_cursorY = ( 300.0f - normalized_cursor.y)/300.0f ;//* 5.0f;
}
normalized_cursor = glm::vec3(normalized_cursorX, normalized_cursorY, 4.0f);

float sensitivity = 0.3;
xOffset = x_mouse - xPos;
yOffset = y_mouse - yPos;
xPos  = x_mouse;
yPos = y_mouse;

yaw   += xOffset   * sensitivity;
pitch += yOffset * sensitivity;


glm::vec3 direction;
   direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
   direction.y = sin(glm::radians(pitch));
   direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
look_dir = direction;



   //printf(" %s (%.5f, %.5f)\n",ev.eventToString().c_str(), normalized_cursorX, normalized_cursorY);
   //printf("handled ? %d \n", handled);
   return true;
}
bool App::keyPressedEvent(KeyEvents& ev){
    if(ev.key_pressed_code == GLFW_KEY_1 && ev.action_c == GLFW_PRESS){
        printf("(%f, %f, %f) \n",look_dir.x, look_dir.y, look_dir.z);
    }
//printf(" %s {%d} repeate {%d}\n",ev.eventToString().c_str(),ev.key_pressed_code,ev.action_c);
return true;
}
void App::raiseEvent(Event& ev){
 onEvent(ev);
}
App::~App(){
delete cube_a;
delete cube_b;
destroy_win();
glfwTerminate();
}



void Cube::setup(){
    loadShader("../assets\\shaders\\vertex.glsl", shader_p);//CHANGE TO GOOD COMPACT
    compileShader(vertices_C, indices_C);
    texture   = loadTexture(texture_path, 0);
    texture_2 = loadTexture(texture_path_specular, 1);
}
void Cube::draw(){
    glBindVertexArray(VAO);
    glUseProgram(program);
    camera = glm::lookAt(
        view_pos,
        look_dir + view_pos,
        world_up
    );;

    uniform("model", mod_pass);
    uniform("view", camera);
    uniform("projection", glm::perspective(glm::radians(70.0f), 2.0f, 0.1f, 100.0f));
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE0);
    uniform("cubeTexture", 0);
    glBindTexture(GL_TEXTURE_2D, texture_2);
    glActiveTexture(GL_TEXTURE1);
    uniform("cubeTexture_specularMap", 1);
    uniform("vec4_uniform", vec4_uniform);
    uniform("vec3_uniform", vec3_uniform);
    uniform("view_pos", view_pos);
    uniform("light_translation", light_translation);
    
    

    drawObj(indices_C.size());
}
void Cube::clean(){
    glBindVertexArray(0);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
}

