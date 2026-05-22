#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
protected:
GLuint VBO = GLuint(), VAO = GLuint(), IBO = GLuint(), texture = GLuint(), texture_2 = GLuint();
GLuint vertex_shader = GLuint();
GLuint fragment_shader = GLuint();
GLuint program = GLuint();

std::string vertex_code = std::string();
std::string fragment_code = std::string();;

const char* vertex_source = nullptr;
const char* fragment_source = nullptr;

void loadShader(std::string path_vertex, std::string path_fragment);

GLuint text = GLuint();//text = texture
GLuint loadTexture(std::string path_texture, int i);

void compileShader(std::vector<float> vertices, std::vector<unsigned int> indices);
void drawObj(int num);

void uniform(std::string name, int i);
void uniform(std::string name, glm::mat4 mat4);
void uniform(std::string name, glm::vec4 vec4);
void uniform(std::string name, glm::vec3 vec3);

private:
void check_errors();
};