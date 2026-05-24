#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class App {
private:
public:
int width_w = int();
int height_w = int();
App();
GLFWwindow* window = nullptr;
void createWindow(int width, int height);
void run();

~App();
};