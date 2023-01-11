#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <iostream>
#include "../include/stb/stb_image.h"
#include "shaderClass.h"

class Texture{
    public:
        GLuint ID;
        const char* type;
        Texture(const char* imagePath, const char* texType, GLenum slot, GLenum format, GLenum pixelType);

        // Assigns a Texture unit to a Texture
        void texUnit(Shader& shader, const char* uniform, GLuint unit);
        void Bind();
        void Unbind();
        void Delete();
};

#endif //TEXTURE_H
