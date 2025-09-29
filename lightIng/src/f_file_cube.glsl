#version 330 core
out vec4 FragColor;
in vec2 text_coords;

uniform sampler2D text;
uniform vec3 lightColor;

void main(){
FragColor = vec4(lightColor,1.0);//vec4(1.0f,1.0f,1.0f,1.0f);//texture(text, text_coords);// * vec4(1.0,0.5,0.0,1.0);
}