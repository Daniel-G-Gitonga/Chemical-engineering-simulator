#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <sstream>
#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Texture{
GLuint id                = GLuint();
std::string texture_type = std::string();
std::string path         = std::string();
};

struct Vertex{
glm::vec3 vertices;
glm::vec3 normals;
glm::vec2 texture_coords;
};

class Shader{
public:
Shader(std::string p_vertex, std::string p_fragment);

GLuint program           = GLuint();
GLuint vertex_shader     = GLuint();
GLuint fragment_shader   = GLuint();

std::string fragment_shader_path = std::string();
std::string vertex_shader_path   = std::string();
std::string vertex_code   = std::string();
std::string fragment_code = std::string();


const char* vertex_shader_source   = nullptr;
const char* fragment_shader_source = nullptr;

void loadShader();
void useProgram();
void uniform(std::string name, int i);
void uniform(std::string name, glm::mat4 matrix4);

void checkError();
void clean();

void draw(Shader &shader);
};

class Mesh{
public:

Mesh(std::vector<Vertex> &vertex, std::vector<unsigned int> &indices, std::vector<Texture> &texture);
std::vector<Vertex>           vertex ;//vertices normal texturecoordinates
std::vector<Texture>          texture;
std::vector<unsigned int>     indices;  

GLuint VAO  = GLuint();
GLuint VBO  = GLuint();
GLuint IBO  = GLuint();

void setUp();
void draw(Shader & shader);
void clean();
};


class Model{
public:
Model(std::string model_p);


std::string model_path              = std::string();
std::string model_texture_directory = std::string();

GLuint texture = GLuint();

std::vector<Mesh>    meshes;

GLuint loadTexture(std::string texture_location, std::string texture_directory);
std::vector<Texture> loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string name);

void loadModel();
void processNode(aiNode* node, const aiScene* scene);
Mesh processMesh(aiMesh* mesh, const aiScene* scene);
void clean();

void draw(Shader &shader);

};