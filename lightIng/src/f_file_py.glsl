#version 330 core
out vec4 FragColor;
in vec2 text_coords;

in vec3 aNorms;//___________1
in vec3 posFragment;//______2

uniform sampler2D text;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 finalLightPos;
uniform mat4 lightRot;
uniform vec3 viewerPos;


void main(){

vec4 lightPosition = lightRot * vec4(1.0f);
vec3 o_finalLightPos = finalLightPos * vec3(lightPosition).xyz;

float ambientFactor = 0.15f;
vec3 ambient = lightColor * ambientFactor  * vec3(texture(text, text_coords));

//ambient lighting is basically how the lighting is during the dark high value = not so dark, low value = dark
vec3 lightRayVec = normalize(o_finalLightPos - posFragment);
vec3 norm = normalize(aNorms);
float diffuse = max(dot(norm, lightRayVec), 0.00);//finding the diffuse constant
vec3 diffuseLight =  diffuse * lightColor  * vec3(texture(text, text_coords));

//specular lighting, shinness of obj
float specularStrength = 0.10;
vec3 viewDir = normalize(viewerPos - posFragment);
vec3 reflectDir = reflect(lightRayVec, norm);
float specular = pow( max( dot(viewDir, reflectDir), 0.0),  256);
vec3 specularLight = specularStrength * specular * lightColor;


vec3 resultLight = ( ambient + diffuseLight + specularStrength ) * objectColor;
FragColor =  vec4(resultLight,1.0f);;// * vec4(1.0,0.5,0.0,1.0);
}