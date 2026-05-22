#pragma  once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer.h"
#include "events.h"


class Cube : public Shader{
public:
std::vector<float> vertices_C = {
    
     // Front face (normal: 0,0,1)
    -0.5f,-0.5f, 0.5f,   0.0f,0.0f,1.0f,   0.0f,0.0f,
     0.5f,-0.5f, 0.5f,   0.0f,0.0f,1.0f,   1.0f,0.0f,
     0.5f, 0.5f, 0.5f,   0.0f,0.0f,1.0f,   1.0f,1.0f,
    -0.5f, 0.5f, 0.5f,   0.0f,0.0f,1.0f,   0.0f,1.0f,

    // Back face (normal: 0,0,-1)
    -0.5f,-0.5f,-0.5f,   0.0f,0.0f,-1.0f,  1.0f,0.0f,
     0.5f,-0.5f,-0.5f,   0.0f,0.0f,-1.0f,  0.0f,0.0f,
     0.5f, 0.5f,-0.5f,   0.0f,0.0f,-1.0f,  0.0f,1.0f,
    -0.5f, 0.5f,-0.5f,   0.0f,0.0f,-1.0f,  1.0f,1.0f,

    // Left face (normal: -1,0,0)
    -0.5f,-0.5f,-0.5f,  -1.0f,0.0f,0.0f,   0.0f,0.0f,
    -0.5f,-0.5f, 0.5f,  -1.0f,0.0f,0.0f,   1.0f,0.0f,
    -0.5f, 0.5f, 0.5f,  -1.0f,0.0f,0.0f,   1.0f,1.0f,
    -0.5f, 0.5f,-0.5f,  -1.0f,0.0f,0.0f,   0.0f,1.0f,

    // Right face (normal: 1,0,0)
     0.5f,-0.5f,-0.5f,   1.0f,0.0f,0.0f,   1.0f,0.0f,
     0.5f,-0.5f, 0.5f,   1.0f,0.0f,0.0f,   0.0f,0.0f,
     0.5f, 0.5f, 0.5f,   1.0f,0.0f,0.0f,   0.0f,1.0f,
     0.5f, 0.5f,-0.5f,   1.0f,0.0f,0.0f,   1.0f,1.0f,

    // Top face (normal: 0,1,0)
    -0.5f, 0.5f, 0.5f,   0.0f,1.0f,0.0f,   0.0f,0.0f,
     0.5f, 0.5f, 0.5f,   0.0f,1.0f,0.0f,   1.0f,0.0f,
     0.5f, 0.5f,-0.5f,   0.0f,1.0f,0.0f,   1.0f,1.0f,
    -0.5f, 0.5f,-0.5f,   0.0f,1.0f,0.0f,   0.0f,1.0f,

    // Bottom face (normal: 0,-1,0)
    -0.5f,-0.5f, 0.5f,   0.0f,-1.0f,0.0f,  1.0f,0.0f,
     0.5f,-0.5f, 0.5f,   0.0f,-1.0f,0.0f,  0.0f,0.0f,
     0.5f,-0.5f,-0.5f,   0.0f,-1.0f,0.0f,  0.0f,1.0f,
    -0.5f,-0.5f,-0.5f,   0.0f,-1.0f,0.0f,  1.0f,1.0f
};
std::vector<unsigned int> indices_C = {
    
    0, 1, 2,
    2, 3, 0,

    // Right
    1, 5, 6,
    6, 2, 1,

    // Back
    5, 4, 7,
    7, 6, 5,

    // Left
    4, 0, 3,
    3, 7, 4,

    // Top
    3, 2, 6,
    6, 7, 3,

    // Bottom
    4, 5, 1,
    1, 0, 4
};
GLuint program_C = program;

void setup();
void draw();
void clean();

glm::mat4 mod_pass = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, 0.0f));
std::string texture_path = "../assets\\texture\\tt.png" ; 
std::string texture_path_specular = "../assets\\texture\\tt_specular.png";
std::string shader_p = "../assets\\shaders\\fragment.glsl";

glm::vec4 vec4_uniform = glm::vec4(1.0f);
glm::vec3 vec3_uniform_light = glm::vec3(1.0f);
glm::vec3 vec3_uniform = glm::vec3(1.0f);
glm::mat4 light_translation =  glm::mat4(1.0f);

~Cube(){
clean();


}
};

class App{
public:
GLFWwindow* window = nullptr;

int width_win = 1200;
int height_win = 600;

App();
~App();

void init_window();
void destroy_win();

void run();
void onEvent(Event &ev);

void raiseEvent(Event& ev);

bool handled = false;
bool cursorMovedEvent(MouseEvents& event);
bool keyPressedEvent(KeyEvents& event);


Cube* cube_a = new Cube();
Cube* cube_b = new Cube();

//SIMPLE CAMERA var

float xOffset = float();
float yOffset = float();
float x_mouse = float();
float y_mouse = float();
float xPos = 300.0f;
float yPos = 300.0f;
float yaw = 0.0f;
float pitch = 0.0f;

};