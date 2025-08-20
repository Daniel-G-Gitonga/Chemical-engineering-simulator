#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 coord;

out vec2 textCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model_pos;

void main(){
    gl_Position = projection * view * model * model_pos * vec4(pos,1.0);
    textCoords = coord;
}