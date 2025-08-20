#version 330 core

out vec4 FragColor;
in vec2 textCoords;

uniform sampler2D ourTexture;
uniform vec4 ccolor;

void main(){
    FragColor = texture(ourTexture, textCoords) ;// * ccolor;//* texture(ourTexture, textCoords);
}