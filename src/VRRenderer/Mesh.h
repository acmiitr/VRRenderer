#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <VRRenderer/VAO.h>
#include <VRRenderer/VBO.h>
#include <VRRenderer/EBO.h>
#include <VRRenderer/Texture.h>
#include <VRRenderer/Camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
