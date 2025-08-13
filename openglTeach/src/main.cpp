#include <iostream>



#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
   #include "stb_image.h"

const char* fragmentShaderSourceLight = R"(
#version 330 core
out vec4 FragColor;

in vec3 normals_o;

uniform vec3 lightColour;

void main(){
FragColor = vec4(lightColour , 1.0f);//vec4(1.0,1.0,1.0,1.0);
}
)";

const char* fragmentShaderSourcePyramid = R"(
#version 330 core
out vec4 FragColor;

in vec2 texture_coords;
in vec3 normals_o;

uniform vec3 lightColour;
uniform vec3 objColour;

uniform sampler2D text;
void main(){
FragColor = texture(text, texture_coords) * (lightColour),1.0f;// * vec4((objColour) * (lightColour),1.0f); //texture(text, texture_coords) ;//* vec4(1.0,1.0,0.0,1.0);
}
)";

const char* vertexShaderSourceLight = R"(
#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normals_o;

void main(){

normals_o = normals;
gl_Position =  projection * view * model * vec4(pos,1.0);
}
)";


const char* vertexShaderSourcePyramid = R"(
#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texture_coords;
out vec3 normals_o;

void main(){
texture_coords = textCoords;
normals_o = normals;
gl_Position = projection * view * model * vec4(pos,1.0);
}
)";


GLuint VAOl,VAOp,VBOp,VBOl;
glm::vec3 cameraPos = glm::vec3(0.0f,1.5f,5.0f);
glm::vec3 cameraLookForward = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 worldUp   = glm::vec3(0.0f,1.0f,0.0f);
float yaw   = -90.0f;   // initialize facing toward -Z
float pitch = 0.0f;

float lastX = 400, lastY = 300; // initial mouse position (window center)
bool firstMouse = true;

float deltaTime = 0.0f; // time between frames, update outside processInput
float lastFrame = 0.0f;

float mouseSensitivity = 0.1f;
float cameraSpeed = 2.5f; // adjust as needed


GLuint pyramid(){
    GLuint pyramidProgram, vertexShaderPyramid,fragmentShaderPyramid;


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


    

    glGenVertexArrays(1, &VAOp);
    glBindVertexArray(VAOp);
    glGenBuffers(1, &VBOp);
    glBindBuffer(GL_ARRAY_BUFFER, VBOp);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);

    vertexShaderPyramid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderPyramid,1, &vertexShaderSourcePyramid, NULL);
    glCompileShader(vertexShaderPyramid);

{
    GLint success;
    char infolog[512];
    glGetShaderiv(vertexShaderPyramid, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShaderPyramid,512, NULL, infolog);
        std::cout<<"FAILED TO COMPILE pyramid vertex ::"<<infolog<<std::endl;
    }
}
    
    fragmentShaderPyramid  =  glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderPyramid, 1, &fragmentShaderSourcePyramid, NULL);
    glCompileShader(fragmentShaderPyramid);

{
    GLint success;
    char infolog[512];
    glGetShaderiv(fragmentShaderPyramid, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShaderPyramid,512, NULL, infolog);
        std::cout<<"FAILED TO COMPILE pyramiid fragment "<<infolog<<std::endl;
    }
}
    pyramidProgram      = glCreateProgram();
    glAttachShader(pyramidProgram, vertexShaderPyramid);
    glAttachShader(pyramidProgram, fragmentShaderPyramid);
    glLinkProgram(pyramidProgram);
{
    GLint success;
    char infolog[512];
    glGetProgramiv(pyramidProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(pyramidProgram,512, NULL, infolog);
        std::cout<<"FAILED TO LINK pyramid program"<<infolog<<std::endl;
    }
}


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    
    glBindVertexArray(0);
    return pyramidProgram;
}
GLuint light(){
GLuint lightProgram, vertexShaderlight, fragmentShaderLight;
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

    
    glGenVertexArrays(1, &VAOl);
    glBindVertexArray(VAOl);
    glGenBuffers(1, &VBOl);
    glBindBuffer(GL_ARRAY_BUFFER, VBOl);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    vertexShaderlight = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderlight,1, &vertexShaderSourceLight, NULL);
    glCompileShader(vertexShaderlight);
    {
    GLint success;
    char infolog[512];
    glGetShaderiv(vertexShaderlight, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShaderlight,512, NULL, infolog);
        std::cout<<"FAILED TO COMPILE light vertex shader:: "<<infolog<<std::endl;
    }
}

    fragmentShaderLight  =  glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderLight, 1, &fragmentShaderSourceLight, NULL);
    glCompileShader(fragmentShaderLight);
    {
    GLint success;
    char infolog[512];
    glGetShaderiv(fragmentShaderLight, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShaderLight,512, NULL, infolog);
        std::cout<<"FAILED TO COMPILE light fragment shader:: "<<infolog<<std::endl;
    }
}
    
    lightProgram      = glCreateProgram();
    glAttachShader(lightProgram, vertexShaderlight);
    glAttachShader(lightProgram, fragmentShaderLight);
    glLinkProgram(lightProgram);
    {
    GLint success;
    char infolog[512];
    glGetProgramiv(lightProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(lightProgram,512, NULL, infolog);
        std::cout<<"FAILED TO LINK light program "<<infolog<<std::endl;
    }
}


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindVertexArray(0);

    return lightProgram;

}
void processInputs(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
  

    // Calculate deltaTime
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Keyboard input
    float velocity = cameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += velocity * cameraLookForward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= velocity * cameraLookForward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraLookForward, worldUp)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraLookForward, worldUp)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraLookForward, glm::normalize(glm::cross(cameraLookForward, worldUp)))) * velocity;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraLookForward, glm::normalize(glm::cross(cameraLookForward, worldUp)))) * velocity;
    // Mouse input - get current cursor position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (firstMouse) // this bool variable is initially true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    // constrain the pitch angle to prevent screen flip
    if(pitch > 89.0f)
        pitch = 190.0f;
    if(pitch < -89.0f)
        pitch = -190.0f;

    // update cameraFront vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraLookForward = glm::normalize(front);

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
glViewport(0,0,width,height);
}
void uniforms (GLuint program, const char* name){
    

     glm::mat4 model = glm::mat4(1.0f);
     model = glm::translate(model, glm::vec3(1.0));
     glm::mat4 view = glm::mat4(1.0f);
     view = glm::lookAt(cameraPos, cameraPos + cameraLookForward , worldUp);
     glm::mat4 projection = glm::mat4(1.0f);
     projection = glm::perspective(glm::radians(45.0f),800.0f/600.0f,0.1f,100.0f);
    // projection  = glm::ortho(0.0f,800.0f,0.0f,600.0f,0.1f,100.0f);

glm::mat4 holder = glm::mat4(1.0f);

     GLuint loc = glGetUniformLocation(program, name);
     if(name == "model"){
      holder = model;
     }else if(name == "view"){
      holder = view;
     }else if(name == "projection"){
      holder = projection;
     }
     glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(holder));

}
void setLight(GLuint program){
    glUseProgram(program);
    glUniform3f(glGetUniformLocation(program, "lightColour"),1.0f,1.0f,1.0f);
    uniforms(program,"model");
    uniforms(program,"view");
    uniforms(program,"projection");
glBindVertexArray(VAOl);
glDrawArrays(GL_TRIANGLES, 0, 36);
glBindVertexArray(0);

}
void setPyramid(GLuint program){
    glUseProgram(program);
    glUniform3f(glGetUniformLocation(program, "objColour"),0.50f,0.50f,0.0f);
    glUniform3f(glGetUniformLocation(program, "lightColour"),1.0f,1.0f,1.0f);
    glUniform1i(glGetUniformLocation(program, "text"), 0);
    uniforms(program,"model");
    uniforms(program,"view");
    uniforms(program,"projection");
glBindVertexArray(VAOp);
glDrawArrays(GL_TRIANGLES, 0, 18);
glBindVertexArray(0);

}
void load_texture(const char* path){

stbi_set_flip_vertically_on_load(true);


int width, height, nrChannels;
unsigned char* bytes = stbi_load(path, &width, &height, &nrChannels, 0);
if(bytes == NULL){
std::cout<<"FAILED TO LOAD THE IMAGE..."<<std::endl;
}
GLuint texture;
glGenTextures(1,&texture);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

GLenum format = GL_RGBA;
if(nrChannels == 3){
    format = GL_RGB;
}else if(nrChannels != 4 && nrChannels != 3){
     format = GL_RED ;
}

glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,bytes);

stbi_image_free(bytes);
}


int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
     GLFWwindow* window = glfwCreateWindow(800 , 600, "lighting", NULL, NULL);
     if(!window){
       std::cerr<<"failed to create the window..."<<std::endl;

     }
     glfwMakeContextCurrent(window);

     if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr<<"Faile to load glad..."<<std::endl;
     }
   

     glViewport(0,0,800,600);
     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
     GLFW_CURSOR_DISABLED;
     /////
GLuint pyramidProgram = pyramid();
GLuint lightProgram   = light();
     ///
      load_texture("../assets/textures/ai.jpg");
      
     glEnable(GL_DEPTH_TEST);

     while (!glfwWindowShouldClose(window))
     {



        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1,0.01,0.011,1.0);

//
setLight(lightProgram);
setPyramid(pyramidProgram);

//
        processInputs(window);
        glfwPollEvents();
        glfwSwapBuffers(window);

     }
        

    glDeleteBuffers(1, &VBOl);
    glDeleteBuffers(1, &VBOp);
    glDeleteVertexArrays(1, &VAOl);
    glDeleteVertexArrays(1, &VAOp);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}