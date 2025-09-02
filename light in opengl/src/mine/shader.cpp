
#include "mine/shader.h"


namespace rose{
Shader::Shader(){}

void Shader::loadShader(std::string path_fragment_shader, std::string path_vertex_shader){
    fragment_file.exceptions (std::fstream::badbit  | std::fstream::failbit);
    vertex_file.exceptions (std::fstream::badbit  | std::fstream::failbit);
    
    try
    {
        vertex_file.open(path_vertex_shader);
        fragment_file.open(path_fragment_shader);

        v_stream << vertex_file.rdbuf();
        f_stream << fragment_file.rdbuf();

        vertex_file.close();
        fragment_file.close();

        vertex_code = v_stream.str();
        fragment_code = f_stream.str();
    }
    catch(const std::exception& e)
    {
        std::cerr<< " failure to load the path of the shader... " << e.what() << '\n';
    }
    

    fragment_shader_src = fragment_code.c_str();
    vertex_shader_src   = vertex_code.c_str();

}
void Shader::compileShader(){
vertex_shader  = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
glCompileShader(vertex_shader);

fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
glCompileShader(fragment_shader);

}
void Shader::linkShaders(){
    main_program = glCreateProgram();
    glAttachShader(main_program, vertex_shader);
    glAttachShader(main_program, fragment_shader);
    glLinkProgram(main_program);

}
void Shader::checkError(){
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex_shader, 216, NULL, infoLog);
        std::cout<<"failed to compile vertex shader for ...  \n"<<infoLog <<std::endl; 

    }
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment_shader, 216, NULL, infoLog);
        std::cout<<"failed to compile fragment shader for ...  \n"<<infoLog <<std::endl; 
    }
    glGetProgramiv(main_program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(main_program, 216, NULL, infoLog);
        std::cout<<"failed to link the main_program for ...  \n"<<infoLog <<std::endl; 
    }

}

void Shader::setUp(GLuint prog){
    main_program = prog;
compileShader();
linkShaders();
checkError();
}

//////////////////////////////Beware of the following unis.....(I mean uniforms...)
void Shader::uniforms(int i, const char* name){
glUniform1i(glGetUniformLocation(main_program, name),i);
}
void Shader::uniforms(glm::mat4 a,  const char* name){
glUniformMatrix4fv(glGetUniformLocation(main_program, name), 1, GL_FALSE, glm::value_ptr(a));
}
void Shader::uniforms(glm::vec4 a,  const char* name){
glUniform4fv(glGetUniformLocation(main_program, name), 1, glm::value_ptr(a));
}
void Shader::uniforms(glm::vec3 a,  const char* name){
glUniform3fv(glGetUniformLocation(main_program, name), 1, glm::value_ptr(a));
}

void Shader::useProgram(){
    glUseProgram(main_program);
}
void Shader::clean(){
     glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(main_program);
}
Shader::~Shader(){

}
}
//base line of use.. load shader
//setup(calls everything else we previously defined...)
//you can call useProgram function...