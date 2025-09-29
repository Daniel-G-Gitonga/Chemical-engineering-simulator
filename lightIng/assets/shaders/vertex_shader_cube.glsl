#version 330 core 

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 textCoords;
layout (location = 2) in vec3 normals;

void main(){
    vec3 o_normals = normals;
    vec2 o_textCoords = textCoords;
    
    gl_Position = vec4(aPos, 1.0f);
}