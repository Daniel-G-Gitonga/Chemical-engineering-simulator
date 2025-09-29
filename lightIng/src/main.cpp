#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <string>
#include <sstream>

 #define STB_IMAGE_IMPLEMENTATION
   #include "stb_image.h"

GLuint VAO[5];
GLuint VBO[5];
GLuint    cube_program , pyramid_program;
glm::mat4 calcProjection;

double yaw = -90.0f;
double pitch = 00.0f;
float radius = 5.0f;

glm::vec3 target = glm::vec3(0.0f,0.0f,0.0f);

glm::vec3 cameraPos = glm::vec3(0.0f,2.0f,5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f,1.0f,0.0f);
float lastx = 400 , lasty = 300;
bool first = true;


///lighting global
glm::vec3 lightColor  = glm::vec3(1.0f,0.20f,0.70f);
glm::vec3 objectColor    = glm::vec3(0.20f,0.4f,0.6f);
glm::vec3 lightPosition = glm::vec3(1.2f, 1.0f, 2.0f);


void keyboardEvents(GLFWwindow* window){
float speed = 0.25f;
if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
   cameraPos -= speed * cameraFront;
}
if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
   cameraPos += speed * cameraFront;
}
}


void setCursorCallback(GLFWwindow* window, double xpos, double ypos){

float sensitivity = 2.5;
float xoffset, yoffset;

if(first){
    lastx = xpos;
    lasty = ypos;
first = false;
}
xoffset = xpos - lastx;
yoffset = lasty - ypos ;
lastx = xpos;
lasty = ypos;


xoffset *= sensitivity;
yoffset *= sensitivity;

yaw += xoffset;
pitch += yoffset;

glm::vec3 direction;
direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
direction.y = glm::sin(glm::radians(pitch));
direction.z = glm::sin(glm::radians(yaw)) * glm::sin(glm::radians(pitch));

float camx = radius * direction.x;
float camy = radius * direction.y;
float camz = radius * direction.z;


cameraPos = target + glm::vec3(camx, camy, camz);

cameraFront = glm::normalize(target - cameraPos);

}

GLuint textureLoad(const char* path_texture){
stbi_set_flip_vertically_on_load(true);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path_texture, &width, &height, &nrChannels, 0);
    

    if(data){
        GLenum format ;
        if(nrChannels == 4){
        format = GL_RGBA;
        }
        else{
            format = GL_RGB;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    }else{
        std::cout<<"Failed to load the texture in path :: ===> "<<path_texture<<std::endl;
    }

    stbi_image_free(data);
    return texture;
}

template<typename T>
void uniformMat(GLuint program, const char* name, T value){
       glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, glm::value_ptr(value));
}

void uniformAll(GLuint program, const char* name, int value){
 glUniform1i(glGetUniformLocation(program, name), value);
   
}
void uniformAll(GLuint program, const char* name, glm::vec3 value){
 glUniform3fv(glGetUniformLocation(program, name), 1, glm::value_ptr(value));
}

GLuint setUp(float *vertices, const char * vertexShaderSource, const char* fragmentShaderSource, std::string mesh, size_t vertexCount, int _index){

GLuint  program, vertexShader, fragmentShader;
glGenVertexArrays(1, &VAO[_index]);
glBindVertexArray(VAO[_index]);
glGenBuffers(1, &VBO[_index]);
glBindBuffer(GL_ARRAY_BUFFER, VBO[_index]);
glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float) , (void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float) , (void*)(3*sizeof(float)));
glEnableVertexAttribArray(1);
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float) , (void*)(6*sizeof(float)));
glEnableVertexAttribArray(2);



vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource( vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);

fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);

program = glCreateProgram();
glAttachShader(program, vertexShader);
glAttachShader(program, fragmentShader);
glLinkProgram(program);

int success;
char infoLog[520];

glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if(!success){
glGetShaderInfoLog(vertexShader, 520, NULL, infoLog);
std::cout<<"failed to compile vertex shader :: "<<mesh<<" :: :: "<<infoLog<<std::endl;
}
glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
if(!success){
glGetShaderInfoLog(fragmentShader, 520, NULL, infoLog);
std::cout<<"failed to compile fragment shader :: "<<mesh<<" :: :: "<<infoLog<<std::endl;
}
glGetProgramiv(program, GL_LINK_STATUS, &success);
if(!success){
glGetProgramInfoLog(program, 520, NULL, infoLog);
std::cout<<"failed to link program :: "<<mesh<<" :: :: "<<infoLog<<std::endl;
}


return program;

}
GLuint cube(){


float cubeVertices[] = {
    // --- Front face (+Z) ---
    2.0f, 3.0f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    3.0f, 3.0f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    3.0f, 4.0f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    
    2.0f, 3.0f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    3.0f, 4.0f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    2.0f, 4.0f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

    // --- Back face (-Z) ---
    3.0f, 3.0f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
    2.0f, 3.0f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
    2.0f, 4.0f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,

    3.0f, 3.0f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
    2.0f, 4.0f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
    3.0f, 4.0f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,

    // --- Left face (-X) ---
    2.0f, 3.0f, -0.5f,  -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    2.0f, 3.0f,  0.5f,  -1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    2.0f, 4.0f,  0.5f,  -1.0f, 0.0f, 0.0f,   1.0f, 1.0f,

    2.0f, 3.0f, -0.5f,  -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    2.0f, 4.0f,  0.5f,  -1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    2.0f, 4.0f, -0.5f,  -1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

    // --- Right face (+X) ---
    3.0f, 3.0f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    3.0f, 3.0f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    3.0f, 4.0f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,

    3.0f, 3.0f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    3.0f, 4.0f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    3.0f, 4.0f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

    // --- Top face (+Y) ---
    2.0f, 4.0f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
    3.0f, 4.0f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    3.0f, 4.0f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

    2.0f, 4.0f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
    3.0f, 4.0f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    2.0f, 4.0f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

    // --- Bottom face (-Y) ---
    2.0f, 3.0f, -0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,
    3.0f, 3.0f, -0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 0.0f,
    3.0f, 3.0f,  0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f,

    2.0f, 3.0f, -0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,
    3.0f, 3.0f,  0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f,
    2.0f, 3.0f,  0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 1.0f
};


std::ifstream v_file;
std::ifstream f_file;
std::string v_code;
std::string f_code;


v_file.exceptions(std::ios::badbit | std::ios::failbit);
f_file.exceptions(std::ios::badbit | std::ios::failbit);

try{
std::stringstream v_stream;
std::stringstream f_stream;

v_file.open("../src/v_file_cube.glsl");
f_file.open("../src/f_file_cube.glsl");

v_stream << v_file.rdbuf();
f_stream << f_file.rdbuf();

v_file.close();
f_file.close();

v_code = v_stream.str();
f_code = f_stream.str();

}catch(const std::exception &e){
std::cout<<"failed to load file from... :: "<<e.what()<<std::endl;
}

const char* cube_vertexShaderSource = v_code.c_str();
const char* cube_fragmentShaderSource =  f_code.c_str();


cube_program = setUp(cubeVertices, cube_vertexShaderSource, cube_fragmentShaderSource, "cube", sizeof(cubeVertices)/sizeof(float), 1);
return cube_program; 
}
GLuint pyramid(){
    float pyramidVertices[] = {
    // --- Base (Y = 0), normal pointing down (0, -1, 0) ---

    // Triangle 1
    -1.0f, 0.0f, -1.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,  // v0
     1.0f, 0.0f, -1.0f,   0.0f, -1.0f, 0.0f,   1.0f, 0.0f,  // v1
     1.0f, 0.0f,  1.0f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f,  // v2

    // Triangle 2
    -1.0f, 0.0f, -1.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,  // v0
     1.0f, 0.0f,  1.0f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f,  // v2
    -1.0f, 0.0f,  1.0f,   0.0f, -1.0f, 0.0f,   0.0f, 1.0f,  // v3

    // --- Side 1 (Front) ---
    -1.0f, 0.0f, -1.0f,  -0.707f, 0.5f, -0.5f,   0.0f, 0.0f,  // base left
     0.0f, 2.0f,  0.0f,  -0.707f, 0.5f, -0.5f,   0.5f, 1.0f,  // tip
     1.0f, 0.0f, -1.0f,   0.707f, 0.5f, -0.5f,   1.0f, 0.0f,  // base right

    // --- Side 2 (Right) ---
     1.0f, 0.0f, -1.0f,   0.707f, 0.5f, -0.5f,   0.0f, 0.0f,
     0.0f, 2.0f,  0.0f,   0.707f, 0.5f,  0.5f,   0.5f, 1.0f,
     1.0f, 0.0f,  1.0f,   0.707f, 0.5f,  0.5f,   1.0f, 0.0f,

    // --- Side 3 (Back) ---
     1.0f, 0.0f,  1.0f,   0.707f, 0.5f, 0.5f,    0.0f, 0.0f,
     0.0f, 2.0f,  0.0f,   0.0f,   0.5f, 1.0f,    0.5f, 1.0f,
    -1.0f, 0.0f,  1.0f,  -0.707f, 0.5f, 0.5f,    1.0f, 0.0f,

    // --- Side 4 (Left) ---
    -1.0f, 0.0f,  1.0f,  -0.707f, 0.5f, 0.5f,    0.0f, 0.0f,
     0.0f, 2.0f,  0.0f,  -0.707f, 0.5f, -0.5f,   0.5f, 1.0f,
    -1.0f, 0.0f, -1.0f,  -0.707f, 0.5f, -0.5f,   1.0f, 0.0f,
};
std::ifstream v_file;
std::ifstream f_file;
std::string v_code;
std::string f_code;


v_file.exceptions(std::ios::badbit | std::ios::failbit);
f_file.exceptions(std::ios::badbit | std::ios::failbit);

try{
std::stringstream v_stream;
std::stringstream f_stream;

v_file.open("../src/v_file_py.glsl");
f_file.open("../src/f_file_py.glsl");

v_stream << v_file.rdbuf();
f_stream << f_file.rdbuf();

v_file.close();
f_file.close();

v_code = v_stream.str();
f_code = f_stream.str();

}catch(const std::exception &e){
std::cout<<"failed to load file from... :: "<<e.what()<<std::endl;
}

const char* pyramid_vertexShaderSource = v_code.c_str();
const char* pyramid_fragmentShaderSource =  f_code.c_str();

pyramid_program = setUp(pyramidVertices, pyramid_vertexShaderSource, pyramid_fragmentShaderSource, "pyramid", sizeof(pyramidVertices)/sizeof(float), 2);
return pyramid_program; 

}


void size_callback(GLFWwindow* window, int width, int height){
glViewport( 0, 0, width, height);

glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width)/static_cast<float>(height), 0.1f, 100.0f);
calcProjection = projection;
}

int main(){

     glfwInit();
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

     GLFWwindow* window = glfwCreateWindow( 800, 600, "light", NULL, NULL);
     if(!window){
        std::cerr<<"failed to create window"<<std::endl;
     }
     glfwMakeContextCurrent(window);

     if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
    std::cerr<<"Failed to iitialize glad..."<<std::endl;
    }
 glViewport(0,0, 800, 600);

 glfwSetInputMode(window, GLFW_CURSOR ,GLFW_CURSOR_DISABLED );
 glfwSetFramebufferSizeCallback(window, size_callback);
 glfwSetCursorPosCallback(window, setCursorCallback);


glEnable(GL_DEPTH_TEST);

GLuint program_1 = cube();
//GLuint cube_texture = textureLoad("../assets/textures/ai.jpg");

GLuint program_2 = pyramid();
GLuint pyramid_texture = textureLoad("../assets/textures/2024-11-02.png");

bool first_1 = true;
double time = double() ;
while(!glfwWindowShouldClose(window)){
time = glfwGetTime();

glClearColor( 0.0f, 0.00f, 0.0f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
if(first_1){//flag to allow initializing the object 
    calcProjection = glm::perspective(glm::radians(45.0f), 1.0f/1.0f, 0.1f, 100.0f);
    first_1 = false;
}

//cube
glUseProgram(program_1);
glBindVertexArray(VAO[1]);
uniformMat<glm::mat4>(cube_program, "lightPosition", glm::translate(glm::mat4(1.0f), lightPosition));
uniformMat<glm::mat4>(cube_program, "model", glm::scale(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,0.5f)));
uniformMat<glm::mat4>(cube_program, "rot",  glm::rotate(glm::mat4(1.0f), static_cast<float>(time) * glm::radians(-45.0f),glm::vec3(0.0f,1.0f,0.0f)));
uniformMat<glm::mat4>(cube_program, "view", glm::lookAt(cameraPos, target, cameraUp));
uniformMat<glm::mat4>(cube_program, "projection", calcProjection);
uniformAll(cube_program, "lightColor", lightColor);


//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_2D, cube_texture);
//uniformAll(cube_program, "text", 0);

glDrawArrays(GL_TRIANGLES, 0, 36);
//pyramid


glUseProgram(program_2);
glBindVertexArray(VAO[2]);

uniformMat<glm::mat4>(pyramid_program, "model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f)));
uniformMat<glm::mat4>(pyramid_program, "rot", glm::rotate(glm::mat4(1.0f), static_cast<float>(time) * glm::radians(45.0f),glm::vec3(0.0f,1.0f,0.0f)));
uniformMat<glm::mat4>(pyramid_program, "view", glm::lookAt(cameraPos, target, cameraUp));
uniformMat<glm::mat4>(pyramid_program, "projection", calcProjection);
uniformAll(pyramid_program, "lightColor", lightColor);
uniformAll(pyramid_program, "objectColor", objectColor);
uniformAll(pyramid_program, "viewerPos", cameraPos);

uniformMat<glm::mat4>(pyramid_program, "lightRot", glm::rotate(glm::mat4(1.0f), static_cast<float>(time) * glm::radians(-45.0f),glm::vec3(0.0f,1.0f,0.0f)));
uniformAll(pyramid_program, "finalLightPos", lightPosition);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, pyramid_texture);
uniformAll(pyramid_program, "text", 0);


glDrawArrays(GL_TRIANGLES, 0, 18);


keyboardEvents(window);
glfwSwapBuffers(window);
glfwPollEvents();
}
     glDeleteVertexArrays(1, &VAO[1]);
     glDeleteBuffers(1, &VBO[1]);
     glDeleteVertexArrays(1, &VAO[2]);
     glDeleteBuffers(1, &VBO[2]);
     glDeleteProgram(cube_program);
     glDeleteProgram(pyramid_program);
     glfwDestroyWindow(window);
     glfwTerminate();
    return 0;
}