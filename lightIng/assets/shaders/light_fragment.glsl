#version 330 core

out vec4 fragColor;
in vec2 tex;

uniform sampler2D cubeTexture;

uniform vec4 vec4_uniform;

void main(){
    
    fragColor = vec4_uniform;//vec4(1.0f, 1.0f, 0.0f, 1.0f);
}