#pragma once
/*
store vertex(position, normals, text_coords, faces[ebo_s])
store texture properties, lighting included
draw mesh
________________
for lighting lets do cube first
*/

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mine/shader.h"
#include "mine/camera.h"

namespace rose{
class Mesh : public Shader , public FlyCam{
public:
std::vector<float> Vertex;
GLuint VBO,VAO,prog;

virtual void set_c() = 0;
virtual void draw_c(glm::mat4 cam)= 0;
virtual void release_c() = 0;

};

class Cube : public Mesh{
public:
Cube();
void set_c();
void draw_c(glm::mat4 cam);
void release_c();
~Cube();
};
class Pyramid : public Mesh{
public:
Pyramid();
void set_c();
void draw_c(glm::mat4 cam);
void release_c();
~Pyramid();
};
}