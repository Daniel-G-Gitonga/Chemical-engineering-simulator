
#pragma once

#include <GLFW/glfw3.h>
#include "pch.h"


namespace chem{

void mess(std::string message);

class CHEM_ENG_ROSE Window{

protected:
Window(std::string title_a, float width_a, float height_a);
~Window();

public:
std::string title = "";
float width = 0;
float height = 0;

GLFWwindow* window_g;
bool createWindow();
void destroyWindow();

};

};