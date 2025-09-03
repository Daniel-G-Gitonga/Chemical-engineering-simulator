#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>

#include "mine/events/events.h"

namespace rose{

class Window : public Events , public CameraF_Evs{
public:
Window();
GLFWwindow* window;
void createWin(int width, int height, std::string win);
bool closeWin();
void destroyWin();
~Window();

private:
};
}