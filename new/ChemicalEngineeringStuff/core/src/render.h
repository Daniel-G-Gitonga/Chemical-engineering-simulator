#pragma once

#include "pch.h"
#include <glad/glad.h>


namespace chem{
//mesh class
struct Vertex{
glm::vec3 vertices;
glm::vec3 normals;
glm::vec2 text_coords;
//size 8 + padding\\but negligible
};
struct Material{
    int id;
    std::string name;
};


class CHEM_ENG_ROSE Render{
    private:
GLuint program;
GLuint VAO;
GLuint VBO;
GLuint EBO;
GLuint fragmentShader;
GLuint vertexShader;
GLuint texture;


    public:
int width;
int height;


Render();
~Render();
std::vector<GLuint> setUp(std::string name,const char* vertex_shader_path, const char* fragment_shader_path, std::vector<Vertex> vertex, std::vector<unsigned int> indices_pass,  int indexCount/*number of indixes*/, int vertexCount/*number of vertices stored*/);
void initRenderer();
void useProgram(GLuint program);
void draw(GLuint program_draw, GLuint VAO_draw, int indexCount, int vertexCount);
//void loadTexture();
private:
void error_checker(std::string name, GLuint *vertexShader, GLuint *fragementShader, GLuint *program);

};

class Mesh: public Render{
public:
std::vector<unsigned int> indices;
std::vector<Vertex> vertex;
std::vector<Material> material;


GLuint VAO;
GLuint VBO;
GLuint EBO;
GLuint texture;
GLuint program_mesh;


Mesh();
~Mesh();

void setUp();
void renderMesh();//transparent mesh such as glass
void renderMesh_norm();//normal mesh
//constructor calls setUp destructor release everything else
};

class Model{

};
};