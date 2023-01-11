#include "../headers/Texture.h"

Texture::Texture(const char* imagePath, const char* texType, GLenum slot, GLenum format, GLenum pixelType) {
    // Loading the image
    type = texType;
    int widthImg, heightImg, numColorCh;
    // Flips the image so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imgBytes = stbi_load(imagePath, &widthImg, &heightImg, &numColorCh, 0);

    glGenTextures(1, &ID);
    // Activating Texture slot 0
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Modifying the Texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Generating the Texture
    if (imgBytes) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, imgBytes);
        glGenerateMipmap(GL_TEXTURE_2D);  // Mipmap on
    }
    else
    {
        std::cout << "Failed to load Texture" << std::endl;
    }

    stbi_image_free(imgBytes);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}
void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
