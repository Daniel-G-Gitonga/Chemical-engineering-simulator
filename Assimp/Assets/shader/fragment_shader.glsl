#version 330 core

out vec4 fragColor;

uniform int texture;

struct Material{
sampler2D texture_diffuse1;
sampler2D texture_specular1;
sampler2D texture_diffuse2;
sampler2D texture_specular2;
sampler2D texture_diffuse3;
sampler2D texture_specular3;
};

uniform Material material;
in vec2 texture_coordinates;

vec4 color;

void main(){
    fragColor =  texture(material.texture_diffuse1, texture_coordinates);// vec4(0.0f, 1.0f, 1.0f, 1.0f);
}