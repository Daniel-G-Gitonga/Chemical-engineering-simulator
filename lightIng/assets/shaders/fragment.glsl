#version 330 core

out vec4 fragColor;
in vec2 tex;
in vec3 normal;
in vec3 frag_pos;

in vec3 position;

in mat4 view_pass;

uniform vec4 vec4_uniform;//color of light obj

uniform vec3 view_pos;

uniform mat4 light_translation;
vec3 light_pos;
uniform sampler2D cubeTexture;
uniform sampler2D cubeTexture_specularMap;

float distance_l = 13.0f;
float attenuation = 1.0f;
//att is attenuation --- its constatnts
float att_constant  = 1.0f;
float att_linear    = 0.35f;
float att_quadratic = 0.44f;


void main(){
    light_pos =  vec3(0.0f, 0.0f, -3.0f);

    vec3 norms_n = normalize(normal);
    vec3 light_dir = normalize( light_pos - frag_pos );
    
    distance_l  = length(light_pos - frag_pos);
    attenuation = 1/(att_constant + (distance_l *att_linear) + ( att_quadratic * distance_l * distance_l));


    float ambient_strength = 0.4f;
    vec4 out_ambient_light = ambient_strength * vec4_uniform *  vec4(vec3( texture( cubeTexture, tex)), 1.0f);
    
    float diffuse_value = max(dot( light_dir, norms_n ), 0.0);
    vec4 diffuse = diffuse_value * vec4_uniform * vec4(vec3( texture( cubeTexture, tex)), 1.0f);
    
    float specular_strength = 90.5f;
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(light_dir, norms_n);
    float specular_value = pow(max(dot( view_dir, reflect_dir), 0.0f), 32);
    vec4 specular = specular_strength * specular_value * vec4_uniform *  vec4(vec3(texture( cubeTexture_specularMap, tex)),1.0f) ;

    out_ambient_light *= attenuation;
    specular          *= attenuation;
    diffuse           *= attenuation;

    fragColor = ( out_ambient_light + specular  + diffuse  ) * vec4(0.6f, 0.3f, 0.1f, 1.0f) * texture( cubeTexture, tex);
}