#include "mine/mesh.h"


namespace rose{
     Cube::Cube(){}
   void Cube::set_c(){
    Vertex = {
    // positions           // texture coords

    // Front face
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,

    // Back face
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,

    // Left face
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

    // Right face
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f,

    // Bottom face
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,

    // Top face
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f
};
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertex.size() * sizeof(float), Vertex.data() , GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    loadShader("../assets/shaders/fsc.glsl", "../assets/shaders/vsc.glsl");
    setUp(prog);
   }
   void Cube::draw_c(){
      glBindVertexArray(VAO);
      useProgram();
      glDrawArrays(GL_TRIANGLES, 0, 36);

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);
      
   }
   void Cube::release_c(){
    clean();
   }
     Cube::~Cube(){}

     Pyramid::Pyramid(){}
   void Pyramid::set_c(){
     Vertex = {
     // --- Base (Y = 0), normal pointing down (0, -1, 0) ---

    // Triangle 1
    -1.0f, 0.0f, -1.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,  // v0
     1.0f, 0.0f, -1.0f,   0.0f, -1.0f, 0.0f,   1.0f, 0.0f,  // v1
     1.0f, 0.0f,  1.0f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f,  // v2

    // Triangle 2
    -1.0f, 0.0f, -1.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,  // v0
     1.0f, 0.0f,  1.0f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f,  // v2
    -1.0f, 0.0f,  1.0f,   0.0f, -1.0f, 0.0f,   0.0f, 1.0f,  // v3

    // --- Side 1 (Front) ---
    -1.0f, 0.0f, -1.0f,  -0.707f, 0.5f, -0.5f,   0.0f, 0.0f,  // base left
     0.0f, 2.0f,  0.0f,  -0.707f, 0.5f, -0.5f,   0.5f, 1.0f,  // tip
     1.0f, 0.0f, -1.0f,   0.707f, 0.5f, -0.5f,   1.0f, 0.0f,  // base right

    // --- Side 2 (Right) ---
     1.0f, 0.0f, -1.0f,   0.707f, 0.5f, -0.5f,   0.0f, 0.0f,
     0.0f, 2.0f,  0.0f,   0.707f, 0.5f,  0.5f,   0.5f, 1.0f,
     1.0f, 0.0f,  1.0f,   0.707f, 0.5f,  0.5f,   1.0f, 0.0f,

    // --- Side 3 (Back) ---
     1.0f, 0.0f,  1.0f,   0.707f, 0.5f, 0.5f,    0.0f, 0.0f,
     0.0f, 2.0f,  0.0f,   0.0f,   0.5f, 1.0f,    0.5f, 1.0f,
    -1.0f, 0.0f,  1.0f,  -0.707f, 0.5f, 0.5f,    1.0f, 0.0f,

    // --- Side 4 (Left) ---
    -1.0f, 0.0f,  1.0f,  -0.707f, 0.5f, 0.5f,    0.0f, 0.0f,
     0.0f, 2.0f,  0.0f,  -0.707f, 0.5f, -0.5f,   0.5f, 1.0f,
    -1.0f, 0.0f, -1.0f,  -0.707f, 0.5f, -0.5f,   1.0f, 0.0f,
};
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertex.size() * sizeof(float), Vertex.data() , GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    loadShader("../assets/shaders/fsp.glsl", "../assets/shaders/vsp.glsl");
    setUp(prog);
   }
   void Pyramid::draw_c(){
      glBindVertexArray(VAO);
      useProgram();
      glDrawArrays(GL_TRIANGLES, 0, 18);

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

   }
   void Pyramid::release_c(){
     clean();    
   }
     Pyramid::~Pyramid(){}
}