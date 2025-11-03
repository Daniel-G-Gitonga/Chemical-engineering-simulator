#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 norms;
layout (location = 2) in vec2 textCoords;

uniform mat4 model;
out vec2 text_coords_fs;


void main()
{

text_coords_fs = textCoords;

gl_Position = model * vec4(aPos, 1.0f);

}