#include "model.h"

#define STB_IMAGE_IMPLEMENTATION
   #include "stb_image.h"
   

     Shader::Shader(std::string p_vertex, std::string p_fragment){
this->vertex_shader_path    = p_vertex;
this->fragment_shader_path = p_fragment;

loadShader();
vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
glCompileShader(vertex_shader);
fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
glCompileShader(fragment_shader);
program         = glCreateProgram();
glAttachShader(program, vertex_shader);
glAttachShader(program, fragment_shader);
glLinkProgram(program);

checkError();
}
void Shader::clean(){
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
}

void Shader::loadShader(){
    std::fstream vertex_file;
    std::fstream fragment_file;

    vertex_file.exceptions(std::ios::failbit | std::ios::badbit);
    fragment_file.exceptions(std::ios::failbit | std::ios::badbit);

    std::stringstream vertex_stream ;
    std::stringstream fragment_stream ;

    try
    {
        vertex_file.open(vertex_shader_path.c_str());
        fragment_file.open(fragment_shader_path.c_str());
        
        
        vertex_stream << vertex_file.rdbuf();
        fragment_stream << fragment_file.rdbuf();

        vertex_file.close();
        fragment_file.close();
    }
    catch(const std::exception& e)
    {
        std::cerr <<"shader not loaded "<< e.what() << '\n';
    }

    fragment_code = fragment_stream.str();
    vertex_code   = vertex_stream.str();
    
    vertex_shader_source   = vertex_code.c_str();
    fragment_shader_source = fragment_code.c_str();
}
void Shader::uniform(std::string name, int i){
    glUniform1i(glGetUniformLocation(program,name.c_str()), i);
}
void Shader::uniform(std::string name, glm::mat4 matrix4){
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix4));
}
void Shader::useProgram(){
    glUseProgram(program);
}
void Shader::checkError(){
    int success;
    char infoLog[516];
    {
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
    glGetShaderInfoLog(vertex_shader, 516, NULL, infoLog );
    printf("error in vertex shader {%s}\n",infoLog);
    }
    }
    {
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success){
    glGetShaderInfoLog(fragment_shader, 516, NULL, infoLog );
    printf("error in fragment shader {%s}\n",infoLog);
    }
    }
    {
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
    glGetProgramInfoLog(program, 516, NULL, infoLog );
    printf("error in program linkage {%s}\n",infoLog);
    }
    }
}



     Mesh::Mesh(std::vector<Vertex> &vertex, std::vector<unsigned int> &indices, std::vector<Texture> &texture){
    this->vertex  = vertex;
    this->indices = indices;
    this->texture = texture;

    setUp();
};
void Mesh::setUp(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);
   
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 ));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,normals));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texture_coords));

    glBindVertexArray(0);

}
void Mesh::draw(Shader &shader){
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(int i = 0; i < texture.size() ;i++){
      glActiveTexture(GL_TEXTURE0 + i);
      std::string number;
      std::string name = texture[i].texture_type;
      if(name == "texture_diffuse"){
        number = std::to_string(diffuseNr++);
        printf("diffuse found material.{%s}\n", (name + number).c_str() );
      }else if(name == "texture_specular"){
        number = std::to_string(specularNr++);
        printf("specular found material.{%s}\n", (name + number).c_str() );
      }

      shader.uniform(("material."+ name + number), i);
      glBindTexture(GL_TEXTURE_2D, texture[i].id);
    }

    shader.uniform("textures", texture.size());
    //shader.uniform("model",glm::rotate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)), glm::radians(45.0f) * static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f)));
    shader.uniform("view", glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,1.0f, 0.0f)));
    shader.uniform("projection", glm::perspective(glm::radians(65.0f), 2.0f/*width twice s big as height*/, 0.1f, 100.0f));

// draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void Mesh::clean(){
glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);
glDeleteBuffers(1, &IBO);
}

     Model::Model(std::string model_p){
this->model_path = model_p;
loadModel();
}
void Model::loadModel(){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(model_path, aiProcess_Triangulate | aiProcess_FlipUVs );
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout<<"error::assimp::"<< importer.GetErrorString() << std::endl;
        printf("IMPORTTATION FAILED :: l:: \n");
    }  
    model_texture_directory = model_path.substr(0, model_path.find_last_of("/")) ;
    model_texture_directory.push_back('/');

    processNode(scene->mRootNode, scene);
    importer.FreeScene();

}
void Model::processNode(aiNode* node, const aiScene* scene){
    for(int i = 0 ; i < node->mNumMeshes ; i++){
        //extract the meshes of this node
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for(int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
        
    }
    //process the mesh of this node
    //go to the nodes child and process the mesh of the child
    //go down to the child of child and process the mesh of them
}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene){
    //vertex, indices and texture
    std::vector<Vertex> vertex_mesh;
    std::vector<unsigned int> indices_mesh;
    std::vector<Texture> textures;

    for(int i = 0; i < mesh->mNumVertices ; i++){
        Vertex vert;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vert.vertices = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vert.normals = vector;

        if(mesh->mTextureCoords[0]){
            glm::vec2 text_coords;
            text_coords.x = mesh->mTextureCoords[0][i].x;
            text_coords.y = mesh->mTextureCoords[0][i].y;

            vert.texture_coords = text_coords;
        }else{
            vert.texture_coords = glm::vec2(0.0f);
        }
        vertex_mesh.push_back(vert);

    }

    for(unsigned int i = 0; i <  mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0 ; j < face.mNumIndices; j++){
            indices_mesh.push_back(face.mIndices[j]);
        }

    }

    if(mesh->mNumFaces >= 0){
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps  = loadMaterialTexture(material, aiTextureType_DIFFUSE , "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    }
    
    return Mesh(vertex_mesh, indices_mesh, textures);
        
}

std::vector<Texture> Model::loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string name){
std::vector<Texture> textures;
for(int i = 0; i < material->GetTextureCount(type); i++){
    aiString str;
    material->GetTexture(type, i, &str);//texture file location retrival
    Texture texture;
    texture.id   = loadTexture(str.C_Str(), model_texture_directory);
    texture.texture_type = name;
    texture.path         = str.C_Str();
    textures.push_back(texture);

}
return textures;
}
GLuint Model::loadTexture(std::string texture_location, std::string texture_directory){

stbi_set_flip_vertically_on_load(true);
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
glActiveTexture(GL_TEXTURE0);

int width, height, nrChannels;

std::string path_string = texture_directory  + texture_location;
const char* path = path_string.c_str();

printf("{%s} ", path);
unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
if(data){
int format ;
nrChannels == 4 ? format = GL_RGBA : format = GL_RGB; 

glTexImage2D(GL_TEXTURE_2D,0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glGenerateMipmap(GL_TEXTURE_2D);

}else{
    printf("inspect texture {%s} \n",path);
}
stbi_image_free(data);
return texture;
}
void   Model::draw(Shader &shader){
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].draw(shader);
    }
}
void Model::clean(){
    for(int i = 0; i < meshes.size(); i++){
        meshes[i].clean();
    }
}

///cleaning trash

//shader
//event
//camera
//animation
//lighting