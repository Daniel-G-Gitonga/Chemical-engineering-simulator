#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "pch.h"
#include "win.h"
#include "render.h"
#include "key.h"
#include "camera.h"

bool first_resize = true;//
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);


namespace chem{
    class CHEM_ENG_ROSE App:public Window{
        private:
chem::Render*  main_r = new Render();
float delta_time = 0;
float current_frame_time = 0;
float last_frame_time = 0;


int key;
ROSES_EYE::Debug_cam* cam_1 = new ROSES_EYE::Debug_cam();//camera


std::vector<std::string> paths;
std::vector<glm::vec3> positions;
std::vector<std::string> id;

std::vector<Model> loaded_model;//vector to store the loaded models for later draw calls


        public:


void setup();                     //setUp glfw and init window creation
bool is_window_ready = false;
glm::mat4 model = glm::mat4(1.0f);///model per The obj that to extract mesh from, basically posittions initial, but may change on adding phyc
                                  ///also transformations like scale

GLFWwindow* mini_win;
float timer ;
void mini_window(int width, int height, std::string title, bool share_context_with_main_win );
void run();
void set_model_array(std::vector<std::string> path_specified, std::vector<glm::vec3> pos_specified, std::vector<std::string> id_o_model);
App(std::string title_a, float width_a, float height_a);
~App();

    };
}