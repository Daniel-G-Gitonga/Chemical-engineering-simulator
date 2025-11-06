#pragma once

#include "pch.h"
#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace chem{
//mesh class
struct Vertex{
glm::vec3 position;
glm::vec3 normals;
glm::vec2 text_coords;
//size 8 + padding\\but negligible
};
struct Texture{
    unsigned int id;
    std::string path;
    std::string name;
};
struct Material{

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
private:
void error_checker(std::string name, GLuint *vertexShader, GLuint *fragementShader, GLuint *program);

};

class Mesh: public Render{
public:
std::vector<unsigned int> indices;
std::vector<Vertex> vertex;
std::vector<Texture> textures;


GLuint VAO;
GLuint VBO;
GLuint EBO;
GLuint texture;
GLuint program_mesh;


Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
~Mesh();

void use_program_for_mesh();
void setUp();
void renderMesh();
void uniforms(std::string name, int i);//specifically for tetxture loading
//__in model__
//; setUp in constructor
//;before render call use_program_for_mesh() for binding texture and vao
//;call uniforms after use_program_for_mesh()
//;load-texture() will be called off
};

class Model{
public:
Model(std::string path);
~Model();

void load_model();
void processNode(aiNode* node,const aiScene* scene);
chem::Mesh processMesh(aiMesh* mesh,const aiScene* scene);
void drawModel(glm::mat4 model , glm::mat4 camera);//;draw model as per mesh
std::vector<Texture> loadMaterialTexture(aiMaterial * material, aiTextureType type, std::string typeName );
unsigned int load_texture(std::string texture_dir, const char* name_4_texture);

void clean();

private:
std::vector<Mesh> meshes;
std::string directory_4_model ;
std::string directory_4_textures ;


};
};