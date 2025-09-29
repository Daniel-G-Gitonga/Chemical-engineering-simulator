#version 330 core
layout  (location = 0) in vec3 pos;
layout  (location = 1) in vec3 norms;
layout  (location = 2) in vec2 textCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 rot;
uniform mat4 lightPosition;


out vec2 text_coords;

void main(){
gl_Position = projection * view *  lightPosition * rot * model *  vec4(pos, 1.0);
text_coords = textCoords;
}