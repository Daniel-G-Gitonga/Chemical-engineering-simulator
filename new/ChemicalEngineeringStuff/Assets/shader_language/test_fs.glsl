#version 330 core

out vec4 FragColor;

in vec2 text_coords_fs;
uniform sampler2D texture_img;

void main()
{
FragColor = texture(texture_img, text_coords_fs );//vec4(0.50f,1.0f,0.50f,1.0f) ;

}