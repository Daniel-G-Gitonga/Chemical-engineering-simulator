#version 330 core

layout (location = 0) in vec3 pos_p;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textCoords_p;
out vec2 TextC_p;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    TextC_p = textCoords_p;
    gl_Position = vec4(pos_p, 1.0f);
}