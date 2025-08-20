#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
   #include "stb_image.h"

//#include "shader.h"

float yaw = -90.0f;
float pitch = 0.0f;
float lastx = 400.0f, lasty = 300.0f;
bool first_mouse =  true;
float fov = 45.0f;

glm::vec3 camPos    = glm::vec3(-2.0f,0.0f,3.0f);
glm::vec3 camFront  = glm::vec3(2.0f,0.0f,-1.0f);
glm::vec3 camUp     = glm::vec3(0.0f,0.0f,1.0f);

float tri_vertices[] = {
    -1.0f,-1.0f,0.0f,
     0.0f,-1.0f,0.0f,
     0.0f,1.0f,0.0f
    };
float cube_vertices[] = {
  
    // positions           // texture coords

    // Front face
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,

    // Back face
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,

    // Left face
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

    // Right face
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f,

    // Bottom face
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,

    // Top face
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f
};


class Shader{
private:
    GLuint prog;
public:
GLuint VBO,vertexShader,fragmentShader, VAO;
GLuint index ;

 
void error(GLuint program,const char* name_p, GLuint fragmentShader,const char* name_f, GLuint vertexShader,const char* name_v){

int success ;
char infoLog[512];

glGetShaderiv(fragmentShader,GL_COMPILE_STATUS, &success);
if(!success){
    glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
    std::cerr<<"Failed to compile fragmentShader for"<<name_f<<" in::"<<infoLog<<std::endl;
}

glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if(!success){
     glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
     std::cerr<<"failed to compile veetexShader for"<<name_v<<" in::"<<infoLog<<std::endl;
}

glGetProgramiv(program,GL_LINK_STATUS, &success);
if(!success){
     glGetProgramInfoLog(program,512,NULL,infoLog);
     std::cerr<<"Failed to link the program for "<<name_p<<" in::"<<infoLog<<std::endl;
}


}

GLuint setUp(const char* name_prog, int size_to,float vertices[],const char* path_vertex, const char* path_fragment){
   std::string vertexCode;
   std::string fragmentCode;

   std::ifstream vShaderFile;
   std::ifstream fShaderFile;

   std::stringstream vShaderStream;
   std::stringstream fShaderStream;

   vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
   fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
   try
   {
      vShaderFile.open(path_vertex);
      fShaderFile.open(path_fragment);

      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();

      vShaderFile.close();
      fShaderFile.close();   

      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();

   }
   catch(std::ifstream::failure& e)
   {
    std::cerr<<"FILE NOT SUCCESSFULLY READ  "<< e.what()<<std::endl;
   }
   
    const char* fragmentShaderSource = fragmentCode.c_str();
    const char* vertexShaderSource   = vertexCode.c_str();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(&vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, size_to * sizeof(float), vertices, GL_STATIC_DRAW); 

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    prog = glCreateProgram();
    glAttachShader(prog, vertexShader);
    glAttachShader(prog, fragmentShader);
    glLinkProgram(prog);
    
     error(prog,name_prog,fragmentShader,name_prog,vertexShader,name_prog);

     return prog;
  }

  void uniform( const char* uniformName, GLuint program, glm::vec4 value){
    index = glGetUniformLocation(program, uniformName);
    glUniform4fv(index, 1,glm::value_ptr(value));
  }
  void uniform(const char* uniformName, GLuint program, glm::mat4 value){
    index = glGetUniformLocation(program, uniformName);
    glUniformMatrix4fv(index, 1, GL_FALSE ,glm::value_ptr(value));
  }
  void uniform(const char* uniformName, GLuint program, GLenum i){
   int indices = 0;

   index = glGetUniformLocation(program, uniformName);
   glUniform1i(index, indices);
  }

void clean(){
glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(prog);
}
~Shader(){
    
    clean();
}

};
class Texture : public Shader{
public:
GLuint texture, program;
const char* path ;
const char* uniformName;
GLenum text_unit;


Texture(const char* path_c, const char* uniformName_c, GLenum text_unit_c){
path = path_c;
uniformName = uniformName_c;
text_unit   = text_unit_c;


}

void textureUse(GLuint program){
stbi_set_flip_vertically_on_load(true);

int width, height, nrChannels;
unsigned char* byte = stbi_load(path, &width, &height, &nrChannels, 0);


glActiveTexture(text_unit);

glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


if(byte){

GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB ;
glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, byte);

uniform(uniformName , program, text_unit);
}else{std::cout<<"failed to load the texture..."<< path <<std::endl;}
stbi_image_free(byte);


}

~Texture(){
glDeleteTextures(1, &texture);
}
};
class Triangle : public Texture{

  public:

  GLuint tri_program;
  Triangle(const char* path, const char* uniformtexture, GLenum t_u) : Texture(path, uniformtexture, t_u) {

    float *vv = tri_vertices;
    
    tri_program = setUp("triangle_program...",9, tri_vertices,"../src/vst.glsl","../src/fst.glsl");

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)(0));
    glBindVertexArray(0);    
  }

};
class Cube : public Texture{
public:
float *cc = cube_vertices;
GLuint cube_program ;
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;


Cube(const char* path, const char* uniformtexture, GLenum t_u) : Texture(path, uniformtexture, t_u) {

/*
nothing to see here just passing arguments from one constructor to another( from Cube class to texture class....)
*/

cube_program= setUp("cube",180,cube_vertices,"../src/vsc.glsl","../src/fsc.glsl");

glEnableVertexAttribArray(0);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(0));

glEnableVertexAttribArray(1);
glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
glBindVertexArray(0);


}


void cubeUniform(glm::mat4 pos, glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec4 color){
    uniform("ccolor"    , cube_program,                            color);
    uniform("model_pos"     , cube_program,                           pos);
    uniform("model"     , cube_program,                           model);
    uniform("view"      , cube_program,                            view);
    uniform("projection", cube_program,                      projection);
   }

};
class Events{
    public:
GLFWwindow* win;
Events(GLFWwindow* window){
    win = window;
}
void ev(){

    const float camSpeed = 0.21115f;

    if(glfwGetKey(win,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(win, true);        
    }

    if(glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
    {//camPos == camFront
        camPos += glm::normalize(glm::cross(camUp, camFront)) * camSpeed;
    }
    if(glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
    {
        camPos += glm::normalize(glm::cross(glm::cross(camUp, camFront),camFront)) * camSpeed;
    }
    if(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
    {//camPos == camFront
        camPos -= glm::normalize(glm::cross(camUp,camFront)) * camSpeed;
    }
    if(glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        camPos -= glm::normalize(glm::cross(glm::cross(camUp, camFront),camFront)) * camSpeed;
    }
    if(glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
    {
        camPos += camFront * camSpeed;
    }
    if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
    {
        camPos -= camFront * camSpeed;
    }
    
    
}

};
class Main{
public: static void framebuffer_size_call(GLFWwindow* window, int width, int height){
glViewport(0,0,width,height);
}

public: static void mouse_callback(GLFWwindow* window, double xpos, double ypos){
 static float sensitivity = 0.1f;

 if(first_mouse){
    lastx = xpos;
    lasty = ypos;
    first_mouse = false;

 }

 float xoffset = xpos - lastx;
 float yoffset = lasty - ypos;
 lastx = xpos;
 lasty = ypos;

 xoffset *= sensitivity;
 yoffset *= sensitivity;

 yaw   += xoffset;
 pitch += yoffset;

 if(pitch > 89.0f){
    pitch = 89.0f;

 }
 if(pitch < -89.0f){
    pitch = -89.0f;
 }

 glm::vec3 front;
 front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
 front.y = sin(glm::radians(pitch));
 front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
 camFront = glm::normalize(front);

}

public: static void scroll_callback(GLFWwindow*, double xoffset, double yoffset){
fov -= (float)yoffset;
if(fov < 1.0f) fov = 1.0f;
if(fov > 45.0f) fov = 45.0f;
}

public: static void main(){

glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

GLFWwindow* window = glfwCreateWindow(800,600,".>Mary_Ann<.",NULL,NULL);
if(window == NULL){
std::cout<<"failed to create the window...."<<std::endl;
}
glfwMakeContextCurrent(window);


Events* evs = new Events(window);

if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
std::cout<<"Failed to load the f'ing glad..."<<std::endl;
}
glViewport(0,0,800,600);

glfwSetCursorPosCallback(window, mouse_callback);
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
glfwSetScrollCallback(window, scroll_callback);
glfwSetFramebufferSizeCallback(window, framebuffer_size_call);

glEnable(GL_DEPTH_TEST);

Triangle* tr_1 = new Triangle("../assets/textures/ai88.png","triTexture", GL_TEXTURE0);
Cube* cub_1    = new Cube("../assets/textures/2024-11-02.png","ourTexture", GL_TEXTURE0);
Cube* cub_2    = new Cube("../assets/textures/ai.jpg","ourTexture", GL_TEXTURE0);
Cube* cub_3    = new Cube("../assets/textures/2024-11-02.png","ourTexture", GL_TEXTURE0);
Cube* cub_4    = new Cube("../assets/textures/2024-11-02.png","ourTexture", GL_TEXTURE0);

bool firstLoad_1 = true, firstLoad_2 = true, firstLoad_3 = true ;

while(!glfwWindowShouldClose(window)){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.0,0.0,0.0,1.0);


evs->ev();
/*
glUseProgram(tr_1->tri_program);
glBindVertexArray(tr_1->VAO);
glDrawArrays(GL_TRIANGLES,0,3);
*/





glUseProgram(cub_1->cube_program);
if(firstLoad_1){
    cub_1-> textureUse(cub_1->cube_program);
    firstLoad_1 = false;
}
glBindTexture(GL_TEXTURE_2D, cub_1->texture);
cub_1->cubeUniform(
     glm::translate(glm::mat4(1.0f),
     glm::vec3(0.0f,0.5f,2.0f)
     ),

     glm::rotate(glm::mat4(1.0f),
     (float)glfwGetTime() * glm::radians(45.0f),
     glm::vec3(1.0f,1.0f,0.0f)),

     glm::lookAt(
     camPos,
     camPos + camFront ,
     glm::vec3(0.0f,0.0f,1.0f)),

     glm::perspective(
     glm::radians(fov),
     800.0f/600.0f,
     0.1f,100.0f
     ),

     glm::vec4(0.1f,1.0f,0.6f,1.0f)
);
glBindVertexArray(cub_2->VAO);
glDrawArrays(GL_TRIANGLES,0,36);



glUseProgram(cub_2->cube_program);
if(firstLoad_2){
    cub_2-> textureUse(cub_2->cube_program);
    firstLoad_2 = false;
}
glBindTexture(GL_TEXTURE_2D, cub_2->texture);
cub_2->cubeUniform(
     glm::translate(glm::mat4(1.0f),
     glm::vec3(1.0f,0.5f,2.0f)
     ),

     glm::rotate(glm::mat4(1.0f),
     (float)glfwGetTime() * glm::radians(45.0f),
     glm::vec3(1.0f,0.0f,1.0f)),

     glm::lookAt(
     camPos,
     camPos + camFront ,
     glm::vec3(0.0f,0.0f,1.0f)),

     glm::perspective(
     glm::radians(fov),
     800.0f/600.0f,
     0.1f,100.0f
     ),

     glm::vec4(0.2f,0.8f,0.43f,1.0f)
);
glBindVertexArray(cub_3->VAO);
glDrawArrays(GL_TRIANGLES,0,36);


glUseProgram(cub_3->cube_program);
if(firstLoad_3){
    cub_3-> textureUse(cub_3->cube_program);
    firstLoad_3 = false;
}
glBindTexture(GL_TEXTURE_2D, cub_3->texture);
cub_3->cubeUniform(
    glm::translate(glm::mat4(1.0f),
    glm::vec3(3.0f,0.5f,2.0f)
    ),

     glm::rotate(glm::mat4(1.0f),
     (float)glfwGetTime() * glm::radians(45.0f),
     glm::vec3(0.0f,1.0f,1.0f)),

     glm::lookAt(
     camPos,
     camPos + camFront ,
     glm::vec3(0.0f,0.0f,1.0f)),

     glm::perspective(
     glm::radians(fov),
     800.0f/600.0f,
     0.1f,100.0f
     ),

     glm::vec4(1.0f,0.7f,0.2f,1.0f)
);
glBindVertexArray(cub_3->VAO);
glDrawArrays(GL_TRIANGLES,0,36);

glfwSwapBuffers(window);
glfwPollEvents();
}

cub_3->clean();
delete cub_3;
cub_3->clean();
delete cub_3;
cub_2->clean();
delete cub_2;
cub_1->clean();
delete cub_1;
tr_1->clean();
delete tr_1;
delete evs;

glfwDestroyWindow(window);
glfwTerminate();
}
};

int main(int argc, char** argv){
    Main::main();
return 0;
}
