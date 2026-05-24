#include "app.h"
#include "model.h"

App::App(){
    
}

void App::createWindow(int width, int height){
glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_SAMPLES, 4);

GLFWwindow* window = glfwCreateWindow(width, height, "assimp", NULL, NULL);
this->window = window;
glfwMakeContextCurrent(window);

glfwGetWindowSize(window , &width_w, &height_w);
}

App::~App(){
    

    
    glfwDestroyWindow(window);
    glfwTerminate();
}



void App::run(){

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window,[](GLFWwindow* win , int width, int height){
        App *app = static_cast<App*>(glfwGetWindowUserPointer(win));
        glViewport(0, 0, width, height);
    });

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("failed to initialise glad.");
    }
    glViewport(0, 0, width_w, height_w );

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    
    Shader *shader = new Shader("../Assets/shader/vertex_shader.glsl", "../Assets/shader/fragment_shader.glsl");
    Model *model = new Model("../Assets/model/cube.gltf");

    Shader* shader2 = new Shader("../Assets/shader/vertex_shader.glsl", "../Assets/shader/fragment_shader.glsl");
    Model *model2 = new Model("../Assets/model/untitled.gltf");

    while(!glfwWindowShouldClose(window)){
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//OPAQUE
    shader2->useProgram();
    shader2->uniform("model",glm::rotate(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)), glm::vec3(0.5f)), glm::radians(45.0f) * static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f)));
    model2->draw(*shader2);

//transparent
    glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader->useProgram();
    shader->uniform("model",glm::rotate(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)), glm::vec3(1.5f)), glm::radians(-45.0f) * static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f)));
    model->draw(*shader);
    glDisable(GL_BLEND);


        glfwPollEvents();
        glfwSwapBuffers(window);

    }

    model2->clean();
    shader2->clean();
    delete model2;
    delete shader2;
    model->clean();
    shader->clean();
    delete model;
    delete shader;
 
}