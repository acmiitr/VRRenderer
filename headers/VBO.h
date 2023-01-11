#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include "../include/glm/glm.hpp"
#include <vector>

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;

};
class VBO{
    public:
        GLuint ID;
        VBO(std::vector<Vertex>& vertices);

        void Bind();
        void Unbind();
        void Delete();
};

#endif //VBO_H
