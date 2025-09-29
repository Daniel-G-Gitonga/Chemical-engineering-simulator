#version 330 core
layout  (location = 0) in vec3 pos;
layout  (location = 1) in vec3 norms;
layout  (location = 2) in vec2 textCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 rot;

out vec3 posFragment;
out vec3 aNorms;
out vec2 text_coords;
out vec3 finalLightPos;



void main(){
aNorms = mat3(transpose(inverse(model))) *  norms ;

gl_Position = projection * view * rot * model * vec4(pos, 1.0);
posFragment = vec3(rot * model * vec4(pos, 0.0));


text_coords = textCoords;
}