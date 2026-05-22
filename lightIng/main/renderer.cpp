#include "renderer.h"

#define STB_IMAGE_IMPLEMENTATION
   #include "stb_image.h"


void Shader::loadShader(std::string path_vertex, std::string path_fragment){
std::fstream v_file;
std::fstream f_file;

v_file.exceptions(std::ios::failbit | std::ios::badbit);
f_file.exceptions(std::ios::failbit | std::ios::badbit);
 std::stringstream vertex_stream;
std::stringstream fragment_stream;
  
try
{
  v_file.open(path_vertex.c_str());
  f_file.open(path_fragment.c_str());
 
    vertex_stream  << v_file.rdbuf();
    fragment_stream << f_file.rdbuf();
  v_file.close();
  f_file.close();    
}
catch(const std::exception& e)
{
    std::cerr <<" FAILURE LOADING THE SHADER "<< e.what() << '\n';
}
vertex_code   = vertex_stream.str();
fragment_code = fragment_stream.str(); 
vertex_source   = vertex_code.c_str();
fragment_source = fragment_code.c_str();
}
GLuint Shader::loadTexture(std::string path_texture, int i){

int width      = int();
int height     = int();
int nrChannels = int();
int format     = int();

stbi_set_flip_vertically_on_load(true);

unsigned char* data = stbi_load(path_texture.c_str(), &width, &height, &nrChannels, 0);


glGenTextures(1, &text);
glBindTexture(GL_TEXTURE_2D, text);
glActiveTexture(GL_TEXTURE0 + i);

nrChannels = 4 ? format = GL_RGBA : format = GL_RGB;

if(data){
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


stbi_image_free(data);
return text;
}

void Shader::check_errors(){
    int success;
    char infoLog[516];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
    glGetShaderInfoLog(vertex_shader, 516, NULL, infoLog);
    printf("ERROR COMPILING V_SHADER :: %s", infoLog );
    }
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success){
    glGetShaderInfoLog(fragment_shader, 516, NULL, infoLog);
    printf("ERROR COMPILING F_SHADER :: %s", infoLog );
    }
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
    glGetProgramInfoLog(program, 516, NULL, infoLog);
    printf("ERROR LINKING Program :: %s", infoLog );
    }

}
void Shader::compileShader(std::vector<float> vertices, std::vector<unsigned int> indices){

glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW );
glGenBuffers(1, &IBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW );

glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0));
glEnableVertexAttribArray(1);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
glEnableVertexAttribArray(2);
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));

vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertex_shader, 1, &vertex_source, NULL);
glCompileShader(vertex_shader);

fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragment_shader, 1, &fragment_source, NULL);
glCompileShader(fragment_shader);

program         = glCreateProgram();
glAttachShader(program, vertex_shader);
glAttachShader(program, fragment_shader);
glLinkProgram(program);

check_errors();
}
void Shader::drawObj(int num){
    glDrawElements(GL_TRIANGLES, num, GL_UNSIGNED_INT, 0);
}

void Shader::uniform(std::string name, int i){
glUniform1i(glGetUniformLocation(program, name.c_str()), i);
}
void Shader::uniform(std::string name, glm::mat4 mat4){
glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
}
void Shader::uniform(std::string name, glm::vec4 vec4){
glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, glm::value_ptr(vec4));
}
void Shader::uniform(std::string name, glm::vec3 vec3){
glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, glm::value_ptr(vec3));
}