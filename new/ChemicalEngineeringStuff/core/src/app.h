#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "pch.h"
#include "win.h"
#include "render.h"

namespace chem{
    class CHEM_ENG_ROSE App:public Window{
        private:
void setup();
        public:

bool is_window_ready = false;

void run();

App(std::string title_a, float width_a, float height_a);
~App();
    };
}