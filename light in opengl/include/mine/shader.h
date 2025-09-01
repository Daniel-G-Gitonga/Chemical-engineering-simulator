#pragma once
/*
load shader from glsl(main_prog is passed a prog dulling linking.. so each obj has its own obj)
compile
link to prog
allow error checking
support uniforms

///
drawing...
creat buffers,
pass to opengl
compile shader
*/
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace rose{

class Shader{
private:
GLuint main_program;
GLuint fragment_shader;
GLuint vertex_shader;

std::fstream fragment_file;
std::fstream vertex_file;


std::stringstream v_stream;
std::stringstream f_stream;

std::string vertex_code;
std::string fragment_code;

const char* vertex_shader_src;
const char* fragment_shader_src;


int success;
char infoLog[216];

public:
Shader();
void loadShader(std::string path_fragment_shader, std::string path_vertex_shader);
void compileShader();
void linkShaders();
void checkError();
void setUp(GLuint prog);
//method overrloading for uniforms...
void uniforms(int i,  const char* name);//only data the location can be obtained using the program of obj passed to main prog
void uniforms(glm::mat4,  const char* name);
void uniforms(glm::vec3 a,  const char* name);
void uniforms(glm::vec4 a,  const char* name);
void useProgram();
~Shader();
};

}