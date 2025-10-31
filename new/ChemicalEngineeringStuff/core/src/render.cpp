#include "render.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
glBufferData(GL_ARRAY_BUFFER,  sizeof(Vertex) * vertexCount, &vertex[0], GL_STATIC_DRAW);
glGenBuffers(1,&EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER,  indexCount  * sizeof(unsigned int) , &indices_pass[0], GL_STATIC_DRAW);

glEnableVertexAttribArray(0);
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 8 * sizeof(float),(void*)offsetof(Vertex, vertices));
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
void chem::Render::draw(GLuint program_draw, GLuint VAO_draw,int indexCount, int vertexCount){
    chem::Render::useProgram(program_draw);
    glBindVertexArray(VAO_draw);
    glDrawElements(GL_TRIANGLES, indexCount,GL_UNSIGNED_INT, 0);
 }



chem::Mesh::Mesh(){
setUp();
std::vector<GLuint> mesh_obj = chem::Render::setUp("test mesh", "C:/Users/USER/Desktop/ChemicalEngineeringStuff/core/src/shader_language/test_vs.glsl", "C:/Users/USER/Desktop/ChemicalEngineeringStuff/core/src/shader_language/test_fs.glsl", vertex, indices, indices.size(),  vertex.size());

   VAO = mesh_obj[0];
   program_mesh = mesh_obj[1];
   EBO = mesh_obj[2];
 
   

}
chem::Mesh::~Mesh(){
glDeleteVertexArrays(1, &VAO);
glDeleteProgram(program_mesh);
}
void chem::Mesh::setUp(){
    
     vertex.push_back({glm::vec3(-0.5f, -0.5f, 0.0f),glm::vec3(0.0f),glm::vec2(0.0f)});
     vertex.push_back({glm::vec3( 0.5f, -0.5f, 0.0f),glm::vec3(0.0f),glm::vec2(0.0f)});
     vertex.push_back({glm::vec3( 0.5f, 0.5f, 0.0f),glm::vec3(0.0f),glm::vec2(0.0f)});
     vertex.push_back({glm::vec3(-0.5f,  0.5f, 0.0f),glm::vec3(0.0f),glm::vec2(0.0f)});
     
     indices={
     0,1,2,
     2,3,0
     };
}
void chem::Mesh::renderMesh(){

 //glDepthMask(true);
 useProgram(program_mesh);
 draw(program_mesh, VAO, indices.size(), vertex.size());
 //glDepthMask(false);

}
