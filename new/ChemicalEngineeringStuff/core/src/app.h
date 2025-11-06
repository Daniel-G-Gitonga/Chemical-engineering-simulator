#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "pch.h"
#include "win.h"
#include "render.h"
#include "key.h"
#include "camera.h"


namespace chem{
    class CHEM_ENG_ROSE App:public Window{
        private:

void setup();
std::vector<std::string> paths;
std::vector<glm::vec3> positions;
        public:

bool is_window_ready = false;

void run();
void set_model_array(std::vector<std::string> path_specified, std::vector<glm::vec3> pos_specified);
App(std::string title_a, float width_a, float height_a);
~App();
    };
}