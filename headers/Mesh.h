#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

// struct Vertex {
//     glm::vec3 Position;
//     glm::vec3 Colors;
//     glm::vec2 TexCoords;
//     glm::vec3 Normal;
// };

class Mesh
{

public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO vao;
    Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures);

    void Draw(Shader &shader, Camera &camera);
};

#endif //MESH_H
