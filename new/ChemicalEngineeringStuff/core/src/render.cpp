#include "render.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

chem::Render::Render(){
     chem::Render::initRenderer();
}
chem::Render::~Render(){

}
void chem::Render::initRenderer(){
    //PLS CHECK
    
   if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
std::cout<<"Failed to initialize glad"<<std::endl;
    
    
    }else{
        printf("Succesfully initiallized glad");
        glViewport(0,0, 600, 600 );
        std::cout<<"glad context "<<glfwGetCurrentContext()<<std::endl; 
    }
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_BLEND);//for transparency , controlled in render for glass or smt
    glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
     
}
std::vector<GLuint> chem::Render::setUp(std::string name, const char* vertex_path, const char* fragment_path, std::vector<Vertex> vertex, std::vector<unsigned int> indices_pass, int indexCount, int vertexCount){

if(vertex.empty() || indices_pass.empty()){
std::cout<<"EMPTY VERTEX AND INDICES"<<std::endl;
//return ;
}

std::ifstream load_vertex;
std::ifstream load_fragment;

std::string fragment_shader_code;
std::string vertex_shader_code;

load_vertex.exceptions(std::ios::badbit | std::ios::failbit);
load_fragment.exceptions(std::ios::badbit | std::ios::failbit);
try{
load_vertex.open(vertex_path);
load_fragment.open(fragment_path);

std::stringstream vertex_stream;
std::stringstream fragment_stream;

vertex_stream << load_vertex.rdbuf();
fragment_stream << load_fragment.rdbuf();

vertex_shader_code = vertex_stream.str();
fragment_shader_code = fragment_stream.str();

load_vertex.close();
load_fragment.close();
}
catch(std::ifstream::failure e){
std::cout<<" \n FAILED TO LOAD THE SHADERS  DUE TO UNKNOWN ERRORS "<< e.what()<<std::endl;
printf("PATH FOR VERTEX SHADER FILE %s \n PATH FOR FRAGMENT SHADER FILE %s \n ", vertex_path, fragment_path);
}

const char* fragment_shader_source = fragment_shader_code.c_str();
const char* vertex_shader_source = vertex_shader_code.c_str();


glGenVertexArrays(1,&VAO);
glBindVertexArray(VAO);
glGenBuffers(1,&VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER,  sizeof(Vertex) * vertexCount, vertex.data(), GL_STATIC_DRAW);
glGenBuffers(1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,  indexCount  * sizeof(unsigned int) , indices_pass.data(), GL_STATIC_DRAW);

glEnableVertexAttribArray(0);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 8 * sizeof(float),(void*)offsetof(Vertex, position));
glEnableVertexAttribArray(1);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(offsetof(Vertex, normals)));
glEnableVertexAttribArray(2);
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(offsetof(Vertex, text_coords)));


//prog

vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
glCompileShader(vertexShader);

fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
glCompileShader(fragmentShader);

program = glCreateProgram();
glAttachShader(program,vertexShader);
glAttachShader(program, fragmentShader);
glLinkProgram(program);


error_checker(name, &vertexShader, &fragmentShader, &program);

std::vector<GLuint> model_obj;
model_obj.push_back(VAO);
model_obj.push_back(program);
model_obj.push_back(EBO);

return model_obj;

}
void chem::Render::error_checker(std::string name, GLuint *vertexShader, GLuint *fragementShader, GLuint *program){

    int success;
    char infoLog[560];

{
    glGetShaderiv(*vertexShader , GL_COMPILE_STATUS, &success );
    if(!success){
        glGetShaderInfoLog(*vertexShader, 560, NULL, infoLog);
        std::cout<<"ERROR :: VERTEX_SHADER_NOT_ATTACHED FOR "<<name<<" "<<infoLog<<std::endl;
    }
}
{  
    glGetShaderiv(*fragementShader , GL_COMPILE_STATUS, &success );
    if(!success){
        glGetShaderInfoLog(*fragementShader, 560, NULL, infoLog);
        std::cout<<"ERROR :: FRAGMENT_SHADER_NOT_ATTACHED FOR "<<name<<" "<<infoLog<<std::endl;
    }
}
{
   glGetProgramiv(*program , GL_LINK_STATUS, &success );
    if(!success){
        glGetProgramInfoLog(*program, 560, NULL, infoLog);
        std::cout<<"ERROR :: PROGRAM NOT ATTACHED FOR "<<name<<" "<<infoLog<<std::endl;
    }
}
}
void chem::Render::useProgram(GLuint program){
    glUseProgram(program);
}


chem::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){
    this->vertex = vertices;
    this->indices = indices;
   // this->textures = textures;
    //dat test
 

    setUp();
}
chem::Mesh::~Mesh(){


}
void chem::Mesh::setUp(){

   std::vector<GLuint> mesh_obj = chem::Render::setUp("test mesh", "../../Assets/shader_language/test_vs.glsl", "../../Assets/shader_language/test_fs.glsl", vertex, indices, indices.size(),  vertex.size());

   VAO = mesh_obj[0];
   program_mesh = mesh_obj[1];
   EBO = mesh_obj[2];
   use_program_for_mesh();
}
void chem::Mesh::use_program_for_mesh(){
useProgram(program_mesh);

}
void chem::Mesh::renderMesh(){
  
  glBindVertexArray(VAO);
  //glBindTexture(GL_TEXTURE_2D, texture);
  glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_INT, 0);
}
void chem::Mesh::uniforms(std::string name, int i)
{
    glUniform1i(glGetUniformLocation(program_mesh, name.c_str()), static_cast<GLuint>(i));
}


chem::Model::Model(std::string path){

//test if directory all setup
//std::cout<<"directory for model "<<directory_4_model<<std::endl;
//std::cout<<"directory for texture "<<directory_4_textures<<std::endl;
directory_4_model = path;
directory_4_textures = path.substr(0, path.find_last_of("/"))+"/../textures/";
    load_model();

}
chem::Model::~Model(){

}
void chem::Model::load_model(){
   Assimp::Importer importer;
   const aiScene * scene = importer.ReadFile(directory_4_model, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
//load model and store it in scene object
    if(scene == NULL || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
       printf("FAILED TO LOAD THE MODEL FROM THE GIVEN DIR :: :: :: %s \n %s", directory_4_model.c_str(), importer.GetErrorString());
       
       return ;

    }

    
    processNode(scene->mRootNode, scene);
}
void chem::Model::processNode(aiNode* node,const aiScene* scene){

for(unsigned int i = 0 ; i < node->mNumMeshes ; i++){
aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
meshes.push_back(processMesh(mesh, scene));
}
for(unsigned int i = 0 ;  i < node->mNumChildren ; i++){
    processNode(node->mChildren[i], scene);
}
}
chem::Mesh chem::Model::processMesh(aiMesh* mesh,const aiScene* scene){
std::vector<Vertex> vertices;
std::vector<unsigned int> indices;
std::vector<Texture> textures;

for(int i = 0; i < mesh->mNumVertices ; i++){
//for each mesh temporary store 
Vertex vertex;

glm::vec3 vector;
vector.x = mesh->mVertices[i].x;
vector.y = mesh->mVertices[i].y;
vector.z = mesh->mVertices[i].z;
vertex.position = vector;


glm::vec3 vector2;
vector2.x = mesh->mNormals[i].x;
vector2.y = mesh->mNormals[i].y;
vector2.z = mesh->mNormals[i].z;
vertex.normals = vector2;

glm::vec2 vector3;

if(mesh->mTextureCoords[0]){
vector3.x = mesh->mTextureCoords[0][i].x;
vector3.y = mesh->mTextureCoords[0][i].y;
vertex.text_coords = vector3;
}else{
    vertex.text_coords = glm::vec2( 0.0f , 0.0f);
}

vertices.push_back(vertex);
}
for(int i = 0; i < mesh->mNumFaces ; i++){
aiFace faces = mesh->mFaces[i];
for(int j = 0 ; j < faces.mNumIndices ; j++){
     indices.push_back(faces.mIndices[j]);
}

}

if(mesh->mMaterialIndex >= 0)
{
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = loadMaterialTexture(material, 
                                        aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTexture(material, 
                                        aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
}  

return chem::Mesh(vertices, indices, textures);//pls check texture not passed, if changed del this comment also check on material func and load  texture func
}
void chem::Model::drawModel(glm::mat4 model){
for(int i = 0; i < meshes.size() ; i++){
    meshes[i].use_program_for_mesh();
    glUniformMatrix4fv(glGetUniformLocation(meshes[i].program_mesh, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform1i(glGetUniformLocation(meshes[i].program_mesh,"texture"), 0);
    meshes[i].renderMesh();
}
}
std::vector<chem::Texture> chem::Model::loadMaterialTexture(aiMaterial * material, aiTextureType type, std::string typeName ){
std::vector<Texture> textures;
for(int i = 0 ; i<material->GetTextureCount(type); i++){
aiString str;
material->GetTexture(type, i, &str);
Texture texture;
texture.id = load_texture(directory_4_textures, str.C_Str());
texture.name = typeName;
texture.path = str.C_Str();
textures.push_back(texture); 

}
return textures;

}
unsigned int chem::Model::load_texture(std::string texture_dir, const char* name_4_texture){
std::string name_text_passed_through_arg = std::string(name_4_texture);

std::string  file_name = texture_dir + name_text_passed_through_arg;

unsigned int texture;
stbi_set_flip_vertically_on_load(true);
int width;
int height;
int nrChannels;



unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &nrChannels, 0);
if(!data){

    std::cout<<"failed to load the texture "<<std::endl;
    std::cout<<"texture given "<<file_name<<std::endl;
    std::cout<<"texture spaced wieredly, just avoid spacing, i wont write encordings :) :)"<<std::endl;
}

glGenTextures(1, &texture);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture);

//setings
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//gen
GLenum format =( nrChannels == 4) ? GL_RGBA : GL_RGB;
glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,GL_UNSIGNED_BYTE, data);

return texture;
}

