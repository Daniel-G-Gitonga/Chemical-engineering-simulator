#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norms;
layout (location = 2) in vec2 textCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out mat4 view_pass;

out vec3 normal;
out vec3 frag_pos;
out vec3 position;

out vec2 tex;

void main(){
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    tex = textCoords ;
    frag_pos = vec3( vec4(pos, 1.0f));
    position = pos;
    view_pass = view;
    normal  = normalize(mat3(((inverse(transpose(model))))) * norms);
}