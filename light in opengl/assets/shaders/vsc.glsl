#version 330 core

layout (location = 0) in vec3 pos_c;
layout (location = 1) in vec2 textCoords_c;

out vec2 TextC_c;

uniform mat4 model;
uniform mat4 view;

void main(){
    TextC_c = textCoords_c;
    gl_Position =  view * model * vec4(pos_c, 1.0f);
}